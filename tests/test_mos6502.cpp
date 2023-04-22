#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "mos6502.hpp"
#include "system_bus.hpp"
#include "logger/logger.hpp"
#include "test_system_bus.hpp"

namespace mos6502 {

using CpuType = MOS6502;
using logger::LogLevel;

constexpr int32_t TEST_CLOCK_RATE_HZ = 1000000;

class TestCpu : public ::testing::Test
{
public:
    TestCpu() :
        system_bus{TEST_RAM_SIZE, TEST_ROM_SIZE, INTERRUPT_VECTORS},
        cpu{system_bus,
        TEST_CLOCK_RATE_HZ} {}

    TestSystemBus system_bus;
    CpuType cpu;
    CpuData state = {};

    void wait_for_state(auto predicate)
    {
        while (!predicate(state))
        {
            cpu.step();
            state = cpu.save_state();
        }
    }

    void enter_idle_state()
    {
        auto in_idle_state = [](auto state){
            // return state.opcode == STA_ABS_X && state.op_decode.b2 == SCRATCH_PAGE;
            return state.opcode == JMP_ABS &&
                state.op_decode.b1 == IDLE_ADDRESS_LOW &&
                state.op_decode.b2 == IDLE_ADDRESS_HIGH;
        };
        wait_for_state(in_idle_state);
        wait_for_state(in_idle_state);
    }

    void step()
    {
        cpu.step();
        state = cpu.save_state();
    }

    void run(int steps)
    {
        cpu.run(steps);
        state = cpu.save_state();
    }

protected:
    void SetUp() override {
        logger::set_pattern("%v");
        logger::set_level(LogLevel::Warn);
        cpu.reset();
        state = cpu.save_state();
    }

    void TearDown() override {
        logger::set_level(LogLevel::Error);
    }
};

TEST_F(TestCpu, Reset)
{
    std::memset(&system_bus.memory[0], 0xAA, sizeof(system_bus.memory));
    ASSERT_EQ(state.pc, RESET_ADDRESS);
    ASSERT_TRUE(state.flags.interrupt_inhibit);

    logger::debug("Loading registers");
    run(2);
    ASSERT_EQ(state.x, 0xFF);
    ASSERT_EQ(state.acc, 0x00);
    ASSERT_EQ(state.opcode, LDA_IMM);

    logger::debug("Clearing memory");
    wait_for_state([](auto state){return state.x == 0;});
    wait_for_state([](auto state){
        return state.opcode == STA_ABS_X && state.op_decode.b2 == SCRATCH_PAGE;
    });
    ASSERT_EQ(state.x, 0);
    auto mem_check_page = [&](auto page_idx) {
        return std::all_of(
            system_bus.memory.begin() + page_idx,
            system_bus.memory.begin() + page_idx + 0x100,
            [](auto x){return x == 0;});
    };
    EXPECT_TRUE(mem_check_page(0));
    EXPECT_TRUE(mem_check_page(0x200));
    EXPECT_TRUE(mem_check_page(0x300));

    wait_for_state([](auto state){return state.opcode == JMP_ABS;});
    ASSERT_EQ(
        std::memcmp(&system_bus.memory[INFO_PAGE_ADDRESS],
                    RESET_PATTERN.data(),
                    RESET_PATTERN.size()),
        0);
}

TEST_F(TestCpu, Irq)
{
    const uint8_t* irq_info = &system_bus.memory[INFO_PAGE_ADDRESS + IRQ_INFO_OFFSET];

    enter_idle_state();

    step();
    system_bus.interrupt_signals.irq = true;
    enter_idle_state();
    EXPECT_EQ(irq_info[0], 1);
    EXPECT_EQ(std::memcmp(irq_info + 1, IRQ_PATTERN.data(), IRQ_PATTERN.size()), 0);

    step();
    system_bus.interrupt_signals.irq = true;
    enter_idle_state();
    EXPECT_EQ(system_bus.memory[INFO_PAGE_ADDRESS + IRQ_INFO_OFFSET], 2);
    EXPECT_EQ(std::memcmp(irq_info + 1, IRQ_PATTERN.data(), IRQ_PATTERN.size()), 0);
}

TEST_F(TestCpu, Nmi)
{
    const uint8_t* nmi_info = &system_bus.memory[INFO_PAGE_ADDRESS + NMI_INFO_OFFSET];

    enter_idle_state();

    step();
    system_bus.interrupt_signals.nmi = true;
    enter_idle_state();
    EXPECT_EQ(nmi_info[0], 1);
    EXPECT_EQ(std::memcmp(nmi_info + 1, NMI_PATTERN.data(), NMI_PATTERN.size()), 0);
    EXPECT_EQ(state.acc, nmi_info[4]);
    EXPECT_EQ(state.x, nmi_info[5]);
    EXPECT_EQ(state.y, nmi_info[6]);
    // EXPECT_EQ(state.flags.get(), nmi_info[7]);
    // EXPECT_EQ(state.stack_ptr, nmi_info[8]);
}


} // namespace mos6502
