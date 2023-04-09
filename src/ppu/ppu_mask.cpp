#include "ppu_mask.hpp"

namespace nes {

void PpuMask::deserialize(uint8_t value)
{
    reg = value;
}

uint8_t PpuMask::serialize() const
{
    return reg;
}

bool PpuMask::is_rendering() const
{
    // #b00011000 24
    // #x18 24
    return (reg & 0x18) > 0;
}

} // namespace nes
