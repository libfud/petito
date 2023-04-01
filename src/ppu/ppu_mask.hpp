#ifndef PPU_MASK_HPP
#define PPU_MASK_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "ppu_register.hpp"

namespace nes {

struct PpuMask : public PpuRegister
{
    bool greyscale;
    bool show_bg_left;
    bool show_sprites_left;
    bool show_background;
    bool show_sprites;
    bool emphasize_red;
    bool emphasize_green;
    bool emphasize_blue;

    void deserialize(uint8_t data) override;
    uint8_t serialize() const override;
};

} // namespace nes

#endif
