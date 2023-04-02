#include "gtest/gtest.h"
#include "ppu.hpp"
#include "../cartridge/mapper_000.hpp"

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

} // namespace nes
