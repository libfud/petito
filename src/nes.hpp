#ifndef NES_HPP
#define NES_HPP

#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include <optional>

#include "mos6502.hpp"
#include "apu.hpp"
#include "ppu/ppu.hpp"
#include "memory.hpp"
#include "cartridge/cartridge.hpp"

namespace nes {

constexpr double DEFAULT_CPU_CLOCK_RATE = 1.789733 * 1e6;

class NesMemory : public Memory
{

public:
    NesMemory(Cartridge&& cartridge, int& clock_counter);

    ~NesMemory();

    void init();

    uint8_t read(uint16_t address) override;

    void write(uint16_t address, uint8_t data) override;

    const Cartridge& get_cart() const;

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

    Cartridge cart;

    PPU ppu;

    APU apu;
};

class NES
{
public:
    NES(Cartridge&& cart, double cpu_clock_rate = DEFAULT_CPU_CLOCK_RATE);
    ~NES();
    void run(bool reset = true);

// private:
    mos6502::MOS6502 cpu;

    NesMemory memory;
};

}

#endif
