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

TEST(TestAssembler, LDA_IMM_EXPR)
{
    OpName op_id = OpName::LDA;
    const std::string op_name = opid_to_name(op_id);
    uint8_t value = 42;
    std::string input = std::format(
        "\t{} #<[-${:02X}+${:02X}]\n",
        op_name,
        value,
        value);
    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), 2);
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), 2);
    EXPECT_EQ(prog_bytes[0], LDA_IMM);
    EXPECT_EQ(prog_bytes[1], 0);

    input = std::format(
        "\t{} #<[-${:02X}*5]\n", op_name, value);

    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), 2);
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), 2);
    EXPECT_EQ(prog_bytes[0], LDA_IMM);
    EXPECT_EQ(prog_bytes[1], (-value * 5) & 0xFF);
}

TEST(TestAssembler, ASSIGN_LDA_ABS)
{
    OpName op_id = OpName::LDA;
    const std::string op_name = opid_to_name(op_id);
    const std::string symbol{"FOO"};
    uint16_t symbol_value = 0x200;
    uint8_t value = 42;
    std::string line_1 = std::format("{} EQU ${:04X}\n", symbol, symbol_value);
    std::string line_2 = "NOP\n";
    std::string line_3 = std::format(
        "\t{} {}-*\n",
        op_name,
        symbol,
        value);
    std::string input = line_1 + line_2 + line_3;
    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), 4);
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), 4);
    EXPECT_EQ(prog_bytes[0], NOP_IMPL);
    EXPECT_EQ(prog_bytes[1], LDA_ABS);
    auto expected_value = symbol_value  - 1;
    EXPECT_EQ(prog_bytes[2], expected_value & 0xFF);
    EXPECT_EQ(prog_bytes[3], (expected_value >> 8) & 0xFF);
}

TEST(TestAssembler, ASSIGN_STA_INDEX_X_NESTED_EXPR)
{
    OpName op_id = OpName::STA;
    const std::string op_name = opid_to_name(op_id);
    const std::string symbol{"FOO"};
    uint16_t symbol_value = 0x200;
    uint8_t value = 42;
    std::string line_1 = std::format("{} EQU ${:04X}\n", symbol, symbol_value);
    std::string line_2 = std::format(
        "\t{} [[{}*1]+[{}-2]],X\n",
        op_name,
        value,
        value);
    std::string line_3 = std::format(
        "\t{} {}+[[{}-1]+[{}*2]+-[2*3]],X\n",
        op_name,
        symbol,
        value,
        value);
    std::string input = line_1 + line_2 + line_3;
    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), 5);
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), 5);

    uint16_t expected_address = 0x200 + (value - 1 + value * 2 - 6);
    uint8_t expected_low = static_cast<uint8_t>(expected_address & 0xFF);
    uint8_t expected_high = static_cast<uint8_t>((expected_address >> 8) & 0xFF);
    std::array<uint8_t, 5> expected_bytes{
        STA_ZPG_X, static_cast<uint8_t>(value * 2 - 2),
        STA_ABS_X, expected_low, expected_high
    };
    EXPECT_EQ(std::memcmp(prog_bytes.data(), expected_bytes.data(), prog_bytes.size()), 0);
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), expected_bytes.begin()));
}

TEST(TestAssembler, STA_INDEX_Y_NESTED_EXPR)
{
    OpName op_id = OpName::STA;
    const std::string op_name = opid_to_name(op_id);
    uint8_t value = 42;
    std::string line_1 = std::format(
        "\t{} 0x300+[[{}*1]+-[{}/2]],Y\n",
        op_name,
        value,
        value);
    std::string input = line_1;
    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), 3);
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), 3);

    uint16_t expected_address = 0x300 + (value + -(value/2));
    uint8_t expected_low = static_cast<uint8_t>(expected_address & 0xFF);
    uint8_t expected_high = static_cast<uint8_t>((expected_address >> 8) & 0xFF);
    std::array<uint8_t, 3> expected_bytes{
        STA_ABS_Y, expected_low, expected_high
    };
    EXPECT_EQ(std::memcmp(prog_bytes.data(), expected_bytes.data(), prog_bytes.size()), 0);
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), expected_bytes.begin()));
}

TEST(TestAssembler, STA_INDEX_Y_UNARY_EXPR)
{
    OpName op_id = OpName::STX;
    const std::string op_name = opid_to_name(op_id);
    constexpr uint8_t value = 42;
    std::string line_1 = std::format(
        "\t{} -[-[{}*1]+-[{}/2]],Y\n",
        op_name,
        value,
        value);
    std::string input = line_1;
    std::cout << "input is\n" << input << "\n";
    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), 2);
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), 2);

    constexpr uint8_t expected_byte = -(-value + -(value/2));
    std::array<uint8_t, 2> expected_bytes{
        STX_ZPG_Y, expected_byte
    };
    EXPECT_EQ(std::memcmp(prog_bytes.data(), expected_bytes.data(), prog_bytes.size()), 0);
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), expected_bytes.begin()));
}

} // namespace mos6502
