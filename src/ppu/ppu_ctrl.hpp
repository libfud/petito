#ifndef PPU_CTRL_HPP
#define PPU_CTRL_HPP

#include <cstdint>

namespace nes {

constexpr uint16_t NAMETABLE_0 = 0x2000;
constexpr uint16_t NAMETABLE_1 = 0x2400;
constexpr uint16_t NAMETABLE_2 = 0x2800;
constexpr uint16_t NAMETABLE_3 = 0x2C00;

constexpr uint8_t VRAM_INCREMENT_ACROSS = 1;
constexpr uint8_t VRAM_INCREMENT_DOWN = 32;

constexpr uint16_t SPRITE_TABLE_0 = 0;
constexpr uint16_t SPRITE_TABLE_1 = 0x1000;

constexpr uint16_t BG_TABLE_0 = 0;
constexpr uint16_t BG_TABLE_1 = 0x1000;

union  PpuCtrl {
    // bits 0, 1
    struct CtrlData {
        uint8_t nametable_x : 1;

        uint8_t nametable_y : 1;

        // bit 2
        /* VRAM address increment per CPU read/write of PPUDATA */
        uint8_t vram_increment : 1;

        // bit 3
        /* Sprite pattern table address for 8x8 sprites
         * (0: $0000; 1: $1000; ignored in 8x16 mode) */
        uint8_t sprite_pattern_table : 1;

        // bit 4
        /* Background pattern table address (0: $0000; 1: $1000) */
        uint8_t background_pattern_table : 1;

        // bit 5
        /* Sprite size (0: 8x8 pixels; 1: 8x16 pixels – see PPU OAM#Byte 1) */
        uint8_t sprite_size : 1;

        // bit 6
        /* PPU master/slave select
         * (0: read backdrop from EXT pins; 1: output color on EXT pins) */
        uint8_t master_slave_select : 1;

        // bit 7
        /* Generate an NMI at the start of the
         * vertical blanking interval (0: off; 1: on) */
        bool generate_nmi : 1;
    } data;
    uint8_t reg;

    void deserialize(uint8_t value);
    uint8_t serialize() const;

    uint16_t get_base_nametable_address() const;
    uint8_t get_vram_increment() const;
    uint16_t get_sprite_pattern_address() const;
    uint16_t get_background_pattern_address() const;
};

} // namespace nes

#endif
