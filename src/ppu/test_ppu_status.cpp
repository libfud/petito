#include "gtest/gtest.h"
#include "ppu_status.hpp"

namespace nes {

TEST(TestStatus, serialize)
{
    PpuStatus status{};
    ASSERT_EQ(status.serialize(), 0x00);

    status.data.sprite_overflow = true;
    status.data.sprite_0_hit = false;
    status.data.in_v_blank = false;
    ASSERT_EQ(status.serialize(), 0x20);

    status.data.sprite_overflow = false;
    status.data.sprite_0_hit = true;
    status.data.in_v_blank = false;
    ASSERT_EQ(status.serialize(), 0x40);

    status.data.sprite_overflow = false;
    status.data.sprite_0_hit = false;
    status.data.in_v_blank = true;
    ASSERT_EQ(status.serialize(), 0x80);

    status.data.sprite_overflow = true;
    status.data.sprite_0_hit = true;
    status.data.in_v_blank = true;
    ASSERT_EQ(status.serialize(), 0xE0);
}

TEST(TestStatus, deserialize)
{
    PpuStatus status{};
    status.deserialize(0);
    ASSERT_EQ(status.data.sprite_overflow, false);
    ASSERT_EQ(status.data.sprite_0_hit, false);
    ASSERT_EQ(status.data.in_v_blank, false);

    status.deserialize(0x20);
    ASSERT_EQ(status.data.sprite_overflow, true);
    ASSERT_EQ(status.data.sprite_0_hit, false);
    ASSERT_EQ(status.data.in_v_blank, false);

    status.deserialize(0x40);
    ASSERT_EQ(status.data.sprite_overflow, false);
    ASSERT_EQ(status.data.sprite_0_hit, true);
    ASSERT_EQ(status.data.in_v_blank, false);

    status.deserialize(0x80);
    ASSERT_EQ(status.data.sprite_overflow, false);
    ASSERT_EQ(status.data.sprite_0_hit, false);
    ASSERT_EQ(status.data.in_v_blank, true);

    status.deserialize(0xE0);
    ASSERT_EQ(status.data.sprite_overflow, true);
    ASSERT_EQ(status.data.sprite_0_hit, true);
    ASSERT_EQ(status.data.in_v_blank, true);
}

} // namespace nes
