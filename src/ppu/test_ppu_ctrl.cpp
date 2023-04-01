#include "gtest/gtest.h"
#include "ppu_ctrl.hpp"

namespace nes {

TEST(TestPpuCtrl, serialize)
{
    PpuCtrl ctrl{};
    ASSERT_EQ(ctrl.serialize(), 0);

    ctrl.nametable_base = 1;
    ASSERT_EQ(ctrl.serialize(), 0x01);

    ctrl.nametable_base = 2;
    ASSERT_EQ(ctrl.serialize(), 0x02);

    ctrl.nametable_base = 3;
    ASSERT_EQ(ctrl.serialize(), 0x03);

    ctrl.nametable_base = 0;
    ctrl.vram_increment = 1;
    ASSERT_EQ(ctrl.serialize(), 0x04);

    ctrl.nametable_base = 3;
    ASSERT_EQ(ctrl.serialize(), 0x07);

    ctrl.sprite_pattern_table = 1;
    ctrl.nametable_base = 0;
    ctrl.vram_increment = 0;
    ASSERT_EQ(ctrl.serialize(), 0x08);

    ctrl.nametable_base = 3;
    ctrl.vram_increment = 1;
    ASSERT_EQ(ctrl.serialize(), 0x0F);

    ctrl.background_pattern_table = 1;
    ctrl.sprite_pattern_table = 0;
    ctrl.nametable_base = 0;
    ctrl.vram_increment = 0;
    ASSERT_EQ(ctrl.serialize(), 0x10);

    ctrl.nametable_base = 3;
    ctrl.vram_increment = 1;
    ctrl.sprite_pattern_table = 1;
    ASSERT_EQ(ctrl.serialize(), 0x1F);

    ctrl.nametable_base = 0;
    ctrl.vram_increment = 0;
    ctrl.sprite_pattern_table = 0;
    ctrl.background_pattern_table = 0;
    ctrl.sprite_size = 1;
    ASSERT_EQ(ctrl.serialize(), 0x20);

    ctrl.nametable_base = 3;
    ctrl.vram_increment = 1;
    ctrl.sprite_pattern_table = 1;
    ctrl.background_pattern_table = 1;
    ASSERT_EQ(ctrl.serialize(), 0x3F);

    ctrl.nametable_base = 0;
    ctrl.vram_increment = 0;
    ctrl.sprite_pattern_table = 0;
    ctrl.background_pattern_table = 0;
    ctrl.sprite_size = 0;
    ctrl.master_slave_select = 1;
    ASSERT_EQ(ctrl.serialize(), 0x40);

    ctrl.master_slave_select = 0;
    ctrl.generate_nmi = true;
    ASSERT_EQ(ctrl.serialize(), 0x80);

    ctrl.nametable_base = 3;
    ctrl.vram_increment = 1;
    ctrl.sprite_pattern_table = 1;
    ctrl.background_pattern_table = 1;
    ctrl.sprite_size = 1;
    ctrl.master_slave_select = 1;
    ctrl.generate_nmi = true;
    ASSERT_EQ(ctrl.serialize(), 0xFF);
}

TEST(TestPpuCtrl, deserialize)
{
    PpuCtrl ctrl{};
    ctrl.deserialize(0x00);
    ASSERT_EQ(ctrl.nametable_base, 0);
    ASSERT_EQ(ctrl.vram_increment, 0);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x01);
    ASSERT_EQ(ctrl.nametable_base, 1);
    ASSERT_EQ(ctrl.vram_increment, 0);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x02);
    ASSERT_EQ(ctrl.nametable_base, 2);
    ASSERT_EQ(ctrl.vram_increment, 0);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x03);
    ASSERT_EQ(ctrl.nametable_base, 3);
    ASSERT_EQ(ctrl.vram_increment, 0);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x04);
    ASSERT_EQ(ctrl.nametable_base, 0);
    ASSERT_EQ(ctrl.vram_increment, 1);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x07);
    ASSERT_EQ(ctrl.nametable_base, 3);
    ASSERT_EQ(ctrl.vram_increment, 1);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x08);
    ASSERT_EQ(ctrl.nametable_base, 0);
    ASSERT_EQ(ctrl.vram_increment, 0);
    ASSERT_EQ(ctrl.sprite_pattern_table, 1);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x0F);
    ASSERT_EQ(ctrl.nametable_base, 3);
    ASSERT_EQ(ctrl.vram_increment, 1);
    ASSERT_EQ(ctrl.sprite_pattern_table, 1);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x10);
    ASSERT_EQ(ctrl.nametable_base, 0);
    ASSERT_EQ(ctrl.vram_increment, 0);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 1);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x1F);
    ASSERT_EQ(ctrl.nametable_base, 3);
    ASSERT_EQ(ctrl.vram_increment, 1);
    ASSERT_EQ(ctrl.sprite_pattern_table, 1);
    ASSERT_EQ(ctrl.background_pattern_table, 1);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x20);
    ASSERT_EQ(ctrl.nametable_base, 0);
    ASSERT_EQ(ctrl.vram_increment, 0);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 1);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x3F);
    ASSERT_EQ(ctrl.nametable_base, 3);
    ASSERT_EQ(ctrl.vram_increment, 1);
    ASSERT_EQ(ctrl.sprite_pattern_table, 1);
    ASSERT_EQ(ctrl.background_pattern_table, 1);
    ASSERT_EQ(ctrl.sprite_size, 1);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x40);
    ASSERT_EQ(ctrl.nametable_base, 0);
    ASSERT_EQ(ctrl.vram_increment, 0);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 1);
    ASSERT_EQ(ctrl.generate_nmi, false);

    ctrl.deserialize(0x80);
    ASSERT_EQ(ctrl.nametable_base, 0);
    ASSERT_EQ(ctrl.vram_increment, 0);
    ASSERT_EQ(ctrl.sprite_pattern_table, 0);
    ASSERT_EQ(ctrl.background_pattern_table, 0);
    ASSERT_EQ(ctrl.sprite_size, 0);
    ASSERT_EQ(ctrl.master_slave_select, 0);
    ASSERT_EQ(ctrl.generate_nmi, true);

    ctrl.deserialize(0xFF);
    ASSERT_EQ(ctrl.nametable_base, 3);
    ASSERT_EQ(ctrl.vram_increment, 1);
    ASSERT_EQ(ctrl.sprite_pattern_table, 1);
    ASSERT_EQ(ctrl.background_pattern_table, 1);
    ASSERT_EQ(ctrl.sprite_size, 1);
    ASSERT_EQ(ctrl.master_slave_select, 1);
    ASSERT_EQ(ctrl.generate_nmi, true);
}

