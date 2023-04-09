#include "ppu_status.hpp"

namespace nes {

void PpuStatus::deserialize(uint8_t value)
{
    data.sprite_overflow = (value >> 5) & 0x01;
    data.sprite_0_hit = (value >> 6) & 0x01;
    data.in_v_blank = (value >> 7) & 0x01;
}

uint8_t PpuStatus::serialize() const
{
    return reg & 0xE0;
    return
        data.sprite_overflow << 5 |
        data.sprite_0_hit << 6 |
        data.in_v_blank << 7;
}

} // namespace nes
