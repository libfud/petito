#include <algorithm>
#include <exception>
#include <fstream>
#include <iterator>
#include <filesystem>

#include "nes.hpp"
#include "logger/logger.hpp"

namespace nes {

NesMemory::NesMemory(Cartridge&& cart) :
    internal_ram(2048),
    ppu(),
    apu(),
    cart(std::move(cart))
{}

void NesMemory::init()
{
    cart.init_mapper();
}

uint8_t NesMemory::read(uint16_t address)
{
    if (address <= INTERNAL_RAM_END)
    {
        logger::log(logger::LogLevel::Trace, "Reading address={:04X} from internal ram", address);
        uint16_t mapped_address = address & INTERNAL_RAM_MASK;
        return internal_ram[mapped_address];
    }
    else if (address <= PPU_REG_END)
    {
        logger::log(logger::LogLevel::Trace, "Reading address={:04X} from PPU", address);
        return ppu.read(address);
    }
    else if (address <= APU_REG_END)
    {
        logger::log(logger::LogLevel::Trace, "Reading address={:04X} from APU", address);
        return apu.read(address);
    }
    else
    {
        logger::log(logger::LogLevel::Trace, "Reading address={:04X} from Cart", address);
        return cart.read(address);
    }
}

void NesMemory::write(uint16_t address, uint8_t data)
{
    if (address <= INTERNAL_RAM_END)
    {
        logger::log(logger::LogLevel::Trace, "Internal Write: 0x{:04X} 0x{:02X}", address, data);
        uint16_t mapped_address = address % INTERNAL_RAM_SIZE;
        internal_ram[mapped_address] = data;
    }
    else if (address <= PPU_REG_END)
    {
        logger::log(logger::LogLevel::Trace, "PPU Write: 0x{:04X} 0x{:02X}", address, data);
        return ppu.write(address, data);
    }
    else if (address <= APU_REG_END)
    {
        logger::log(logger::LogLevel::Trace, "APU Write: 0x{:04X} 0x{:02X}", address, data);
        return apu.write(address, data);
    }
    else
    {
        logger::log(logger::LogLevel::Trace, "Cart Write: 0x{:04X} 0x{:02X}", address, data);
        return cart.write(address, data);
    }
}

NES::NES(Cartridge&& cart) :
    cpu(),
    memory(std::move(cart))
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
    }
}

}