TEST(TestPpuCtrl, get_base_nametable_address)
{
    PpuCtrl ctrl{};
    ctrl.nametable_base = 0;
    ASSERT_EQ(ctrl.get_base_nametable_address(), NAMETABLE_0);

    ctrl.nametable_base = 1;
    ASSERT_EQ(ctrl.get_base_nametable_address(), NAMETABLE_1);

    ctrl.nametable_base = 2;
    ASSERT_EQ(ctrl.get_base_nametable_address(), NAMETABLE_2);

    ctrl.nametable_base = 3;
    ASSERT_EQ(ctrl.get_base_nametable_address(), NAMETABLE_3);
}

TEST(TestPpuCtrl, get_vram_increment)
{
    PpuCtrl ctrl{};
    ctrl.vram_increment = 0;
    ASSERT_EQ(ctrl.get_vram_increment(), VRAM_INCREMENT_ACROSS);

    ctrl.vram_increment = 1;
    ASSERT_EQ(ctrl.get_vram_increment(), VRAM_INCREMENT_DOWN);
}

TEST(TestPpuCtrl, get_sprite_pattern_address)
{
    PpuCtrl ctrl{};
    ctrl.sprite_pattern_table = 0;
    ASSERT_EQ(ctrl.get_sprite_pattern_address(), SPRITE_TABLE_0);

    ctrl.sprite_pattern_table = 1;
    ASSERT_EQ(ctrl.get_sprite_pattern_address(), SPRITE_TABLE_1);
}

TEST(TestPpuCtrl, get_background_pattern_address)
{
    PpuCtrl ctrl{};
    ctrl.background_pattern_table = 0;
    ASSERT_EQ(ctrl.get_background_pattern_address(), BG_TABLE_0);

    ctrl.background_pattern_table = 1;
    ASSERT_EQ(ctrl.get_background_pattern_address(), BG_TABLE_1);
}

} // namespace nes
