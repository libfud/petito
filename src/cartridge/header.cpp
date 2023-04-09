#include "header.hpp"

namespace nes {

std::optional<NesHeader> NesHeader::from_bytes(const std::array<uint8_t, 16>& header_bytes)
{
    NesHeader header{};

    if (header_bytes[0] != LETTER_N ||
        header_bytes[1] != LETTER_E ||
        header_bytes[2] != LETTER_S ||
        header_bytes[3] != MSDOS_EOF)
    {
        return {};
    }

    header.prg_rom_pages = header_bytes[4];
    header.chr_rom_pages = header_bytes[5];

    header.mirror = header_bytes[6] & MIRROR_TYPE_MASK;

    header.has_prg_ram = (header_bytes[6] & PRG_RAM_MASK) != 0;
    header.has_trainer = (header_bytes[6] & TRAINER_MASK) != 0;
    header.ignore_mirroring = (header_bytes[6] & IGNORE_MIRROR_MASK) != 0;
    header.mapper_number =
        (header_bytes[7] & UPPER_MAPPER_MASK) |
        ((header_bytes[6] & LOWER_MAPPER_MASK) >> LOWER_MAPPER_SHIFT);

    header.prg_ram_pages = header_bytes[8];

    header.chr_ram_pages = 0;
    if (header.chr_rom_pages == 0)
    {
        header.chr_ram_pages = 1;
    }

    return std::optional<NesHeader>(header);
}

size_t NesHeader::prg_rom_size() const
{
    return prg_rom_pages * PRG_ROM_PAGE_SIZE;
}

size_t NesHeader::prg_ram_size() const
{
    if (prg_ram_pages > 0)
    {
        return prg_ram_pages * PRG_RAM_PAGE_SIZE;
    }
    else
    {
        return PRG_RAM_PAGE_SIZE;
    }
}

size_t NesHeader::chr_rom_size() const
{
    return chr_rom_pages * CHR_ROM_PAGE_SIZE;
}

size_t NesHeader::chr_ram_size() const
{
    return chr_ram_pages * CHR_RAM_PAGE_SIZE;
}

uint8_t NesHeader::mapper() const
{
    return mapper_number;
}

bool NesHeader::horizontal_mirroring() const
{
    return !ignore_mirroring && mirror == 0;
}

bool NesHeader::vertical_mirroring() const
{
    return !ignore_mirroring && mirror == 1;
}

bool NesHeader::four_screen_vram() const
{
    return ignore_mirroring;
}

bool NesHeader::uses_trainer() const
{
    return has_trainer;
}

}
