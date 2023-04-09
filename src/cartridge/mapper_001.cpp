#include "mapper_001.hpp"
#include "../logger/logger.hpp"

namespace nes {

Mapper001::Mapper001(Cartridge& cart) :
    cartridge(cart),
    load_register(0),
    chr_bank_0(0),
    chr_bank_1(0),
    prg_bank(0),
    prg_ram_enable(0),
    write_counter(0),
    mirroring(NAMETABLE_0),
    prg_swap_bank(BANK_C000_FIXED),
    prg_bank_size(0),
    chr_bank_size(0)
{

}

uint8_t& Mapper001::cpu_map(uint16_t address, bool& is_rom)
{
    if (address >= 0x6000 && address < 0x8000)
    {
        auto mapped_address = address - 0x6000;
        auto& data = cartridge.prg_ram[mapped_address];
        logger::trace(
            "mapper001 access RAM, address=0x{:04X}, mapped=0x{:04X}, data 0x{:02x}",
            address,
            mapped_address,
            data);
        is_rom = false;
        return data;
    }

    uint32_t bank = (prg_bank & prg_bank_size) << BANK_SHIFT;
    auto mapped_address = (bank | address) - 0x8000;

    auto page_size = NesHeader::PRG_ROM_PAGE_SIZE;

    if (mapped_address >= page_size && cartridge.prg_rom.size() == page_size)
    {
        mapped_address -= page_size;
    }
    auto& data = cartridge.prg_rom[mapped_address];
    logger::trace(
        "mapper001 access ROM, address=0x{:04X}, mapped=0x{:04X}, data 0x{:02x}",
        address,
        mapped_address,
        data);
    return data;
}

uint8_t Mapper001::read(uint16_t address)
{
    logger::trace("mapper001 read to address=0x{:04X}", address);
    bool is_rom = false;
    return cpu_map(address, is_rom);
}

void Mapper001::check_modify_load_register(uint16_t address, uint8_t data)
{
    if (address >= 0x8000)
    {
        auto data_bit = data & 0x01;
        auto reset_bit = (data & 0x80) > 0;

        if (reset_bit)
        {
            logger::trace("mapper001 write reset");

            write_counter = 0;
            load_register = 0;

            mirroring = NAMETABLE_0;
            prg_swap_bank = BANK_C000_FIXED;
            prg_bank_size = BANK_SIZE_16K;
            chr_bank_size = ONE_8K_BANK;
        }
        else
        {
            load_register |= data_bit << (4 - write_counter);
            write_counter++;
        }
    }
}

void Mapper001::write(uint16_t address, uint8_t data)
{
    logger::trace("mapper001 write to address=0x{:04X}, data 0x{:02x}", address, data);

    /* TODO: This logic is still probably faulty. */
    check_modify_load_register(address, data);

    if (write_counter == 5)
    {
        write_counter = 0;
        const auto CONTROL_MIN = 0x8000;
        const auto CONTROL_MAX = 0x9FFF;
        const auto CHR_0_MIN = 0xA000;
        const auto CHR_0_MAX = 0xBFFF;
        const auto CHR_1_MIN = 0xC000;
        const auto CHR_1_MAX = 0xDFFF;
        if (address >= CONTROL_MIN && address <= CONTROL_MAX)
        {
            mirroring = load_register & 0x03;
            prg_swap_bank = load_register & 0x04 >> 2;
            prg_bank_size = load_register & 0x08 >> 3;
            chr_bank_size = load_register & 0x10;
            uint32_t bank = (prg_bank & prg_bank_size) << BANK_SHIFT;

            logger::trace(
                "mapper001 state: M={:02X} SWAP_BANK={:02X}, PRG_BANK_SIZE={}, PRG_BANK={:04X}, CHR_BANK_SIZE={}",
                mirroring,
                prg_swap_bank,
                prg_bank_size,
                bank,
                chr_bank_size);

        }
        else if (address >= CHR_0_MIN && address <= CHR_0_MAX)
        {
            chr_bank_0 = load_register & 0x1F;
        }
        else if (address >= CHR_1_MIN && address <= CHR_1_MAX)
        {
            chr_bank_1 = load_register & 0x1F;
        }
        else
        {
            uint32_t bank = (prg_bank & prg_bank_size) << BANK_SHIFT;

            prg_bank = load_register & 0x0F;
            prg_ram_enable = (load_register & 0x10) == 0;
            logger::trace(
                "mapper001 state: PRG_BANK={:02X}, BANK={:04X}, PRG_RAM_ENABLE={}",
                prg_bank,
                bank,
                prg_ram_enable);
        }
        load_register = 0;
    }

    if (address >= 0x6000 && address < 0x8000 && prg_ram_enable)
    {
        cartridge.prg_ram[address - 0x6000] = data;
    }
}

uint8_t& Mapper001::ppu_map(uint16_t address, bool& is_rom)
{
    if (address >= SIZE_8K)
    {
        is_rom = false;
        return cartridge.ppu_ram[(address - SIZE_8K) % PPU_RAM_SIZE];
    }

    auto is_8k_bank = chr_bank_size == ONE_8K_BANK;
    auto bank = is_8k_bank || address < SIZE_8K ? chr_bank_0 : chr_bank_1;
    auto mask = is_8k_bank ? 0x1E : 0x1F;

    uint32_t mapped_address = ((bank & mask) << PPU_BANK_SHIFT) | address;

    if (cartridge.chr_ram.size() != 0)
    {
        return cartridge.chr_ram[mapped_address];
    }

    return cartridge.chr_rom[mapped_address];
}

uint8_t Mapper001::ppu_read(uint16_t address)
{
    logger::trace("mapper001 ppu read to address=0x{:04X}", address);
    bool is_rom = false;
    return ppu_map(address, is_rom);
}

void Mapper001::ppu_write(uint16_t address, uint8_t data)
{
    logger::trace("mapper001 ppu write to address=0x{:04X}", address);
    bool is_rom = false;
    auto& data_ref = ppu_map(address, is_rom);
    if (!is_rom)
    {
        data_ref = data;
    }
}

} // namespace nes
