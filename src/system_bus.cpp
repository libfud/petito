#include "system_bus.hpp"

namespace nes {

static constexpr uint16_t INTERNAL_RAM_END = 0x1FFF;
static constexpr uint16_t INTERNAL_RAM_SIZE = 0x0800;
static constexpr uint16_t INTERNAL_RAM_MASK = 0x07FF;
static constexpr uint16_t PPU_REG_END =   0x3FFF;
static constexpr uint16_t APU_REG_END =   0x401F;

NesSystemBus::NesSystemBus(Cartridge &cart, PPU &ppu, APU &apu)
    : cart{cart},
      ppu{ppu},
      apu{apu},
      internal_ram(2048)
{
}

InterruptSignals& NesSystemBus::get_interrupt_signals()
{
    return signals;
}

uint8_t NesSystemBus::read(uint16_t address)
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

void NesSystemBus::write(uint16_t address, uint8_t data)
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

uint8_t NesSystemBus::ppu_read(uint16_t address)
{
    return cart.ppu_read(address);
}

void NesSystemBus::ppu_write(uint16_t address, uint8_t data)
{
    return cart.ppu_write(address, data);
}

void NesSystemBus::init()
{
    cart.init_mapper();
}

} // namespace nes
