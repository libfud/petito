#ifndef PPU_MASK_HPP
#define PPU_MASK_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace nes {

union PpuMask
{
    struct PpuMaskData
    {
        uint8_t greyscale : 1;
        uint8_t show_bg_left : 1;
        uint8_t show_sprites_left : 1;
        uint8_t show_background : 1;
        uint8_t show_sprites : 1;
        uint8_t emphasize_red : 1;
        uint8_t emphasize_green : 1;
        uint8_t emphasize_blue : 1;
    } data;
    uint8_t reg;

    void deserialize(uint8_t value);
    uint8_t serialize() const;
    bool is_rendering() const;
};

} // namespace nes

#endif
