#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <string>

#include "mos6502.hpp"
#include "system_bus.hpp"
#include "logger/logger.hpp"

namespace mos6502 {

using CpuType = MOS6502;
using logger::LogLevel;

constexpr int32_t TEST_CLOCK_RATE_HZ = 1000000;

constexpr uint16_t TEST_RAM_SIZE = 0x400;
constexpr uint8_t ZERO_PAGE = 0x00;
// constexpr uint8_t STACK_PAGE = 0x01;
constexpr uint16_t INFO_PAGE_ADDRESS = 0x0200;
constexpr uint8_t INFO_PAGE = INFO_PAGE_ADDRESS >> 8;
constexpr uint8_t SCRATCH_PAGE = 0x03;

constexpr uint16_t TEST_ROM_SIZE = 0x300;

constexpr uint16_t VECTOR_START = NMI_VECTOR;

constexpr uint16_t NMI_ADDRESS = TEST_RAM_SIZE;
constexpr uint8_t NMI_ADDRESS_LOW = NMI_ADDRESS & 0xFF;
constexpr uint8_t NMI_ADDRESS_HIGH = (NMI_ADDRESS >> 8) & 0xFF;

constexpr uint16_t IRQ_ADDRESS = TEST_RAM_SIZE;
constexpr uint8_t IRQ_ADDRESS_LOW = IRQ_ADDRESS & 0xFF;
constexpr uint8_t IRQ_ADDRESS_HIGH = (IRQ_ADDRESS >> 8) & 0xFF;

constexpr uint16_t RESET_ADDRESS = TEST_RAM_SIZE;
constexpr uint8_t RESET_ADDRESS_LOW = RESET_ADDRESS & 0xFF;
constexpr uint8_t RESET_ADDRESS_HIGH = (RESET_ADDRESS >> 8) & 0xFF;

constexpr uint8_t RESET_BYTE_ADDR = 0x00;

constexpr std::array<uint8_t, 4> RESET_PATTERN = {0xBE, 0xEF, 0xCA, 0xFE};

class TestSystemBus : public SystemBus
{
public:
    TestSystemBus();
    TestSystemBus(TestSystemBus&) = delete;
    TestSystemBus(TestSystemBus&&) = delete;
    TestSystemBus& operator=(TestSystemBus&) = delete;
    TestSystemBus&& operator=(TestSystemBus&&) = delete;
    virtual ~TestSystemBus() = default;

    InterruptSignals& get_interrupt_signals() override {
        return interrupt_signals;
    }

    int32_t& get_cpu_clock() override {
        return cpu_clock;
    };

    uint8_t read(uint16_t address) override
    {
        if (address < TEST_RAM_SIZE)
        {
            return memory[address];
        }

        if (address < (TEST_RAM_SIZE + TEST_ROM_SIZE))
        {
            uint16_t mapped_address = address - TEST_RAM_SIZE;
            return program[mapped_address];
        }

        if (address >= VECTOR_START)
        {
            uint16_t mapped_address = address - VECTOR_START;
            return vectors[mapped_address];
        }

        throw std::runtime_error("Invalid address read");
    }

    void write(uint16_t address, uint8_t data) override {
        if (address < TEST_RAM_SIZE)
        {
            memory[address] = data;
        }
        else
        {
            throw std::runtime_error("Invalid address write");
        }
    }

    uint8_t const_read(uint16_t address) const override {
        return address % 256;
    }

    std::vector<uint8_t> memory;
    std::vector<uint8_t> program;
    std::array<uint8_t, 6> vectors;
    InterruptSignals interrupt_signals = {};
    int32_t cpu_clock = 0;
};

size_t add_reset_procedure(std::vector<uint8_t>& program)
{
    std::array<uint8_t, 45> reset_procedure = {
        // set X to 0xFF and A to 0
        LDX_IMM, 0xFF,
        LDA_IMM, 0x00,
        // zero out 0x00 to 0xFF, 0x200-0x2FF and 0x300-0x3FF
        STA_ABS_X, 0x00, ZERO_PAGE,
        STA_ABS_X, 0x00, INFO_PAGE,
        STA_ABS_X, 0x00, SCRATCH_PAGE,
        // decrement X
        DEX_IMPL,
        // repeat until X reaches zero
        BNE_REL, static_cast<uint8_t>(-(3 * 3 + 1 + 2)),
        // I'm too tired to think of an elegant solution so enjoy brute force
        STA_ABS_X, 0x00, ZERO_PAGE,
        STA_ABS_X, 0x00, INFO_PAGE,
        STA_ABS_X, 0x00, SCRATCH_PAGE,
        LDA_IMM, RESET_PATTERN[0],
        LDY_IMM, RESET_PATTERN[1],
        STA_ABS, 0x00, INFO_PAGE,
        STY_ABS, 0x01, INFO_PAGE,
        LDA_IMM, RESET_PATTERN[2],
        LDY_IMM, RESET_PATTERN[3],
        STA_ABS, 0x02, INFO_PAGE,
        STY_ABS, 0x03, INFO_PAGE,
    };
    std::memcpy(&program[RESET_BYTE_ADDR], reset_procedure.data(), sizeof(reset_procedure));
    return sizeof(reset_procedure);
}

TestSystemBus::TestSystemBus() :
    memory(TEST_RAM_SIZE),
    program(TEST_ROM_SIZE),
    vectors{
        NMI_ADDRESS_LOW, NMI_ADDRESS_HIGH,
        RESET_ADDRESS_LOW, RESET_ADDRESS_HIGH,
        IRQ_ADDRESS_LOW, IRQ_ADDRESS_HIGH,
    }
{
    memory.reserve(TEST_RAM_SIZE);
    memory.resize(TEST_RAM_SIZE);
    program.reserve(TEST_ROM_SIZE);
    program.resize(TEST_ROM_SIZE);

    auto reset_proc_size = add_reset_procedure(program);
    logger::debug("Added reset procedure of size {}", reset_proc_size);
    std::array<uint8_t, 3> irq_procedure = {
        INC_ABS, 0x10, INFO_PAGE,
    };
    std::memcpy(&program[0x100], &irq_procedure[0], sizeof(irq_procedure));

    std::array<uint8_t, 3> nmi_procedure = {
        INC_ABS, 0x20, INFO_PAGE,
    };
    std::memcpy(&program[0x200], &nmi_procedure[0], sizeof(nmi_procedure));
}

TEST(TestCpu, Reset)
{
    TestSystemBus system_bus{};
    CpuType cpu{system_bus, TEST_CLOCK_RATE_HZ};
    logger::set_pattern("%v");
    logger::set_level(LogLevel::Warn);

    cpu.reset();
    cpu.set_diagnostics(true);
    auto state = cpu.save_state();
    ASSERT_EQ(state.pc, RESET_ADDRESS);
    ASSERT_TRUE(state.flags.interrupt_inhibit);

    logger::debug("Loading registers");
    cpu.run(2);
    logger::debug("Clearing memory");
    cpu.run(5 * 255 + 3);
    logger::debug("Storing pattern");
    cpu.run(8);
    logger::debug("Reset procedure complete");

    EXPECT_EQ(
        std::memcmp(&system_bus.memory[INFO_PAGE_ADDRESS],
                    &RESET_PATTERN[0],
                    sizeof(RESET_PATTERN)),
        0);

    logger::set_level(LogLevel::Warn);
}

} // namespace mos6502
