#include <gtest/gtest.h>
#include <gmock/gmock.h>

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
constexpr uint16_t INFO_PAGE_ADDRESS = 0x0200;
constexpr uint8_t INFO_PAGE = INFO_PAGE_ADDRESS >> 8;
constexpr uint8_t SCRATCH_PAGE = 0x03;

constexpr uint16_t TEST_ROM_SIZE = 0x400;

constexpr uint16_t VECTOR_START = NMI_VECTOR;

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

    int32_t& get_cpu_clock() override { return cpu_clock; };

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

        throw std::runtime_error(fmt::format("Invalid address read {:04X}", address));
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

constexpr uint16_t RESET_ADDRESS = TEST_RAM_SIZE;
constexpr uint8_t RESET_ADDRESS_LOW = RESET_ADDRESS & 0xFF;
constexpr uint8_t RESET_ADDRESS_HIGH = (RESET_ADDRESS >> 8) & 0xFF;

constexpr uint16_t NMI_ADDRESS = RESET_ADDRESS + 256;
constexpr uint8_t NMI_ADDRESS_LOW = NMI_ADDRESS & 0xFF;
constexpr uint8_t NMI_ADDRESS_HIGH = (NMI_ADDRESS >> 8) & 0xFF;

constexpr uint16_t IRQ_ADDRESS = RESET_ADDRESS + 2 * 256;
constexpr uint8_t IRQ_ADDRESS_LOW = IRQ_ADDRESS & 0xFF;
constexpr uint8_t IRQ_ADDRESS_HIGH = (IRQ_ADDRESS >> 8) & 0xFF;

constexpr uint8_t RESET_BYTE_ADDRESS = 0x00;
constexpr std::array<uint8_t, 4> RESET_PATTERN = {0xBE, 0xEF, 0xCA, 0xFE};

constexpr uint16_t IDLE_ADDRESS = RESET_ADDRESS + 3 * 256;
constexpr uint8_t IDLE_ADDRESS_LOW = IDLE_ADDRESS & 0xFF;
constexpr uint8_t IDLE_ADDRESS_HIGH = (IDLE_ADDRESS >> 8) & 0xFF;

size_t add_reset_procedure(std::vector<uint8_t>& program, uint16_t reset_address)
{
    std::vector<uint8_t> reset_procedure{
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
        // go to idle procedure
        JMP_ABS, IDLE_ADDRESS_LOW, IDLE_ADDRESS_HIGH,
    };
    std::memcpy(&program[reset_address], reset_procedure.data(), reset_procedure.size());
    return reset_procedure.size();
}

constexpr uint8_t NMI_INFO_OFFSET = 0x10;

size_t add_nmi_procedure(std::vector<uint8_t>& program, uint16_t nmi_address)
{
    constexpr auto acc_offset = 4;
    constexpr auto x_offset = 5;
    constexpr auto y_offset = 6;
    constexpr auto flags_offset = 7;
    constexpr auto sp_offset = 8;
    std::vector<uint8_t> nmi_procedure{
        // push Acc and flags to stack
        PHP_IMPL, PHA_IMPL,
        // increment NMI counter, write NMI to memory
        INC_ABS, NMI_INFO_OFFSET + 0, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('N'),
        STA_ABS, NMI_INFO_OFFSET + 1, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('M'),
        STA_ABS, NMI_INFO_OFFSET + 2, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('I'),
        STA_ABS, NMI_INFO_OFFSET + 3, INFO_PAGE,
        // write X to memory
        TXA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + x_offset, INFO_PAGE,
        // push X (in Acc) onto stack, transfer SP to X, write SP to memory
        PHA_IMPL, TSX_IMPL, TXA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + sp_offset, INFO_PAGE,
        // pop X from stack, restore X
        PLA_IMPL, TAX_IMPL,
        // write Y to memory
        TYA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + y_offset, INFO_PAGE,
        // restore A, write A to memory
        PLA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + acc_offset, INFO_PAGE,
        // copy flags to acc, write flags to memory
        PLA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + flags_offset,
        // restore flags
        PHA_IMPL, PLP_IMPL,
        // restore A
        LDA_ABS, NMI_INFO_OFFSET + acc_offset, INFO_PAGE,
        // go to idle procedure
        JMP_ABS, IDLE_ADDRESS_LOW, IDLE_ADDRESS_HIGH,
    };
    std::memcpy(&program[nmi_address], nmi_procedure.data(), nmi_procedure.size());
    return nmi_procedure.size();
}

constexpr uint8_t IRQ_INFO_OFFSET = 0x20;

