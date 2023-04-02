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
#include "cartridge/cartridge.hpp"
#include "system_bus.hpp"

namespace nes {

constexpr int32_t DEFAULT_CPU_CLOCK_RATE = 1789733;

class NES
{
public:
    NES(Cartridge&& cart, int32_t cpu_clock_rate = DEFAULT_CPU_CLOCK_RATE);
    ~NES();
    void run(bool reset = true);

// private:
    mos6502::MOS6502 cpu;
    Cartridge cart;
    APU apu;
    PPU ppu;
    NesSystemBus system_bus;
};

}

#endif
