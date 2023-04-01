#include "gtest/gtest.h"
#include "ppu_status.hpp"

namespace nes {

TEST(TestStatus, serialize)
{
    PpuStatus status{};
    ASSERT_EQ(status.serialize(), 0x00);

    status.sprite_overflow = true;
    status.sprite_0_hit = false;
    status.in_v_blank = false;
    ASSERT_EQ(status.serialize(), 0x20);

    status.sprite_overflow = false;
    status.sprite_0_hit = true;
    status.in_v_blank = false;
    ASSERT_EQ(status.serialize(), 0x40);

    status.sprite_overflow = false;
    status.sprite_0_hit = false;
    status.in_v_blank = true;
    ASSERT_EQ(status.serialize(), 0x80);

    status.sprite_overflow = true;
    status.sprite_0_hit = true;
    status.in_v_blank = true;
    ASSERT_EQ(status.serialize(), 0xE0);
}

TEST(TestStatus, deserialize)
{
    PpuStatus status{};
    status.deserialize(0);
    ASSERT_EQ(status.sprite_overflow, false);
    ASSERT_EQ(status.sprite_0_hit, false);
    ASSERT_EQ(status.in_v_blank, false);

    status.deserialize(0x20);
    ASSERT_EQ(status.sprite_overflow, true);
    ASSERT_EQ(status.sprite_0_hit, false);
    ASSERT_EQ(status.in_v_blank, false);

    status.deserialize(0x40);
    ASSERT_EQ(status.sprite_overflow, false);
    ASSERT_EQ(status.sprite_0_hit, true);
    ASSERT_EQ(status.in_v_blank, false);

    status.deserialize(0x80);
    ASSERT_EQ(status.sprite_overflow, false);
    ASSERT_EQ(status.sprite_0_hit, false);
    ASSERT_EQ(status.in_v_blank, true);

    status.deserialize(0xE0);
    ASSERT_EQ(status.sprite_overflow, true);
    ASSERT_EQ(status.sprite_0_hit, true);
    ASSERT_EQ(status.in_v_blank, true);
}

} // namespace nes
