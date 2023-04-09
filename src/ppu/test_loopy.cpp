#include "gtest/gtest.h"
#include "loopy_register.hpp"

namespace nes {

TEST(TestLoopyRegister, SetData)
{
    LoopyRegister loopyReg{};
    loopyReg.set(0x001F);
    ASSERT_EQ(loopyReg.data.coarse_x, 0x1F);
    ASSERT_EQ(loopyReg.get(), 0x001F);

    loopyReg.set(0x1F << 5);
    ASSERT_EQ(loopyReg.data.coarse_x, 0);
    ASSERT_EQ(loopyReg.data.coarse_y, 0x1F);
    ASSERT_EQ(loopyReg.get(), 0x001F << 5);

    loopyReg.set((0x1F << 5) | 0x1F);
    ASSERT_EQ(loopyReg.data.coarse_x, 0x1F);
    ASSERT_EQ(loopyReg.data.coarse_y, 0x1F);
    ASSERT_EQ(loopyReg.get(), (0x001F << 5) | 0x001F);

    loopyReg.set(1 << 10);
    ASSERT_EQ(loopyReg.data.coarse_x, 0);
    ASSERT_EQ(loopyReg.data.coarse_y, 0);
    ASSERT_EQ(loopyReg.data.nametable_x, 1);
    ASSERT_EQ(loopyReg.data.nametable_y, 0);
    ASSERT_EQ(loopyReg.data.fine_y, 0);
    ASSERT_EQ(loopyReg.get(), 1 << 10);

    loopyReg.set(1 << 11);
    ASSERT_EQ(loopyReg.data.coarse_x, 0);
    ASSERT_EQ(loopyReg.data.coarse_y, 0);
    ASSERT_EQ(loopyReg.data.nametable_x, 0);
    ASSERT_EQ(loopyReg.data.nametable_y, 1);
    ASSERT_EQ(loopyReg.data.fine_y, 0);
    ASSERT_EQ(loopyReg.get(), 1 << 11);

    loopyReg.set(0x07 << 12);
    ASSERT_EQ(loopyReg.data.coarse_x, 0);
    ASSERT_EQ(loopyReg.data.coarse_y, 0);
    ASSERT_EQ(loopyReg.data.nametable_x, 0);
    ASSERT_EQ(loopyReg.data.nametable_y, 0);
    ASSERT_EQ(loopyReg.data.fine_y, 7);
    ASSERT_EQ(loopyReg.get(), 0x07 << 12);

    loopyReg.set(0xFFFF);
    ASSERT_EQ(loopyReg.data.coarse_x, 0x1F);
    ASSERT_EQ(loopyReg.data.coarse_y, 0x1F);
    ASSERT_EQ(loopyReg.data.nametable_x, 1);
    ASSERT_EQ(loopyReg.data.nametable_y, 1);
    ASSERT_EQ(loopyReg.data.fine_y, 0x07);
    ASSERT_EQ(loopyReg.get(), 0x7FFF);

    loopyReg.set(0x0);
    ASSERT_EQ(loopyReg.data.coarse_x, 0);
    ASSERT_EQ(loopyReg.data.coarse_y, 0);
    ASSERT_EQ(loopyReg.data.nametable_x, 0);
    ASSERT_EQ(loopyReg.data.nametable_y, 0);
    ASSERT_EQ(loopyReg.data.fine_y, 0);
    ASSERT_EQ(loopyReg.get(), 0);

    loopyReg.data.coarse_x = 0x1F;
    loopyReg.data.coarse_y = 0x1F;
    loopyReg.data.nametable_x = 0x01;
    loopyReg.data.nametable_y = 0x01;
    loopyReg.data.fine_y = 0x07;
    ASSERT_EQ(loopyReg.get(), 0x7FFF);
}

}
