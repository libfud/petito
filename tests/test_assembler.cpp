#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <format>
#include <string>

#include "assembler.hpp"

namespace mos6502 {

TEST(TestNumberParser, CheckNumericPrefix)
{
    std::string input{""};
    auto result = check_numeric_prefix(input, 0);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), NumberParseError::InvalidIndex);

    struct TestInput {
        std::string input;
        size_t prefix_length;
    };

    input = "g";
    result = check_numeric_prefix(input, 0);
    ASSERT_TRUE(result.is_ok());
    ASSERT_EQ(result.get_ok(), std::nullopt);

    std::vector<TestInput> hex_prefixes{{"$", 1}, {"&", 1}, {"0x", 2}};
    std::vector<TestInput> decimal_prefixes{{"1", 0}, {"0d", 2}, {"0d134", 2}};
    std::vector<TestInput> octal_prefixes{{"0", 0}, {"00", 1}, {"01", 1}, {"0o", 2}, {"@", 1}};
    std::vector<TestInput> binary_prefixes{{"%", 1}, {"0b", 2}};

    for (const auto& test_input :  hex_prefixes)
    {
        result = check_numeric_prefix(test_input.input, 0);
        ASSERT_TRUE(result.is_ok());
        auto output_option = result.get_ok();
        ASSERT_NE(output_option, std::nullopt);
        auto output = output_option.value();
        ASSERT_EQ(output.base, Base::Hex);
        ASSERT_EQ(output.length, test_input.prefix_length);
    }

    for (const auto& test_input :  decimal_prefixes)
    {
        result = check_numeric_prefix(test_input.input, 0);
        ASSERT_TRUE(result.is_ok());
        auto output_option = result.get_ok();
        ASSERT_NE(output_option, std::nullopt);
        auto output = output_option.value();
        ASSERT_EQ(output.base, Base::Decimal);
        ASSERT_EQ(output.length, test_input.prefix_length);
    }

    for (const auto& test_input :  octal_prefixes)
    {
        result = check_numeric_prefix(test_input.input, 0);
        ASSERT_TRUE(result.is_ok()) << test_input.input;
        auto output_option = result.get_ok();
        ASSERT_NE(output_option, std::nullopt);
        auto output = output_option.value();
        ASSERT_EQ(output.base, Base::Octal);
        ASSERT_EQ(output.length, test_input.prefix_length);
    }

    for (const auto& test_input :  binary_prefixes)
    {
        result = check_numeric_prefix(test_input.input, 0);
        ASSERT_TRUE(result.is_ok());
        auto output_option = result.get_ok();
        ASSERT_NE(output_option, std::nullopt);
        auto output = output_option.value();
        ASSERT_EQ(output.base, Base::Binary);
        ASSERT_EQ(output.length, test_input.prefix_length);
    }

    input = "1234567890";
    result = check_numeric_prefix(input, 0);
    ASSERT_TRUE(result.is_ok());
    auto output_option = result.get_ok();
    ASSERT_NE(output_option, std::nullopt);
    auto output = output_option.value();
    ASSERT_EQ(output.base, Base::Decimal);
    ASSERT_EQ(output.length, 0);

    input = "1g";
    result = check_numeric_prefix(input, 0);
    ASSERT_TRUE(result.is_ok());
    output_option = result.get_ok();
    ASSERT_NE(output_option, std::nullopt);
    output = output_option.value();
    ASSERT_EQ(output.base, Base::Decimal);
    ASSERT_EQ(output.length, 0);

    input = "0g";
    result = check_numeric_prefix(input, 0);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), NumberParseError::InvalidZeroPrefix);
}

TEST(TestNumberParser, EmptyString)
{
    std::string input{};
    size_t length{};

    input = "";
    length = 0;
    auto res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_err());
    EXPECT_EQ(res.get_err(), NumberParseError::InvalidIndex);
}

TEST(TestNumberParser, NullOpt)
{
    std::string input{};
    size_t length{};

    input = " ";
    length = 0;
    auto res = make_number(input, 0, length);
    EXPECT_EQ(length, 0);
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), std::nullopt);
}

