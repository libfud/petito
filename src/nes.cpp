#include <algorithm>
#include <exception>
#include <fstream>
#include <iterator>
#include <filesystem>

#include "nes.hpp"

namespace nes {

NES::NES(Cartridge&& cart, int32_t cpu_clock_rate) :
    cpu{system_bus, cpu_clock_rate},
    cart{std::move(cart)},
    apu{},
    ppu{system_bus},
    system_bus{this->cart, ppu, apu}
{
    system_bus.init();
}

NES::~NES() {}

void NES::run(bool reset)
{
    if (reset)
    {
        cpu.reset();
    }
    while (true)
    {
        auto cycles = cpu.step();
        ppu.run(cycles);
    }
}

}
