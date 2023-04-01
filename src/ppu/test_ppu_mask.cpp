#include "gtest/gtest.h"
#include "ppu_mask.hpp"

namespace nes {

TEST(TestPpuMask, serialize)
{
    PpuMask mask{};
    ASSERT_EQ(mask.serialize(), 0x00);

    mask.greyscale = true;
    mask.show_bg_left = false;
    mask.show_sprites_left = false;
    mask.show_background = false;
    mask.show_sprites = false;
    mask.emphasize_red = false;
    mask.emphasize_green = false;
    mask.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x01);

    mask.greyscale = false;
    mask.show_bg_left = true;
    mask.show_sprites_left = false;
    mask.show_background = false;
    mask.show_sprites = false;
    mask.emphasize_red = false;
    mask.emphasize_green = false;
    mask.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x02);

    mask.greyscale = false;
    mask.show_bg_left = false;
    mask.show_sprites_left = true;
    mask.show_background = false;
    mask.show_sprites = false;
    mask.emphasize_red = false;
    mask.emphasize_green = false;
    mask.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x04);

    mask.greyscale = false;
    mask.show_bg_left = false;
    mask.show_sprites_left = false;
    mask.show_background = true;
    mask.show_sprites = false;
    mask.emphasize_red = false;
    mask.emphasize_green = false;
    mask.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x08);

    mask.greyscale = false;
    mask.show_bg_left = false;
    mask.show_sprites_left = false;
    mask.show_background = false;
    mask.show_sprites = true;
    mask.emphasize_red = false;
    mask.emphasize_green = false;
    mask.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x10);

    mask.greyscale = false;
    mask.show_bg_left = false;
    mask.show_sprites_left = false;
    mask.show_background = false;
    mask.show_sprites = false;
    mask.emphasize_red = true;
    mask.emphasize_green = false;
    mask.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x20);

    mask.greyscale = false;
    mask.show_bg_left = false;
    mask.show_sprites_left = false;
    mask.show_background = false;
    mask.show_sprites = false;
    mask.emphasize_red = false;
    mask.emphasize_green = true;
    mask.emphasize_blue = false;
    ASSERT_EQ(mask.serialize(), 0x40);

    mask.greyscale = false;
    mask.show_bg_left = false;
    mask.show_sprites_left = false;
    mask.show_background = false;
    mask.show_sprites = false;
    mask.emphasize_red = false;
    mask.emphasize_green = false;
    mask.emphasize_blue = true;
    ASSERT_EQ(mask.serialize(), 0x80);

    mask.greyscale = true;
    mask.show_bg_left = true;
    mask.show_sprites_left = true;
    mask.show_background = true;
    mask.show_sprites = true;
    mask.emphasize_red = true;
    mask.emphasize_green = true;
    mask.emphasize_blue = true;
    ASSERT_EQ(mask.serialize(), 0xFF);
}

TEST(TestPpuMask, deserialize)
{
    PpuMask mask{};
    ASSERT_EQ(mask.serialize(), 0x00);

    mask.deserialize(0x01);
    ASSERT_EQ(mask.greyscale, true);
    ASSERT_EQ(mask.show_bg_left, false);
    ASSERT_EQ(mask.show_sprites_left, false);
    ASSERT_EQ(mask.show_background, false);
    ASSERT_EQ(mask.show_sprites, false);
    ASSERT_EQ(mask.emphasize_red, false);
    ASSERT_EQ(mask.emphasize_green, false);
    ASSERT_EQ(mask.emphasize_blue, false);

    mask.deserialize(0x02);
    ASSERT_EQ(mask.greyscale, false);
    ASSERT_EQ(mask.show_bg_left, true);
    ASSERT_EQ(mask.show_sprites_left, false);
    ASSERT_EQ(mask.show_background, false);
    ASSERT_EQ(mask.show_sprites, false);
    ASSERT_EQ(mask.emphasize_red, false);
    ASSERT_EQ(mask.emphasize_green, false);
    ASSERT_EQ(mask.emphasize_blue, false);

    mask.deserialize(0x04);
    ASSERT_EQ(mask.greyscale, false);
    ASSERT_EQ(mask.show_bg_left, false);
    ASSERT_EQ(mask.show_sprites_left, true);
    ASSERT_EQ(mask.show_background, false);
    ASSERT_EQ(mask.show_sprites, false);
    ASSERT_EQ(mask.emphasize_red, false);
    ASSERT_EQ(mask.emphasize_green, false);
    ASSERT_EQ(mask.emphasize_blue, false);

    mask.deserialize(0x08);
    ASSERT_EQ(mask.greyscale, false);
    ASSERT_EQ(mask.show_bg_left, false);
    ASSERT_EQ(mask.show_sprites_left, false);
    ASSERT_EQ(mask.show_background, true);
    ASSERT_EQ(mask.show_sprites, false);
    ASSERT_EQ(mask.emphasize_red, false);
    ASSERT_EQ(mask.emphasize_green, false);
    ASSERT_EQ(mask.emphasize_blue, false);

    mask.deserialize(0x10);
    ASSERT_EQ(mask.greyscale, false);
    ASSERT_EQ(mask.show_bg_left, false);
    ASSERT_EQ(mask.show_sprites_left, false);
    ASSERT_EQ(mask.show_background, false);
    ASSERT_EQ(mask.show_sprites, true);
    ASSERT_EQ(mask.emphasize_red, false);
    ASSERT_EQ(mask.emphasize_green, false);
    ASSERT_EQ(mask.emphasize_blue, false);

    mask.deserialize(0x20);
    ASSERT_EQ(mask.greyscale, false);
    ASSERT_EQ(mask.show_bg_left, false);
    ASSERT_EQ(mask.show_sprites_left, false);
    ASSERT_EQ(mask.show_background, false);
    ASSERT_EQ(mask.show_sprites, false);
    ASSERT_EQ(mask.emphasize_red, true);
    ASSERT_EQ(mask.emphasize_green, false);
    ASSERT_EQ(mask.emphasize_blue, false);

    mask.deserialize(0x40);
    ASSERT_EQ(mask.greyscale, false);
    ASSERT_EQ(mask.show_bg_left, false);
    ASSERT_EQ(mask.show_sprites_left, false);
    ASSERT_EQ(mask.show_background, false);
    ASSERT_EQ(mask.show_sprites, false);
    ASSERT_EQ(mask.emphasize_red, false);
    ASSERT_EQ(mask.emphasize_green, true);
    ASSERT_EQ(mask.emphasize_blue, false);

    mask.deserialize(0x80);
    ASSERT_EQ(mask.greyscale, false);
    ASSERT_EQ(mask.show_bg_left, false);
    ASSERT_EQ(mask.show_sprites_left, false);
    ASSERT_EQ(mask.show_background, false);
    ASSERT_EQ(mask.show_sprites, false);
    ASSERT_EQ(mask.emphasize_red, false);
    ASSERT_EQ(mask.emphasize_green, false);
    ASSERT_EQ(mask.emphasize_blue, true);

    mask.deserialize(0xFF);
    ASSERT_EQ(mask.greyscale, true);
    ASSERT_EQ(mask.show_bg_left, true);
    ASSERT_EQ(mask.show_sprites_left, true);
    ASSERT_EQ(mask.show_background, true);
    ASSERT_EQ(mask.show_sprites, true);
    ASSERT_EQ(mask.emphasize_red, true);
    ASSERT_EQ(mask.emphasize_green, true);
    ASSERT_EQ(mask.emphasize_blue, true);
}

} // namespace nes
