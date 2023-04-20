#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <string>

#include "mos6502.hpp"

namespace mos6502 {

using CpuType = MOS6502;

TEST(TestFlags, get)
{
    Flags flags{};
    EXPECT_EQ(flags.get(), BRK_MASK);
    EXPECT_EQ(flags.get(), (1 << 5) | (0 << 4));
    EXPECT_EQ(flags.get_php(), (1 << 5) | (1 << 4));

    flags.brk = true;
    EXPECT_EQ(flags.get(), (1 << 5) | (1 << 4));
    EXPECT_EQ(flags.get_php(), (1 << 5) | (1 << 4));

    flags.carry = true;

    EXPECT_EQ(flags.get(), (1 << 5) | (1 << 4) | 1);
    EXPECT_EQ(flags.get_php(), (1 << 5) | (1 << 4) | 1);

    flags.zero = true;

    EXPECT_EQ(flags.get(), (1 << 5) | (1 << 4) | (1 << 1) | 1);
    EXPECT_EQ(flags.get_php(), (1 << 5) | (1 << 4) | (1 << 1) | 1);

    flags.interrupt_inhibit = true;
    flags.bcd_arithmetic = true;
    flags.brk = true;
    flags.overflow = true;
    flags.negative = true;

    EXPECT_EQ(flags.get(), 0xFF);
    EXPECT_EQ(flags.get_php(), 0xFF);

    flags.brk = false;
    EXPECT_EQ(flags.get(), 0xFF - (1 << 4));
    EXPECT_EQ(flags.get_php(), 0xFF);
}

} // namespace mos6502
