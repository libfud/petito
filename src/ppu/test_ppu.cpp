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
    TestPpu(int& test_clock, TestCartridge& test_cartridge)
        : PPU{test_clock, static_cast<Cartridge&>(test_cartridge)}
    {
    }
};

TEST(TestPpu, BasicAssertions)
{
    int test_clock = 0;
    TestCartridge test_cartridge;
    test_cartridge.load(test_rom);
    TestPpu test_ppu{test_clock, test_cartridge};
    ASSERT_TRUE(true);
}

} // namespace nes
