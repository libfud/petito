#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

#include "mos6502.hpp"
#include "memory.hpp"
#include "nes.hpp"
#include "cartridge/cartridge.hpp"
#include "logger/logger.hpp"

namespace mos = mos6502;

TEST(TestFlags, get)
{
    mos::Flags flags{};
    flags.carry = false;
    flags.zero = false;
    flags.interrupt_inhibit = false;
    flags.bcd_arithmetic = false;
    flags.brk = false;
    flags.overflow = false;
    flags.negative = false;

    EXPECT_EQ(flags.get(), (1 << 5) | (0 << 4));
    EXPECT_EQ(flags.get_php(), (1 << 5) | (1 << 4));

    flags.brk = true;
    EXPECT_EQ(flags.get(), (1 << 5) | (1 << 4));
    EXPECT_EQ(flags.get_php(), (1 << 5) | (1 << 4));

    flags.carry = true;

    EXPECT_EQ(flags.get(), (1 << 5) | (1 << 4) | 1);
    EXPECT_EQ(flags.get_php(), (1 << 5) | (1 << 4) | 1);

    flags.zero = true;

    EXPECT_EQ(flags.get(), (1 << 5) | (1 << 4) | (1 << 1) | 1);
    EXPECT_EQ(flags.get_php(), (1 << 5) | (1 << 4) | (1 << 1) | 1);

    flags.interrupt_inhibit = true;
    flags.bcd_arithmetic = true;
    flags.brk = true;
    flags.overflow = true;
    flags.negative = true;

    EXPECT_EQ(flags.get(), 0xFF);
    EXPECT_EQ(flags.get_php(), 0xFF);

    flags.brk = false;
    EXPECT_EQ(flags.get(), 0xFF - (1 << 4));
    EXPECT_EQ(flags.get_php(), 0xFF);
}

class TestMemory : public Memory
{
public:
    std::vector<uint8_t> data;

    uint8_t read(uint16_t address) override
    {
        return data[address];
    }

    void write(uint16_t address, uint8_t value) override
    {
        data[address] = value;
    }

};

class TestNes : public ::testing::Test {
public:
    nes::Cartridge cart;
protected:
    TestNes() : cart{} {}

private:


};

TEST_F(TestNes, Reset)
{
    std::string filename = "data/roms/instr_test_v5/official_only.nes";
    cart.load(filename);
    nes::NES nes(std::move(cart));
    nes.memory.init();
    nes.cpu.reset();

    EXPECT_EQ(nes.cpu.pc, 0xEBFA);
    EXPECT_TRUE(nes.cpu.flags.interrupt_inhibit);
}

TEST_F(TestNes, NesTestRom)
{
    std::string filename = "data/roms/nestest.nes";
    cart.load(filename);
    nes::NES nes(std::move(cart));
    nes.memory.init();
    nes.cpu.reset();
    nes.cpu.pc = 0xC000;

    logger::set_pattern("%v");
    logger::set_level(logger::LogLevel::Debug);
    nes.run(false);
    // EXPECT_EQ(nes.cpu.pc, 0xEBFC);
    // for (auto idx = 0; idx < 8991; ++idx)
    // {
    //     nes.cpu.step();
    // }
    // logger::set_level(logger::LogLevel::Critical);
    // EXPECT_EQ(nes.cpu.read(2), 0);
    // EXPECT_EQ(nes.cpu.read(3), 0);
}

TEST_F(TestNes, FirstStep)
{
    std::string filename = "data/roms/instr_test_v5/official_only.nes";
    cart.load(filename);
    nes::NES nes(std::move(cart));
    nes.memory.init();
    nes.cpu.reset();

    nes.cpu.step();
    EXPECT_EQ(nes.cpu.pc, 0xEBFC);
}

