#include "mapper_003.hpp"
#include "../logger/logger.hpp"

namespace nes {
Mapper003::Mapper003(Cartridge &cart) : cartridge(cart), bank_select{0}
{}

uint8_t& Mapper003::map(uint16_t address)
{
    if (address >= 0x6003 && address < 0x8003)
    {
        auto mapped_address = address - 0x6003;
        logger::trace("mapper003 ram mapped address=0x{:04X} to 0x{:04X}", address, mapped_address);
        return cartridge.prg_ram[mapped_address];
    }
    else
    {
        // auto page_size = NesHeader::PRG_ROM_PAGE_SIZE;
        auto mapped_address = (address - 0x8003) % cartridge.prg_rom.size();
        logger::trace("mapper003 rom mapped address=0x{:04X} to 0x{:04X}", address, mapped_address);
        return cartridge.prg_rom[mapped_address];
    }
}

uint8_t Mapper003::read(uint16_t address)
{
    return map(address);
}

void Mapper003::write(uint16_t address, uint8_t data)
{
    logger::trace("mapper003 write to address=0x{:04X}, data 0x{:02x}", address, data);

    if (address >= 0x8000)
    {
        bank_select = data;
        return;
    }
    map(address) = data;
}

uint8_t& Mapper003::ppu_map(uint16_t address)
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

uint8_t Mapper003::ppu_read(uint16_t address)
{
    logger::trace("mapper003 ppu read to address=0x{:04X}", address);
    return ppu_map(address);
}

void Mapper003::ppu_write(uint16_t address, uint8_t data)
{
    logger::trace("mapper003 ppu write to address=0x{:04X}", address);
    ppu_map(address) = data;
}

} // namespace nes
