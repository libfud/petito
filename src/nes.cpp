#include <algorithm>
#include <exception>
#include <fstream>
#include <iterator>
#include <filesystem>

#include "nes.hpp"

namespace nes {

NesMemory::NesMemory(Cartridge&& cartridge, mos6502::InterruptSignals& interrupt_signals, int& clock_counter) :
    internal_ram(2048),
    cart(std::move(cartridge)),
    ppu(clock_counter, interrupt_signals, cart),
    apu()
{}

void NesMemory::init()
{
    cart.init_mapper();
}

uint8_t NesMemory::read(uint16_t address)
{
    if (address <= INTERNAL_RAM_END)
    {
        uint16_t mapped_address = address & INTERNAL_RAM_MASK;
        return internal_ram[mapped_address];
    }
    else if (address <= PPU_REG_END)
    {
        return ppu.cpu_read(address);
    }
    else if (address <= APU_REG_END)
    {
        return apu.read(address);
    }
    else
    {
        return cart.read(address);
    }
}

void NesMemory::write(uint16_t address, uint8_t data)
{
    if (address <= INTERNAL_RAM_END)
    {
        uint16_t mapped_address = address % INTERNAL_RAM_SIZE;
        internal_ram[mapped_address] = data;
    }
    else if (address <= PPU_REG_END)
    {
        return ppu.cpu_write(address, data);
    }
    else if (address <= APU_REG_END)
    {
        return apu.write(address, data);
    }
    else
    {
        return cart.write(address, data);
    }
}

const Cartridge& NesMemory::get_cart() const
{
    return cart;
}

NES::NES(Cartridge&& cart, int32_t cpu_clock_rate) :
    cpu(cpu_clock_rate),
    memory(std::move(cart), cpu.interrupt_signals, cpu.clock_counter)
{
    cpu.set_memory(&memory);
}

NesMemory::~NesMemory() {}

NES::~NES() {}

void NES::run(bool reset)
{
    memory.init();
    if (reset)
    {
        cpu.reset();
    }
    while (true)
    {
        cpu.step();
        // memory.ppu.render();
    }
}

}
