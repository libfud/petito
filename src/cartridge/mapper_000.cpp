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
    logger::debug("mapper000 accessing 0x{:04X}", address);
    if (address >= SIZE_8K)
    {
        auto mapped_address = (address - SIZE_8K) % PPU_RAM_SIZE;
        logger::debug(
            "mapper000 accessing 0x{:04X}, ppu_ram sized 0x{:04X}",
            mapped_address,
            cartridge.ppu_ram.size());
        return cartridge.ppu_ram[mapped_address];
    }
    if (cartridge.chr_ram.size() > 0)
    {
        logger::debug(
        "mapper000 accessing from chr_ram 0x{:04X}, size 0x{:04x}",
            address,
            cartridge.chr_ram.size());
        return cartridge.chr_ram[address];
    }
    logger::debug(
        "mapper000 accessing from chr_rom 0x{:04X}, size 0x{:04x}",
        address,
        cartridge.chr_rom.size());
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
