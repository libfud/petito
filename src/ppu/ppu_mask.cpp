#include "ppu_mask.hpp"

namespace nes {

void PpuMask::deserialize(uint8_t data)
{
    greyscale = data & 0x01;
    show_bg_left = (data >> 1) & 0x01;
    show_sprites_left = (data >> 2) & 0x01;
    show_background = (data >> 3) & 0x01;
    show_sprites = (data >> 4) & 0x01;
    emphasize_red = (data >> 5) & 0x01;
    emphasize_green = (data >> 6) & 0x01;
    emphasize_blue = (data >> 7) & 0x01;
}

uint8_t PpuMask::serialize() const
{
    return
        greyscale |
        show_bg_left << 1 |
        show_sprites_left << 2 |
        show_background << 3 |
        show_sprites << 4 |
        emphasize_red << 5 |
        emphasize_green << 6 |
        emphasize_blue << 7;
}

} // namespace nes
