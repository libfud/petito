#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <format>
#include <string>

#include "assembler.hpp"
#include "../logger/logger.hpp"

namespace mos6502 {

TEST(TestAssembler, FromFileName)
{
    logger::set_level(logger::LogLevel::Debug);
    logger::set_pattern("%v");
    auto result = Assembler::from_file_name("tests/asm/test_program_1.mos");
    if (result.is_err())
    {
        ASSERT_NE(result.get_err(), ParseError::FailedToLoad);
        std::cerr << std::format("Result is {}\n", static_cast<uint32_t>(result.get_err()));
    }
    ASSERT_TRUE(result.is_ok());
}

TEST(TestAssembler, Nop)
{
    OpName op_id = OpName::NOP;
    const std::string input = std::format("\t{}\n", opid_to_name(op_id));

    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    ASSERT_EQ(assembler.format(), input);
    ASSERT_EQ(assembler.size(), 1);
}

} // namespace mos6502
