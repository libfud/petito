#ifndef PPU_CTRL_HPP
#define PPU_CTRL_HPP

#include <cstdint>

#include "ppu_register.hpp"

namespace nes {

struct PpuCtrl : public PpuRegister {
    // bits 0, 1
    /* Base nametable address
     * (0 = $2000; 1 = $2400; 2 = $2800; 3 = $2C00)
     */
    uint8_t nametable_base;

    // bit 2
    /* VRAM address increment per CPU read/write of PPUDATA
     * (0: add 1, going across; 1: add 32, going down) */
    uint8_t vram_increment;

    // bit 3
    /* Sprite pattern table address for 8x8 sprites
     * (0: $0000; 1: $1000; ignored in 8x16 mode) */
    uint8_t sprite_pattern_table;

    // bit 4
    /* Background pattern table address (0: $0000; 1: $1000) */
    uint8_t background_pattern_table;

    // bit 5
    /* Sprite size (0: 8x8 pixels; 1: 8x16 pixels – see PPU OAM#Byte 1) */
    uint8_t sprite_size;

    // bit 6
    /* PPU master/slave select
     * (0: read backdrop from EXT pins; 1: output color on EXT pins) */
    uint8_t master_slave_select;

    // bit 7
    /* Generate an NMI at the start of the
     * vertical blanking interval (0: off; 1: on) */
    bool generate_nmi;

    void deserialize(uint8_t data) override;
    uint8_t serialize() const override;

    uint16_t get_base_nametable_address() const;
    uint8_t get_vram_increment() const;
    uint16_t get_sprite_pattern_address() const;
    uint16_t get_background_pattern_address() const;
};

} // namespace nes

#endif