TEST_F(TestNes, Stack)
{
    std::string filename = "data/roms/instr_test_v5/official_only.nes";
    cart.load(filename);

    TestMemory test_memory{};
    test_memory.data.reserve(0x6000 + cart.prg_rom.size() + cart.chr_rom.size());
    test_memory.data.resize(0x6000);
    std::copy_n(cart.prg_rom.begin(), cart.prg_rom.size(), std::back_inserter(test_memory.data));
    std::copy_n(cart.chr_rom.begin(), cart.chr_rom.size(), std::back_inserter(test_memory.data));

    mos::MOS6502 cpu{nes::DEFAULT_CPU_CLOCK_RATE};
    cpu.set_memory(&test_memory);

    cpu.reset();
    /*
    EXPECT_EQ(cpu.pc, 0xEBFA);
    EXPECT_EQ(cpu.pc & 0xFF, cart.prg_rom[0x7FFC]);
    EXPECT_EQ(cpu.pc >> 8, cart.prg_rom[0x7FFD]);
    */
    EXPECT_TRUE(cpu.flags.interrupt_inhibit);
    cpu.stack_ptr = 0xFF;
    // auto old_pc = cpu.pc;

    auto data = 0xAB;
    cpu.push(data);
    EXPECT_EQ(cpu.stack_ptr, 0xFE);
    EXPECT_EQ(test_memory.data[0x100 | cpu.stack_ptr + 1], data);
    auto comp_data = cpu.pull();
    EXPECT_EQ(data, comp_data);
}

TEST_F(TestNes, Addressing)
{
    std::string filename = "data/roms/instr_test_v5/official_only.nes";
    cart.load(filename);

    TestMemory test_memory{};
    test_memory.data.reserve(0x6000 + cart.prg_rom.size() + cart.chr_rom.size());
    test_memory.data.resize(0x6000);
    std::copy_n(cart.prg_rom.begin(), cart.prg_rom.size(), std::back_inserter(test_memory.data));
    std::copy_n(cart.chr_rom.begin(), cart.chr_rom.size(), std::back_inserter(test_memory.data));

    mos::MOS6502 cpu{nes::DEFAULT_CPU_CLOCK_RATE};
    cpu.set_memory(&test_memory);

    cpu.reset();
    EXPECT_TRUE(cpu.flags.interrupt_inhibit);
    cpu.stack_ptr = 0xFF;

    test_memory.data[0x200] = 0xAD;
    test_memory.data[0x201] = 0xDE;
    test_memory.data[0x202] = 0xFE;
    test_memory.data[0x203] = 0xBE;

    uint8_t b1;
    uint8_t b2;

    cpu.pc = 0x200;
    b1 = cpu.read(cpu.pc);
    b2 = cpu.read(cpu.pc + 1);

    auto addr = cpu.absolute(b1, b2);
    EXPECT_EQ(addr, 0xDEAD);

    cpu.pc = 0x200;
    cpu.x = 0x02;
    cpu.y = 0x44;
    b1 = cpu.read(cpu.pc);
    b2 = cpu.read(cpu.pc + 1);
    addr = cpu.absolute_idx(b1, b2, cpu.x);
    EXPECT_EQ(addr, 0xDEAF);

    cpu.pc = 0x200;
    cpu.x = 0x02;
    cpu.y = 0x44;
    b1 = cpu.read(cpu.pc);
    b2 = cpu.read(cpu.pc + 1);
    addr = cpu.absolute_idx(b1, b2, cpu.y);
    EXPECT_EQ(addr, 0xDEF1);

    cpu.x = 0x02;
    cpu.y = 0x44;
    cpu.pc = 0x8000;
    b1 = cpu.read(cpu.pc);
    addr = cpu.zero_page_x(b1);
    EXPECT_EQ(addr, 0x01);

    cpu.x = 0x02;
    cpu.y = 0x44;
    cpu.pc = 0x8000;
    b1 = cpu.read(cpu.pc);
    addr = cpu.zero_page_y(b1);
    EXPECT_EQ(addr, 0x43);

    test_memory.data[0xDEAD] = 0xEF;
    test_memory.data[0xDEAE] = 0xBE;
    test_memory.data[0xCAFE] = 0xAD;
    test_memory.data[0xCAFF] = 0xDE;
    cpu.pc = 0xCAFE;
    b1 = cpu.read(cpu.pc);
    b2 = cpu.read(cpu.pc + 1);
    addr = cpu.indirect(b1, b2);
    EXPECT_EQ(addr, 0xBEEF);
}