TEST(TestNumberParser, MakeNumberDecimal)
{
    std::string input{};
    int32_t num{};
    size_t length{};

    num = 1;
    input = std::format("{}", num);
    length = 0;
    auto res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 10;
    input = std::format("{}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 120;
    input = std::format("{}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("{}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("0d{}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 255;
    input = std::format("{},X", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length() - 2);
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 255;
    input = std::format("({}),Y", num);
    length = 0;
    res = make_number(input, 1, length);
    EXPECT_EQ(length, std::format("{}", num).length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 10;
    input = std::format("{}A", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, 0);
    ASSERT_TRUE(res.is_err());
    EXPECT_EQ(res.get_err(), NumberParseError::InvalidDigit);
}

TEST(TestNumberParser, MakeNumberOctal)
{
    std::string input{};
    int32_t num{};
    size_t length{};

    num = 1;
    input = std::format("0{:o}", num);
    length = 0;
    auto res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1;
    input = std::format("@{}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1;
    input = std::format("0o{}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 0;
    input = std::format("{}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("0{:011o}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("@{:011o}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("0o{:011o}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 19;
    input = std::format("0{}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, 0);
    ASSERT_TRUE(res.is_err());
    EXPECT_EQ(res.get_err(), NumberParseError::InvalidDigit);
}

TEST(TestNumberParser, MakeNumberHex)
{
    std::string input{};
    int32_t num{};
    size_t length{};

    num = 1;
    input = std::format("&{:X}", num);
    length = 0;
    auto res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1;
    input = std::format("${:X}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1;
    input = std::format("0x{:X}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("${:08X}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("&{:08x}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("(${:08X},X)", num);
    length = 0;
    res = make_number(input, 1, length);
    EXPECT_EQ(length, input.length() - 4);
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 15;
    input = std::format("0x{}g", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, 0);
    ASSERT_TRUE(res.is_err());
    EXPECT_EQ(res.get_err(), NumberParseError::InvalidDigit);
}

TEST(TestNumberParser, MakeNumberBinary)
{
    std::string input{};
    int32_t num{};
    size_t length{};

    num = 1;
    input = std::format("%{:b}", num);
    length = 0;
    auto res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1;
    input = std::format("0b{:b}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("0b{:b}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, input.length());
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 1234567890;
    input = std::format("(%{:b},X)", num);
    length = 0;
    res = make_number(input, 1, length);
    EXPECT_EQ(length, input.length() - 4);
    ASSERT_TRUE(res.is_ok());
    EXPECT_EQ(res.get_ok(), num);

    num = 15;
    input = std::format("0b{}", num);
    length = 0;
    res = make_number(input, 0, length);
    EXPECT_EQ(length, 0);
    ASSERT_TRUE(res.is_err());
    EXPECT_EQ(res.get_err(), NumberParseError::InvalidDigit);
}

TEST(TestToken, IsMathOp)
{
    std::vector<ArithmeticOp> ops{
        ArithmeticOp::Add,
        ArithmeticOp::Subtract,
        ArithmeticOp::Multiply,
        ArithmeticOp::Divide};

    for (auto op : ops)
    {
        ASSERT_TRUE(is_arith_op(static_cast<char>(op)));
    }
    ASSERT_FALSE(is_arith_op('%'));
}

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
    std::string input{};

    input = "not_label";
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Symbol);
    ASSERT_EQ(std::get<token::Symbol>(token.get()).value, input);

    input = std::format("{}:", test_label);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
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
}

TEST(TestToken, Comment)
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

    input = std::format(";;{}", comment);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
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

TEST(TestToken, Mnemonic)
{
    const auto op_id = OpName::NOP;
    const std::string& mnemonic = opid_to_name(op_id);
    std::string input{};

    input = mnemonic;
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);

    for (const auto& pair : MNEMONIC_MAP)
    {
        result = Token::tokenize_line(pair.first);
        ASSERT_TRUE(result.is_ok());
        tokens = result.get_ok();
        ASSERT_EQ(tokens.size(), 1);
        token = tokens[0];
        ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
        ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, pair.second);
    }
}

TEST(TestToken, Hash)
{
    std::string input{};

    input = std::format("#");
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Hash);

    input = std::format("LDA #$11");
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_GT(tokens.size(), 1);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Hash);
}

TEST(TestToken, Char)
{
    std::string input{};
    const char letter = 'M';
    const char number = '5';
    const char space = ' ';
    const char special = '#';

    input = std::format("'{}", letter);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Char);
    ASSERT_EQ(std::get<token::Char>(token.get()).value, letter);

    input = std::format("'{}", number);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Char);
    ASSERT_EQ(std::get<token::Char>(token.get()).value, number);

    input = std::format("'{}", space);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Char);
    ASSERT_EQ(std::get<token::Char>(token.get()).value, space);

    input = std::format("'{}", special);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Char);
    ASSERT_EQ(std::get<token::Char>(token.get()).value, special);

    input = "'";
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), AsmError::BadChar);

    input = "'\t";
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), AsmError::BadChar);
}


TEST(TestToken, ZeroPageByteHex)
{
    const auto op_id = OpName::LDA;
    const auto mnemonic = opid_to_name(op_id);
    const uint8_t byte = 0xCA;
    std::string input{};

    input = std::format("{} ${:02X}", mnemonic, byte);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Byte);
    ASSERT_EQ(std::get<token::Byte>(token.get()).value, byte);

    input = std::format("{} &{:02X}", mnemonic, byte);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Byte);
    ASSERT_EQ(std::get<token::Byte>(token.get()).value, byte);

    input = std::format("{} 0x{:02X}", mnemonic, byte);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Byte);
    ASSERT_EQ(std::get<token::Byte>(token.get()).value, byte);
}

