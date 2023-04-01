#include "ppu_ctrl.hpp"

namespace nes {

void PpuCtrl::deserialize(uint8_t data)
{
    nametable_base = data & 0x03;
    vram_increment = (data >> 2) & 1;
    sprite_pattern_table = (data >> 3) & 1;
    background_pattern_table = (data >> 4) & 1;
    sprite_size = (data >> 5) & 1;
    master_slave_select = (data >> 6) & 1;
    generate_nmi = (data >> 7) & 1;
}

uint8_t PpuCtrl::serialize() const
{
    return
        (nametable_base & 0x03) |
        (vram_increment & 1) << 2 |
        (sprite_pattern_table & 1) << 3 |
        (background_pattern_table & 1) << 4 |
        (sprite_size & 1) << 5 |
        (master_slave_select & 1) << 6 |
        (generate_nmi & 1) << 7;
}

uint16_t PpuCtrl::get_base_nametable_address() const
{
    switch (nametable_base & 0x03)
    {
    case 0:
        return 0x2000;
    case 1:
        return 0x2400;
    case 2:
        return 0x2800;
    case 3:
    default:
        return 0x2C00;
    };
}

uint8_t PpuCtrl::get_vram_increment() const
{
    return (vram_increment & 1) == 0 ? 1 : 32;
}

uint16_t PpuCtrl::get_sprite_pattern_address() const
{
    return (sprite_pattern_table & 1) == 0 ? 0 : 0x1000;
}

uint16_t PpuCtrl::get_background_pattern_address() const
{
    return (background_pattern_table & 1) == 0 ? 0 : 0x1000;
}

} // namespace nes
