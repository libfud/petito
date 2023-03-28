#ifndef NES_HPP
#define NES_HPP

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include <optional>

#include "mos6502.hpp"
#include "apu.hpp"
#include "ppu.hpp"
#include "memory.hpp"
#include "cartridge.hpp"

namespace nes {
class NesMemory : public Memory
{

public:
    explicit NesMemory(Cartridge&& cart);

    ~NesMemory();

    void init();

    uint8_t read(uint16_t address) override;

    void write(uint16_t address, uint8_t data) override;

private:
    static constexpr uint16_t INTERNAL_RAM_END = 0x1FFF;
    static constexpr uint16_t INTERNAL_RAM_SIZE = 0x0800;
    static constexpr uint16_t INTERNAL_RAM_MASK = 0x07FF;
    static constexpr uint16_t PPU_REG_START = 0x2000;
    static constexpr uint16_t PPU_REG_END =   0x3FFF;
    static constexpr uint16_t PPU_MASK = 0x0007;
    static constexpr uint16_t APU_REG_START = 0x4000;
    static constexpr uint16_t APU_REG_END =   0x401F;

    /* 2K internal RAM */
    std::vector<uint8_t> internal_ram;

    PPU ppu;

    APU apu;

public:
    Cartridge cart;

};

class NES
{
public:
    explicit NES(Cartridge&& cart);
    ~NES();
    void run(bool reset = true);

// private:
    mos6502::MOS6502 cpu;

    NesMemory memory;
};

}

#endif
