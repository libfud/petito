#include "gtest/gtest.h"
#include "nes.hpp"
#include "logger/logger.hpp"

#include <algorithm>

namespace nes {

enum class NesState {
    Running,
    Passed,
    Failed
};

class TestNes : public ::testing::Test {
public:
    nes::Cartridge cart;
protected:
    TestNes() : cart{} {}

private:
};

TEST_F(TestNes, basic)
{
    // Cartridge cart{};
    auto res = cart.load("data/roms/instr_test_v5/01-basics.nes");
    ASSERT_TRUE(res);
    if (!res)
    {
        return;
    }

    NES nes(std::move(cart));
    NesState state = NesState::Running;
    int cycles = 0;
    logger::set_pattern("%v");
    logger::set_level(logger::LogLevel::Warn);
    auto terminator = [&](const NES& nes){
        auto has_debug_msg = nes.diagnostics();
        // passed substring
        if (nes.debug_msg.find("assed") != std::string::npos)
        {
            state = NesState::Passed;
            return false;
        }
        else if (nes.debug_msg.find("failed") != std::string::npos)
        {
            state = NesState::Failed;
            return false;
        }
        else
        {
            state = NesState::Running;
        }

        cycles++;
        if (cycles > 1000000000 || cycles < 0)
        {
            return state == NesState::Running;
        }

        return true;
    };
    nes.run_until(terminator);
    ASSERT_EQ(state, NesState::Passed);
}

} // namespace nes