TEST(TestToken, ZeroPageByteOctal)
{
    const auto op_id = OpName::LDA;
    const auto mnemonic = opid_to_name(op_id);
    const uint8_t byte = 0xCA;
    std::string input{};

    input = std::format("{} @{:03o}", mnemonic, byte);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Byte);
    ASSERT_EQ(std::get<token::Byte>(token.get()).value, byte);

    input = std::format("{} 0{:03o}", mnemonic, byte);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Byte);
    ASSERT_EQ(std::get<token::Byte>(token.get()).value, byte);

    input = std::format("{} 0o{:03o}", mnemonic, byte);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Byte);
    ASSERT_EQ(std::get<token::Byte>(token.get()).value, byte);
}

TEST(TestToken, ZeroPageByteError)
{
    const auto op_id = OpName::LDA;
    const auto mnemonic = opid_to_name(op_id);
    const uint8_t byte = 0xCA;
    std::string input{};

    input = std::format("{} $0G", mnemonic);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), AsmError::BadNumber);
}

TEST(TestToken, ImmediateByte)
{
    const auto op_id = OpName::LDA;
    const auto mnemonic = opid_to_name(op_id);
    const uint8_t byte = 0xCA;
    std::string input{};

    input = std::format("{} #${:02X}", mnemonic, byte);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 3);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);

    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Hash);

    token = tokens[2];
    ASSERT_EQ(token.token_type(), TokenType::Byte);
    ASSERT_EQ(std::get<token::Byte>(token.get()).value, byte);
}

TEST(TestToken, AbsoluteHex)
{
    const auto op_id = OpName::LDA;
    const auto mnemonic = opid_to_name(op_id);
    const uint16_t address = 0xCAFE;
    std::string input{};

    input = std::format("{} ${:04X}", mnemonic, address);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Address);
    ASSERT_EQ(std::get<token::Address>(token.get()).value, address);
}

TEST(TestToken, AbsoluteHexError)
{
    const auto op_id = OpName::LDA;
    const auto mnemonic = opid_to_name(op_id);
    const uint32_t big_address = 0xDACAFE;
    std::string input{};

    input = std::format("{} ${:08X}", mnemonic, big_address);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), AsmError::BadNumber);
}

TEST(TestToken, CompLaMnCm)
{
    const auto op_id = OpName::NOP;
    const auto mnemonic = opid_to_name(op_id);
    const auto test_label{"reset_procedure"};
    const auto comment = "Commentary. ; A message.";
    std::string input{};

    input = std::format("{}: ;; {}", test_label, comment);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Label);
    ASSERT_EQ(std::get<token::Label>(token.get()).value, test_label);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Comment);
    ASSERT_EQ(std::get<token::Comment>(token.get()).value, comment);

    input = std::format("{}: {}", test_label, mnemonic);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Label);
    ASSERT_EQ(std::get<token::Label>(token.get()).value, test_label);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);

    input = std::format("{}: {} ;; {}", test_label, mnemonic, comment);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 3);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Label);
    ASSERT_EQ(std::get<token::Label>(token.get()).value, test_label);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);
    token = tokens[2];
    ASSERT_EQ(token.token_type(), TokenType::Comment);
    ASSERT_EQ(std::get<token::Comment>(token.get()).value, comment);

    input = std::format("{}: ;; {} {}", test_label, mnemonic, comment);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 2);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Label);
    ASSERT_EQ(std::get<token::Label>(token.get()).value, test_label);
    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Comment);
    ASSERT_EQ(
        std::get<token::Comment>(token.get()).value,
        std::format("{} {}", mnemonic, comment));

    input = std::format(";; {}: {} {}", test_label, mnemonic, comment);
    result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 1);
    token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Comment);
    ASSERT_EQ(
        std::get<token::Comment>(token.get()).value,
        std::format("{}: {} {}", test_label, mnemonic, comment));
}

TEST(TestToken, Composite1)
{
    const auto op_id = OpName::LDA;
    uint16_t address = 0xBEEF;
    const auto mnemonic = opid_to_name(op_id);
    const auto test_label{"reset_procedure"};
    const auto comment = "Commentary. ; A message.";
    std::string input{};

    input = std::format("{}: {} (${:04X}),X ;; {}", test_label, mnemonic, address, comment);
    auto result = Token::tokenize_line(input);
    ASSERT_TRUE(result.is_ok());
    auto tokens = result.get_ok();
    ASSERT_EQ(tokens.size(), 7);

    auto token = tokens[0];
    ASSERT_EQ(token.token_type(), TokenType::Label);
    ASSERT_EQ(std::get<token::Label>(token.get()).value, test_label);

    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Mnemonic);
    ASSERT_EQ(std::get<token::Mnemonic>(token.get()).value, op_id);

    token = tokens[2];
    ASSERT_EQ(token.token_type(), TokenType::LParen);

    token = tokens[4];
    ASSERT_EQ(token.token_type(), TokenType::RParen);

    token = tokens[1];
    ASSERT_EQ(token.token_type(), TokenType::Comment);
    ASSERT_EQ(std::get<token::Comment>(token.get()).value, comment);
}

} // namespace mos6502
