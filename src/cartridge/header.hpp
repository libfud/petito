#ifndef NES_HEADER_HPP
#define NES_HEADER_HPP

#include <array>
#include <cstdint>

#include <optional>

namespace nes {

class NesHeader
{
public:
    static constexpr size_t HEADER_SIZE = 16;
    static constexpr size_t PRG_ROM_PAGE_SIZE = 16384;
    static constexpr size_t CHR_ROM_PAGE_SIZE = 8192;
    static constexpr size_t PRG_RAM_PAGE_SIZE = 8192;
    static constexpr size_t CHR_RAM_PAGE_SIZE = 8192;

    static std::optional<NesHeader> from_bytes(const std::array<uint8_t, 16>& header_bytes);

    size_t prg_rom_size() const;

    size_t prg_ram_size() const;

    size_t chr_rom_size() const;

    size_t chr_ram_size() const;

    uint8_t mapper() const;

    bool horizontal_mirroring() const;
    bool vertical_mirroring() const;
    bool four_screen_vram() const;

    bool uses_trainer() const;

private:
    static constexpr uint8_t LETTER_N = 0x4E;
    static constexpr uint8_t LETTER_E = 0x45;
    static constexpr uint8_t LETTER_S = 0x53;
    static constexpr uint8_t MSDOS_EOF = 0x1A;

    static constexpr uint8_t MIRROR_TYPE_MASK = 0x01;
    static constexpr uint8_t PRG_RAM_MASK = 0x02;
    static constexpr uint8_t TRAINER_MASK = 0x04;
    static constexpr uint8_t IGNORE_MIRROR_MASK = 0x08;
    static constexpr uint8_t LOWER_MAPPER_MASK = 0xF0;
    static constexpr uint8_t LOWER_MAPPER_SHIFT = 4;
    static constexpr uint8_t UPPER_MAPPER_MASK = 0xF0;

    /** Number of PRG ROM pages in 16 KiB units */
    uint8_t prg_rom_pages;

    /** Number of PRG RAM pages in 16 KiB units */
    uint8_t prg_ram_pages;

    /** Number of CHR ROM pages in 8 KiB units */
    uint8_t chr_rom_pages;

    /** Number of CHR RAM pages in 8 KiB units */
    uint8_t chr_ram_pages;

    /* 0 => horizontal, CIRAM A10 = PPU A11 */
    /* 1 => vertical, CIRAM A10 = PPU A10 */
    uint8_t mirror;

    /* Has battery backed PRG RAM at 0x6000-0x70FFF or other persistent memory */
    bool has_prg_ram;

    /* Presence of 512 byte trainer at 0x7000-0x71FF */
    bool has_trainer;

    bool ignore_mirroring;

    uint8_t mapper_number;
};

}

#endif