size_t add_irq_procedure(std::vector<uint8_t>& program, uint16_t irq_address)
{
    std::vector<uint8_t> irq_procedure{
        // push Acc and flags to stack
        PHP_IMPL, PHA_IMPL,
        INC_ABS, IRQ_INFO_OFFSET + 0, INFO_PAGE,
        // increment IRQ counter, write IRQ to memory
        INC_ABS, IRQ_INFO_OFFSET + 0, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('I'),
        STA_ABS, IRQ_INFO_OFFSET + 1, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('R'),
        STA_ABS, IRQ_INFO_OFFSET + 2, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('Q'),
        STA_ABS, IRQ_INFO_OFFSET + 3, INFO_PAGE,
        // go to idle procedure
        JMP_ABS, IDLE_ADDRESS_LOW, IDLE_ADDRESS_HIGH,
    };
    std::memcpy(&program[irq_address], irq_procedure.data(), sizeof(irq_procedure));
    return irq_procedure.size();
}

size_t add_idle_procedure(std::vector<uint8_t>& program, uint16_t address)
{
    std::vector<uint8_t> idle_procedure{
        NOP_IMPL, NOP_IMPL, NOP_IMPL, NOP_IMPL, NOP_IMPL, NOP_IMPL, NOP_IMPL, NOP_IMPL,
        // go back to start of idle procedure
        JMP_ABS, IDLE_ADDRESS_LOW, IDLE_ADDRESS_HIGH,
    };
    return address;
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

    const auto check_proc_size = [](auto base_address, auto max_address, auto proc_size, auto&& name)
    {
        if ((base_address + proc_size) > max_address)
        {
            throw std::runtime_error(
                fmt::format(
                    "{} procedure too large! Expected less than {}, got {}",
                    name,
                    max_address - base_address,
                    proc_size
                ));
        }
        logger::debug("Added {} procedure", name);
    };

    const auto reset_proc_size = add_reset_procedure(program, RESET_BYTE_ADDRESS);
    check_proc_size(RESET_ADDRESS, NMI_ADDRESS, reset_proc_size, "RESET");

    const auto nmi_base_address = NMI_ADDRESS - RESET_ADDRESS;
    const auto nmi_proc_size = add_nmi_procedure(program, nmi_base_address);
    check_proc_size(NMI_ADDRESS, IRQ_ADDRESS, nmi_proc_size, "NMI");

    const auto irq_base_address = IRQ_ADDRESS - RESET_ADDRESS;
    const auto irq_proc_size = add_irq_procedure(program, irq_base_address);
    check_proc_size(IRQ_ADDRESS, IDLE_ADDRESS, irq_proc_size, "IRQ");

    const auto idle_base_address = IDLE_ADDRESS - RESET_ADDRESS;
    add_idle_procedure(program, idle_base_address);
}

TEST(TestCpu, Reset)
{
    TestSystemBus system_bus{};
    CpuType cpu{system_bus, TEST_CLOCK_RATE_HZ};
    logger::set_pattern("%v");
    logger::set_level(LogLevel::Debug);

    std::memset(&system_bus.memory[0], 0xAA, sizeof(system_bus.memory));

    cpu.reset();
    cpu.set_diagnostics(false);
    auto state = cpu.save_state();
    ASSERT_EQ(state.pc, RESET_ADDRESS);
    ASSERT_TRUE(state.flags.interrupt_inhibit);

    logger::debug("Loading registers");
    cpu.run(2);
    auto save_state = cpu.save_state();
    ASSERT_EQ(save_state.x, 0xFF);
    ASSERT_EQ(save_state.acc, 0x00);
    ASSERT_EQ(save_state.opcode, LDA_IMM);
    logger::debug("Clearing memory");
    // cpu.run(5 * 255 + 3);
    while (save_state.x != 0)
    {
        cpu.step();
        save_state = cpu.save_state();
    }
    while (save_state.opcode != STA_ABS_X && save_state.op_decode.b2 != SCRATCH_PAGE)
    {
        cpu.step();
        save_state = cpu.save_state();
    }
    ASSERT_EQ(save_state.x, 0);
    while (save_state.opcode != JMP_ABS)
    {
        cpu.step();
        save_state = cpu.save_state();
    }
    ASSERT_EQ(
        std::memcmp(&system_bus.memory[INFO_PAGE_ADDRESS],
                    &RESET_PATTERN[0],
                    sizeof(RESET_PATTERN)),
        0);
    logger::debug("Storing pattern");
    cpu.run(8);
    logger::debug("Reset procedure complete");
    cpu.run(1);

    EXPECT_EQ(
        std::memcmp(&system_bus.memory[INFO_PAGE_ADDRESS],
                    &RESET_PATTERN[0],
                    sizeof(RESET_PATTERN)),
        0);

    logger::set_level(LogLevel::Warn);
}

TEST(TestCpu, Irq)
{

}

} // namespace mos6502
