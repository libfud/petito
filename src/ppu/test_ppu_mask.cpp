#include "gtest/gtest.h"
#include "ppu_mask.hpp"

namespace nes {

TEST(TestPpuMask, serialize)
{
    PpuMask mask{};
    ASSERT_EQ(mask.serialize(), 0x00);

    mask.data.greyscale = true;
    mask.data.show_bg_left = false;
    mask.data.show_sprites_left = false;
    mask.data.show_background = false;
    mask.data.show_sprites = false;
    mask.data.emphasize_red = false;
    mask.data.emphasize_green = false;
    mask.data.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x01);

    mask.data.greyscale = false;
    mask.data.show_bg_left = true;
    mask.data.show_sprites_left = false;
    mask.data.show_background = false;
    mask.data.show_sprites = false;
    mask.data.emphasize_red = false;
    mask.data.emphasize_green = false;
    mask.data.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x02);

    mask.data.greyscale = false;
    mask.data.show_bg_left = false;
    mask.data.show_sprites_left = true;
    mask.data.show_background = false;
    mask.data.show_sprites = false;
    mask.data.emphasize_red = false;
    mask.data.emphasize_green = false;
    mask.data.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x04);

    mask.data.greyscale = false;
    mask.data.show_bg_left = false;
    mask.data.show_sprites_left = false;
    mask.data.show_background = true;
    mask.data.show_sprites = false;
    mask.data.emphasize_red = false;
    mask.data.emphasize_green = false;
    mask.data.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x08);

    mask.data.greyscale = false;
    mask.data.show_bg_left = false;
    mask.data.show_sprites_left = false;
    mask.data.show_background = false;
    mask.data.show_sprites = true;
    mask.data.emphasize_red = false;
    mask.data.emphasize_green = false;
    mask.data.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x10);

    mask.data.greyscale = false;
    mask.data.show_bg_left = false;
    mask.data.show_sprites_left = false;
    mask.data.show_background = false;
    mask.data.show_sprites = false;
    mask.data.emphasize_red = true;
    mask.data.emphasize_green = false;
    mask.data.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x20);

    mask.data.greyscale = false;
    mask.data.show_bg_left = false;
    mask.data.show_sprites_left = false;
    mask.data.show_background = false;
    mask.data.show_sprites = false;
    mask.data.emphasize_red = false;
    mask.data.emphasize_green = true;
    mask.data.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x40);

    mask.data.greyscale = false;
    mask.data.show_bg_left = false;
    mask.data.show_sprites_left = false;
    mask.data.show_background = false;
    mask.data.show_sprites = false;
    mask.data.emphasize_red = false;
    mask.data.emphasize_green = false;
    mask.data.emphasize_blue = true;
    ASSERT_EQ(mask.serialize(), 0x80);

    mask.data.greyscale = true;
    mask.data.show_bg_left = true;
    mask.data.show_sprites_left = true;
    mask.data.show_background = true;
    mask.data.show_sprites = true;
    mask.data.emphasize_red = true;
    mask.data.emphasize_green = true;
    mask.data.emphasize_blue = true;
    ASSERT_EQ(mask.serialize(), 0xFF);
}

