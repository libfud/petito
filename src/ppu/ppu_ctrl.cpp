#include "ppu_ctrl.hpp"

namespace nes {

void PpuCtrl::deserialize(uint8_t value)
{
    reg = value;
}

uint8_t PpuCtrl::serialize() const
{
    return reg;
}

uint16_t PpuCtrl::get_base_nametable_address() const
{
    constexpr auto diff = NAMETABLE_1 - NAMETABLE_0;
    auto value = reg & 0x03;
    return NAMETABLE_0 + diff * value;
}

uint8_t PpuCtrl::get_vram_increment() const
{
    return data.vram_increment == 0 ? VRAM_INCREMENT_ACROSS : VRAM_INCREMENT_DOWN;
}

uint16_t PpuCtrl::get_sprite_pattern_address() const
{
    return data.sprite_pattern_table == 0 ? SPRITE_TABLE_0 : SPRITE_TABLE_1;
}

uint16_t PpuCtrl::get_background_pattern_address() const
{
    return data.background_pattern_table == 0 ? BG_TABLE_0: BG_TABLE_1;
}

} // namespace nes
