#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <format>
#include <string>

#include "assembler.hpp"
#include "../logger/logger.hpp"

namespace mos6502 {

#if 0
TEST(TestInstruction, MakeInstruction)
{
    const auto op_id = OpName::NOP;
    const std::string& mnemonic = opid_to_name(op_id);
    std::string input{};
    TokenVector tokens{};

    input = mnemonic;
    auto tokens_result = Token::tokenize_line(input);
    ASSERT_TRUE(tokens_result.is_ok());
    tokens = std::move(tokens_result.get_ok());

    auto result = Instruction::make(tokens);
    ASSERT_TRUE(tokens_result.is_ok());
}
#endif

TEST(TestInstruction, FromFileName)
{
    logger::set_level(logger::LogLevel::Debug);
    logger::set_pattern("%v");
    auto result = Assembler::from_file_name("tests/asm/test_program_1.mos");
    if (result.is_err())
    {
        ASSERT_NE(result.get_err(), AsmError::FailedToLoad);
        std::cerr << std::format("Result is {}\n", static_cast<uint32_t>(result.get_err()));
    }
    ASSERT_TRUE(result.is_ok());
}

} // namespace mos6502