TEST(TestPpuMask, deserialize)
{
    PpuMask mask{};
    ASSERT_EQ(mask.serialize(), 0x00);

    mask.deserialize(0x01);
    ASSERT_EQ(mask.data.greyscale, true);
    ASSERT_EQ(mask.data.show_bg_left, false);
    ASSERT_EQ(mask.data.show_sprites_left, false);
    ASSERT_EQ(mask.data.show_background, false);
    ASSERT_EQ(mask.data.show_sprites, false);
    ASSERT_EQ(mask.data.emphasize_red, false);
    ASSERT_EQ(mask.data.emphasize_green, false);
    ASSERT_EQ(mask.data.emphasize_blue, false);

    mask.deserialize(0x02);
    ASSERT_EQ(mask.data.greyscale, false);
    ASSERT_EQ(mask.data.show_bg_left, true);
    ASSERT_EQ(mask.data.show_sprites_left, false);
    ASSERT_EQ(mask.data.show_background, false);
    ASSERT_EQ(mask.data.show_sprites, false);
    ASSERT_EQ(mask.data.emphasize_red, false);
    ASSERT_EQ(mask.data.emphasize_green, false);
    ASSERT_EQ(mask.data.emphasize_blue, false);

    mask.deserialize(0x04);
    ASSERT_EQ(mask.data.greyscale, false);
    ASSERT_EQ(mask.data.show_bg_left, false);
    ASSERT_EQ(mask.data.show_sprites_left, true);
    ASSERT_EQ(mask.data.show_background, false);
    ASSERT_EQ(mask.data.show_sprites, false);
    ASSERT_EQ(mask.data.emphasize_red, false);
    ASSERT_EQ(mask.data.emphasize_green, false);
    ASSERT_EQ(mask.data.emphasize_blue, false);

    mask.deserialize(0x08);
    ASSERT_EQ(mask.data.greyscale, false);
    ASSERT_EQ(mask.data.show_bg_left, false);
    ASSERT_EQ(mask.data.show_sprites_left, false);
    ASSERT_EQ(mask.data.show_background, true);
    ASSERT_EQ(mask.data.show_sprites, false);
    ASSERT_EQ(mask.data.emphasize_red, false);
    ASSERT_EQ(mask.data.emphasize_green, false);
    ASSERT_EQ(mask.data.emphasize_blue, false);

    mask.deserialize(0x10);
    ASSERT_EQ(mask.data.greyscale, false);
    ASSERT_EQ(mask.data.show_bg_left, false);
    ASSERT_EQ(mask.data.show_sprites_left, false);
    ASSERT_EQ(mask.data.show_background, false);
    ASSERT_EQ(mask.data.show_sprites, true);
    ASSERT_EQ(mask.data.emphasize_red, false);
    ASSERT_EQ(mask.data.emphasize_green, false);
    ASSERT_EQ(mask.data.emphasize_blue, false);

    mask.deserialize(0x20);
    ASSERT_EQ(mask.data.greyscale, false);
    ASSERT_EQ(mask.data.show_bg_left, false);
    ASSERT_EQ(mask.data.show_sprites_left, false);
    ASSERT_EQ(mask.data.show_background, false);
    ASSERT_EQ(mask.data.show_sprites, false);
    ASSERT_EQ(mask.data.emphasize_red, true);
    ASSERT_EQ(mask.data.emphasize_green, false);
    ASSERT_EQ(mask.data.emphasize_blue, false);

    mask.deserialize(0x40);
    ASSERT_EQ(mask.data.greyscale, false);
    ASSERT_EQ(mask.data.show_bg_left, false);
    ASSERT_EQ(mask.data.show_sprites_left, false);
    ASSERT_EQ(mask.data.show_background, false);
    ASSERT_EQ(mask.data.show_sprites, false);
    ASSERT_EQ(mask.data.emphasize_red, false);
    ASSERT_EQ(mask.data.emphasize_green, true);
    ASSERT_EQ(mask.data.emphasize_blue, false);

    mask.deserialize(0x80);
    ASSERT_EQ(mask.data.greyscale, false);
    ASSERT_EQ(mask.data.show_bg_left, false);
    ASSERT_EQ(mask.data.show_sprites_left, false);
    ASSERT_EQ(mask.data.show_background, false);
    ASSERT_EQ(mask.data.show_sprites, false);
    ASSERT_EQ(mask.data.emphasize_red, false);
    ASSERT_EQ(mask.data.emphasize_green, false);
    ASSERT_EQ(mask.data.emphasize_blue, true);

    mask.deserialize(0xFF);
    ASSERT_EQ(mask.data.greyscale, true);
    ASSERT_EQ(mask.data.show_bg_left, true);
    ASSERT_EQ(mask.data.show_sprites_left, true);
    ASSERT_EQ(mask.data.show_background, true);
    ASSERT_EQ(mask.data.show_sprites, true);
    ASSERT_EQ(mask.data.emphasize_red, true);
    ASSERT_EQ(mask.data.emphasize_green, true);
    ASSERT_EQ(mask.data.emphasize_blue, true);
}

TEST(TestPpuMask, is_rendering)
{
    PpuMask mask{{0}};
    ASSERT_EQ(mask.data.show_background, 0);
    ASSERT_EQ(mask.data.show_sprites, 0);
    ASSERT_FALSE(mask.is_rendering());

    mask.data.show_background = 1;
    mask.data.show_sprites = 0;
    ASSERT_TRUE(mask.is_rendering());

    mask.data.show_background = 0;
    mask.data.show_sprites = 1;
    ASSERT_TRUE(mask.is_rendering());

    mask.data.show_background = 1;
    mask.data.show_sprites = 1;
    ASSERT_TRUE(mask.is_rendering());
}

} // namespace nes
