#include "gtest/gtest.h"
#include "ppu.hpp"
#include "../cartridge/mapper_000.hpp"
#include "../logger/logger.hpp"

namespace nes {

static constexpr std::string test_rom{"TestROM"};

class TestCartridge : public Cartridge {
public:
    bool load(const std::string& rom_name)
    {
        prg_rom.clear();
        prg_rom.reserve(SIZE_16K);
        prg_rom.resize(SIZE_16K);
        chr_rom.clear();
        chr_rom.reserve(SIZE_8K);
        chr_rom.resize(SIZE_8K);

        mapper = std::unique_ptr<Mapper>(new Mapper000(*this));
        return true;
    }
};

class TestPpu : public PPU {
public:
    TestPpu(int& test_clock, mos6502::InterruptSignals& interrupts, TestCartridge& test_cartridge)
        : PPU{test_clock, interrupts, static_cast<Cartridge&>(test_cartridge)}
    {
    }

    PpuCtrl& get_ctrl() { return ctrl; }
    PpuStatus& get_status() { return status; }
    uint8_t& get_latch() { return latch; };
    uint16_t& get_line_index() { return line_index; }
    uint16_t& get_cycle_index() { return cycle_index; }
    bool& get_odd_frame() { return odd_frame; }
};

class TestPpuApparatus {
public :
    TestPpuApparatus() :
        cart{},
        clock{0},
        signals{0},
        ppu{clock, signals, cart}
    {
        cart.load(test_rom);
    }
    TestCartridge cart;
    int clock;
    mos6502::InterruptSignals signals;
    TestPpu ppu;
};

TEST(TestPpu, PpuCtrl)
{
    TestPpuApparatus apparatus{};

    apparatus.ppu.cpu_write(PPU_REG_HIGH + PPU_CTRL, 0x00);
    ASSERT_EQ(apparatus.ppu.get_ctrl().serialize(), 0x00);

    apparatus.ppu.cpu_write(PPU_REG_HIGH + PPU_CTRL, 0xFF);
    ASSERT_EQ(apparatus.ppu.get_ctrl().serialize(), 0xFF);

    apparatus.ppu.cpu_write(PPU_REG_HIGH + PPU_CTRL, 0x80);
    ASSERT_EQ(apparatus.ppu.get_ctrl().serialize(), 0x80);
    ASSERT_TRUE(apparatus.ppu.get_ctrl().generate_nmi);
}

TEST(TestPpu, GenerateNmi)
{
    TestPpuApparatus apparatus{};
    logger::set_pattern("%v");
    logger::set_level(logger::LogLevel::Debug);
    apparatus.signals.nmi = false;
    apparatus.ppu.get_ctrl().generate_nmi = true;
    apparatus.ppu.get_line_index() = POST_RENDER_LINE_0 + 1;
    apparatus.ppu.get_cycle_index() = 1;
    apparatus.ppu.step();
    ASSERT_TRUE(apparatus.signals.nmi);
    ASSERT_FALSE(apparatus.ppu.get_ctrl().generate_nmi);
    ASSERT_TRUE(apparatus.ppu.get_status().in_v_blank);
    ASSERT_EQ(apparatus.ppu.get_line_index(), POST_RENDER_LINE_0 + 1);
    ASSERT_EQ(apparatus.ppu.get_cycle_index(), 2);
}

TEST(TestPpu, ReadStatus)
{
    TestPpuApparatus apparatus{};
    apparatus.ppu.get_status().in_v_blank = true;
    apparatus.ppu.get_latch() = 0xFF;
    auto data = apparatus.ppu.cpu_read(PPU_REG_HIGH + PPU_STATUS);
    ASSERT_FALSE(apparatus.ppu.get_status().in_v_blank);
    ASSERT_EQ(data, 0x9F);
}

TEST(TestPpu, OddFrameCycleSkip)
{
    TestPpuApparatus apparatus{};
    apparatus.ppu.get_line_index() = PRE_RENDER_SCANLINE;
    apparatus.ppu.get_cycle_index() = ODD_SPECIAL_TICK;
    apparatus.ppu.get_odd_frame() = true;
    apparatus.ppu.step();
    ASSERT_EQ(apparatus.ppu.get_line_index(), 0);
    ASSERT_EQ(apparatus.ppu.get_cycle_index(), 0);

    apparatus.ppu.get_line_index() = PRE_RENDER_SCANLINE;
    apparatus.ppu.get_cycle_index() = ODD_SPECIAL_TICK;
    apparatus.ppu.get_odd_frame() = false;
    apparatus.ppu.step();
    ASSERT_EQ(apparatus.ppu.get_line_index(), PRE_RENDER_SCANLINE);
    ASSERT_EQ(apparatus.ppu.get_cycle_index(), ODD_SPECIAL_TICK + 1);
}

} // namespace nes
