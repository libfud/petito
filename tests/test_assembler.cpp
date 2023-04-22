#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <format>
#include <string>

#include "assembler.hpp"

namespace mos6502 {

TEST(TestToken, TestEmpty)
{
    std::string input{""};
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    EXPECT_EQ(tokens.size(), 0);
}

TEST(TestToken, SimpleLabel)
{
    const auto test_label{"reset_procedure"};
    /*
    input = {"not_label"};
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    EXPECT_EQ(tokens.size(), 0);
    */

    std::string input{};
    input = std::format("{}:", test_label);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Label);
    ASSERT_EQ(std::get<token::Label>(token.get()).value, test_label);

    input = std::format("{}: ", test_label);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Label);
    ASSERT_EQ(std::get<token::Label>(token.get()).value, test_label);

    /* This should be a combined test */
    /*
    input = std::format("{}: ;; Comment", test_label);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Label);
    ASSERT_EQ(std::get<token::Label>(token.get()).value, test_label);
    */
}

TEST(TestToken, TestComment)
{
    const auto comment = "Commentary. ; A message.";
    std::string input{};

    input = std::format(";; {}", comment);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Comment);
    ASSERT_EQ(std::get<token::Comment>(token.get()).value, comment);

    input = std::format(";; {} ", comment);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Comment);
    ASSERT_EQ(std::get<token::Comment>(token.get()).value, comment);

    input = std::format(";; {} ;;;  ", comment);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Comment);
    ASSERT_EQ(std::get<token::Comment>(token.get()).value, std::format("{} ;;;", comment));
}

TEST(TestToken, TestMnemonic)
{
    const auto mnemonic = "NOP";
    std::string input{};

    input = mnemonic;
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, OpName::NOP);
}

} // namespace mos6502
