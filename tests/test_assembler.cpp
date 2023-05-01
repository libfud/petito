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
    auto assembler = result.get_ok();
}

TEST(TestAssembler, Nop)
{
    OpName op_id = OpName::NOP;
    const std::string input = std::format("\t{}\n", opid_to_name(op_id));

    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.format(), input);
    EXPECT_EQ(assembler.size(), 1);
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), 1);
    EXPECT_EQ(prog_bytes[0], NOP_IMPL);
}

TEST(TestAssembler, LDA_IMM)
{
    OpName op_id = OpName::LDA;
    uint8_t value = 42;
    const std::string input = std::format("\t{} #${:02X}\n", opid_to_name(op_id), value);

    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.format(), input);
    EXPECT_EQ(assembler.size(), 2);
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), 2);
    EXPECT_EQ(prog_bytes[0], LDA_IMM);
    EXPECT_EQ(prog_bytes[1], value);
}


} // namespace mos6502
