#include "ppu_status.hpp"

namespace nes {

void PpuStatus::deserialize(uint8_t data)
{
    sprite_overflow = (data >> 5) & 0x01;
    sprite_0_hit = (data >> 6) & 0x01;
    in_v_blank = (data >> 7) & 0x01;
}

uint8_t PpuStatus::serialize() const
{
    return
        sprite_overflow << 5 |
        sprite_0_hit << 6 |
        in_v_blank << 7;
}

} // namespace nes
