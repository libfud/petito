#include "mapper_000.hpp"
#include "../logger/logger.hpp"

namespace nes {
Mapper000::Mapper000(Cartridge &cart) : cartridge(cart) {}

uint8_t& Mapper000::map(uint16_t address)
{
    if (address >= 0x6000 && address < 0x8000)
    {
        auto mapped_address = address - 0x6000;
        logger::trace("mapper000 ram mapped address=0x{:04X} to 0x{:04X}", address, mapped_address);
        return cartridge.prg_ram[mapped_address];
    }
    else
    {
        // auto page_size = NesHeader::PRG_ROM_PAGE_SIZE;
        auto mapped_address = (address - 0x8000) % cartridge.prg_rom.size();
        logger::trace("mapper000 rom mapped address=0x{:04X} to 0x{:04X}", address, mapped_address);
        return cartridge.prg_rom[mapped_address];
    }
}

uint8_t Mapper000::read(uint16_t address)
{
    return map(address);
}

void Mapper000::write(uint16_t address, uint8_t data)
{
    logger::trace("mapper000 write to address=0x{:04X}, data 0x{:02x}", address, data);

    if (address >= 0x8000 || address < 0x6000)
    {
        logger::error("mapper000 write denied to address=0x{:04X}, data 0x{:02x}", address, data);
        return;
    }
    map(address) = data;
}

uint8_t& Mapper000::ppu_map(uint16_t address)
{
    if (address >= SIZE_8K)
    {
        return cartridge.ppu_ram[(address - SIZE_8K) % PPU_RAM_SIZE];
    }
    if (cartridge.chr_ram.size() > 0)
    {
        return cartridge.chr_ram[address];
    }
    return cartridge.chr_rom[address];
}

uint8_t Mapper000::ppu_read(uint16_t address)
{
    logger::trace("mapper000 ppu read to address=0x{:04X}", address);
    return ppu_map(address);
}

void Mapper000::ppu_write(uint16_t address, uint8_t data)
{
    logger::trace("mapper000 ppu write to address=0x{:04X}", address);
    ppu_map(address) = data;
}

} // namespace nes
