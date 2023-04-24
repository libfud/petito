#ifndef NES_HPP
#define NES_HPP

#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "mos6502.hpp"
#include "apu.hpp"
#include "ppu/ppu.hpp"
#include "cartridge/cartridge.hpp"
#include "system_bus.hpp"
#include "ppu/virtual_screen.hpp"

namespace nes {

constexpr int32_t DEFAULT_CPU_CLOCK_RATE = 1789733;

class NES
{
public:
    NES(Cartridge&& cart, int32_t cpu_clock_rate = DEFAULT_CPU_CLOCK_RATE);
    ~NES();
    void reset();
    void run(bool perform_reset = true);
    void run_until(const std::function<bool(const NES& nes)>& predicate);
    void run_diag();
    void step();
    void set_diagnostics(std::string diag_msg);
    auto diagnostics() const -> bool;
    auto diagnostics2() -> const std::string&;

private:
    mos6502::MOS6502 cpu;
    Cartridge cart;
    APU apu;
    PPU ppu;
    NesSystemBus system_bus;
    VirtualScreen virtual_screen;

    sf::RenderWindow window;
    float screen_scale;
    std::string diagnostic_msg;
public:
    const std::string_view debug_msg;
};

}

#endif
