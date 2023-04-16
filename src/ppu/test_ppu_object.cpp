#include "gtest/gtest.h"
#include "ppu_object.hpp"

namespace nes {

TEST(TestPpuObject, basic)
{
    ObjectAttributeEntry entry{};
    ASSERT_EQ(entry.y_pos(), 0);
}

} // namespace nes
