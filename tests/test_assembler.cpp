#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <format>
#include <numeric>
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

TEST(TestAssembler, EmptyLine)
{
   const std::string input_1 = std::format("\n");
    auto result = Assembler::from_text(input_1);
    ASSERT_TRUE(result.is_ok());
    auto assembler_1 = result.get_ok();
    EXPECT_EQ(assembler_1.format(), input_1);
    EXPECT_EQ(assembler_1.size(), 0);
    auto prog_bytes = assembler_1.serialize();
    ASSERT_EQ(prog_bytes.size(), 0);
}

TEST(TestAssembler, Label)
{
    const std::string input_1 = std::format("LABEL1:\n");
    auto result = Assembler::from_text(input_1);
    ASSERT_TRUE(result.is_ok());
    auto assembler_1 = result.get_ok();
    EXPECT_EQ(assembler_1.format(), input_1);
    EXPECT_EQ(assembler_1.size(), 0);
    auto prog_bytes = assembler_1.serialize();
    ASSERT_EQ(prog_bytes.size(), 0);

    const std::string input_2 = std::format("@LABEL1\n");
    result = Assembler::from_text(input_2);
    ASSERT_TRUE(result.is_ok());
    auto assembler_2 = result.get_ok();
    EXPECT_EQ(assembler_2.format(), input_1);
    EXPECT_EQ(assembler_2.size(), 0);
    prog_bytes = assembler_2.serialize();
    ASSERT_EQ(prog_bytes.size(), 0);

    const std::string input_3 = std::format("@LABEL1:\t;Comment\n");
    result = Assembler::from_text(input_3);
    ASSERT_TRUE(result.is_ok());
    auto assembler_3 = result.get_ok();
    EXPECT_EQ(assembler_3.format(), std::format("LABEL1:\t;Comment\n"));
    EXPECT_EQ(assembler_3.size(), 0);
    prog_bytes = assembler_3.serialize();
    ASSERT_EQ(prog_bytes.size(), 0);

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

TEST(TestAssembler, ASSIGN_REPEAT_VAR)
{
    std::string input{"R% EQU 1"};
    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_err());
    EXPECT_EQ(result.get_err(), ParseError::IllegalRepeatVar);
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
    std::vector<uint8_t> expected_bytes{
        STA_ZPG_X, static_cast<uint8_t>(value * 2 - 2),
        STA_ABS_X, expected_low, expected_high
    };
    EXPECT_EQ(prog_bytes, expected_bytes);
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
    std::vector<uint8_t> expected_bytes{
        STA_ABS_Y, expected_low, expected_high
    };
    EXPECT_EQ(prog_bytes, expected_bytes);
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
    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), 2);
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), 2);

    constexpr uint8_t expected_byte = -(-value + -(value/2));
    std::vector<uint8_t> expected_bytes{
        STX_ZPG_Y, expected_byte
    };
    EXPECT_EQ(prog_bytes, expected_bytes);
}

TEST(TestAssembler, AllAddressModes)
{
    std::string input;
    std::vector<uint8_t> test_program{};
    auto op_set_size = [](size_t acc, const auto& pair) -> size_t {
        return acc + (1 + address_mode_num_bytes(pair.first)) * pair.second.size();
    };
    using std::accumulate;
    constexpr auto& map = ADDRESS_MODE_MAP;

    for (auto mnemonic : IMPLICIT_OP_SET)
    {
        if (!ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(IMPLICIT_MAP.at(mnemonic));
            input += std::format("\t{}\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : ACC_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(ACC_MAP.at(mnemonic));
            input += std::format("\t{} A\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : IMMEDIATE_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(IMMEDIATE_MAP.at(mnemonic));
            test_program.push_back(0);
            input += std::format("\t{} #$00\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : ABSOLUTE_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(ABSOLUTE_MAP.at(mnemonic));
            test_program.push_back(0);
            test_program.push_back(3);
            input += std::format("\t{} $0300\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : ABSOLUTE_X_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(ABSOLUTE_X_MAP.at(mnemonic));
            test_program.push_back(0);
            test_program.push_back(3);
            input += std::format("\t{} $0300,X\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : ABSOLUTE_Y_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(ABSOLUTE_Y_MAP.at(mnemonic));
            test_program.push_back(0);
            test_program.push_back(3);
            input += std::format("\t{} $0300,Y\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : ZPG_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(ZPG_MAP.at(mnemonic));
            test_program.push_back(0);
            input += std::format("\t{}.b $00\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : ZPG_X_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(ZPG_X_MAP.at(mnemonic));
            test_program.push_back(0);
            input += std::format("\t{}.b $00,X\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : ZPG_Y_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(ZPG_Y_MAP.at(mnemonic));
            test_program.push_back(0);
            input += std::format("\t{}.b $00,Y\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : INDIRECT_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(INDIRECT_MAP.at(mnemonic));
            test_program.push_back(0);
            test_program.push_back(0);
            input += std::format("\t{} ($0000)\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : X_INDIRECT_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(X_INDIRECT_MAP.at(mnemonic));
            test_program.push_back(0);
            input += std::format("\t{} ($00,X)\n", opid_to_name(mnemonic));
        }
    }
    for (auto mnemonic : INDIRECT_Y_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(INDIRECT_Y_MAP.at(mnemonic));
            test_program.push_back(0);
            input += std::format("\t{} ($0000),Y\n", opid_to_name(mnemonic));
        }
    }
    size_t branch_label_idx = 0;
    for (auto mnemonic : RELATIVE_OP_SET)
    {
        if (mnemonic != OpName::NOP && !ILLEGAL_OP_SET.contains(mnemonic))
        {
            test_program.push_back(RELATIVE_MAP.at(mnemonic));
            test_program.push_back(-2);
            input += std::format(
                "BRNCH{}: {} BRNCH{}\n",
                branch_label_idx,
                opid_to_name(mnemonic),
                branch_label_idx);
            branch_label_idx++;
        }
    }

    auto result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), test_program.begin()));
}

TEST(TestAssembler, OrgDirective)
{
    std::string input{std::format(".ORG $0400\n")};
    std::vector<uint8_t> test_program{};
    auto result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), test_program.begin()));
    EXPECT_EQ(assembler.format(), input);

    input = std::format(
        "{}\n{}\n",
        ".ORG $0400",
        "\tNOP");
    test_program = std::vector{NOP_IMPL};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), test_program.begin()));

    input = std::format(
        "{}\n{}\n",
        ".ORG -1",
        "\tNOP");
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_err());
    EXPECT_EQ(result.get_err(), ParseError::InvalidRange);
}

TEST(TestAssembler, ByteDirective)
{
    uint8_t value = 0x42;
    std::string line_1{std::format(".BYTE ${:02X}\n", value)};
    std::string input{line_1};
    std::vector<uint8_t> test_program{value};
    auto result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), input);

    input = std::format(
        "{}\n{}\n",
        line_1,
        "\tNOP");
    test_program = std::vector{value, NOP_IMPL};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);

    const uint8_t value_1 = value;
    const uint8_t value_2 = 0x13;
    input = std::format("\tINX\n.BYTE ${:02X}, ${:02X}\n\tNOP\n", value_1, value_2);
    test_program = std::vector{INX_IMPL, value_1, value_2, NOP_IMPL};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), input);

    input = std::format(".BYTE -1");
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_err());
    EXPECT_EQ(result.get_err(), ParseError::InvalidRange);
}

TEST(TestAssembler, DByteDirective)
{
    uint16_t value = 0x4213;
    uint8_t low = value & 0xFF;
    uint8_t high = (value >> 8) & 0xFF;
    std::string line_1{std::format(".DBYTE ${:04X}\n", value)};
    std::string input{line_1};
    std::vector<uint8_t> test_program{high, low};
    auto result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), input);

    input = std::format(
        "{}\n{}\n",
        line_1,
        "\tNOP");
    test_program = std::vector{high, low, NOP_IMPL};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);

    const uint16_t value_1 = value;
    const uint16_t value_2 = 0xFEED;
    input = std::format("\tINX\n.DBYTE ${:04X}, ${:04X}\n\tNOP\n", value_1, value_2);
    test_program = std::vector{
        INX_IMPL,
        high,
        low,
        static_cast<uint8_t>((value_2 >> 8) & 0xFF),
        static_cast<uint8_t>(value_2 & 0xFF),
        NOP_IMPL};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), input);
}

TEST(TestAssembler, WordDirective)
{
    uint16_t value = 0x4213;
    uint8_t low = value & 0xFF;
    uint8_t high = (value >> 8) & 0xFF;
    std::string line_1{std::format(".WORD ${:02X}\t;COMMENT\n", value)};
    std::string input{line_1};
    std::vector<uint8_t> test_program{low, high};
    auto result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    auto prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), test_program.begin()));
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), input);

    input = std::format(
        "{}\n{}\n",
        line_1,
        "\tNOP");
    test_program = std::vector{low, high, NOP_IMPL};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);

    const uint16_t value_1 = value;
    const uint16_t value_2 = 0xFEED;
    input = std::format("\tINX\n.WORD ${:04X}, ${:04X}\n\tNOP\n", value_1, value_2);
    test_program = std::vector{
        INX_IMPL,
        low,
        high,
        static_cast<uint8_t>(value_2 & 0xFF),
        static_cast<uint8_t>((value_2 >> 8) & 0xFF),
        NOP_IMPL};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), input);
}

TEST(TestAssembler, TextDirective)
{
    std::string text{"Hello, World\\n"};
    std::string program_text{"Hello, World\n"};
    std::string line_1{std::format(".TEXT \"{}\"", text)};
    std::string input{line_1 + '\n'};
    std::vector<uint8_t> test_program(program_text.begin(), program_text.end());
    auto result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    auto prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), input);

    input = std::format(
        "{}\n{}\n{}\n",
        "\tINX",
        line_1,
        "\tNOP");
    test_program = {};
    test_program.push_back(INX_IMPL);
    test_program.insert(test_program.end(), program_text.begin(), program_text.end());
    test_program.push_back(NOP_IMPL);
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), input);

    text = std::format("escapes: {}{}\\t\\n\\r", '\\', '"');
    input = std::format(".TEXT \"{}\"\n", text);
    program_text = "escapes: \"\t\n\r";
    test_program = {program_text.begin(), program_text.end()};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    ASSERT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), input);

    text = std::format("bad escape: \\q\\g\\l");
    input = std::format(".TEXT \"{}\"\n", text);
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_err());
    EXPECT_EQ(result.get_err(), ParseError::SyntaxError);
}

TEST(TestAssembler, AlignDirective)
{
    std::string input{".ALIGN"};
    std::string normalized_input{".ALIGN $0002 $00\n"};
    std::vector<uint8_t> test_program{0x00, 0x00};
    auto result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    auto prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = ".ALIGN 2";
    normalized_input = ".ALIGN $0002 $00\n";
    test_program = {0x00, 0x00};
    result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = ".ALIGN 2 0";
    normalized_input = ".ALIGN $0002 $00\n";
    test_program = {0x00, 0x00};
    result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = ".ALIGN 4 $EA";
    normalized_input = ".ALIGN $0004 $EA\n";
    test_program = {0xEA, 0xEA, 0xEA, 0xEA};
    result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = "\tINX\n.ALIGN 4 $EA\n\tINX";
    normalized_input = "\tINX\n.ALIGN $0004 $EA\n\tINX\n";
    test_program = {INX_IMPL, 0xEA, 0xEA, 0xEA, INX_IMPL};
    result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = "\tINX\n.ALIGN -1 $EA\n\tINX";
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), ParseError::InvalidRange);

    input = "\tINX\n.ALIGN 4 -1\n\tINX";
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), ParseError::InvalidRange);
}

TEST(TestAssembler, FillDirective)
{
    std::string input{".FILL 1"};
    std::string normalized_input{".FILL $0001 $00\n"};
    std::vector<uint8_t> test_program{0x00};
    auto result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    auto prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = ".FILL 2";
    normalized_input = ".FILL $0002 $00\n";
    test_program = {0x00, 0x00};
    result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = ".FILL 2 0";
    normalized_input = ".FILL $0002 $00\n";
    test_program = {0x00, 0x00};
    result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = ".FILL 4 $EA";
    normalized_input = ".FILL $0004 $EA\n";
    test_program = {0xEA, 0xEA, 0xEA, 0xEA};
    result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = "\tINX\n.FILL 4 $EA\n\tINX";
    normalized_input = "\tINX\n.FILL $0004 $EA\n\tINX\n";
    test_program = {INX_IMPL, 0xEA, 0xEA, 0xEA, 0xEA, INX_IMPL};
    result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), normalized_input);

    input = "\tINX\n.FILL -1 $EA\n\tINX";
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), ParseError::InvalidRange);

    input = "\tINX\n.FILL 4 -1\n\tINX";
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_err());
    ASSERT_EQ(result.get_err(), ParseError::InvalidRange);
}

TEST(TestAssembler, RepeatDirective)
{
    std::string input{".REPEAT 1 NOP"};
    std::string output{".REPEAT $0001\n\tNOP\n"};
    std::vector<uint8_t> test_program{NOP_IMPL};
    auto result = Assembler::from_text(input);
    if (result.is_err()) { logger::error("Error is {}", static_cast<uint8_t>(result.get_err())); }
    ASSERT_TRUE(result.is_ok());
    auto assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    auto prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), output);

    input = ".REPEAT 0 NOP";
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_err());
    EXPECT_EQ(result.get_err(), ParseError::BadCount);

    input = ".REPEAT 3 LDA #R%";
    output = ".REPEAT $0003\n\tLDA #$00\n\tLDA #$01\n\tLDA #$02\n";
    test_program = {LDA_IMM, 0, LDA_IMM, 1, LDA_IMM, 2};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), output);

    input = ".REPEAT 3 .FILL R%+1 R%";
    output = ".REPEAT $0003\n.FILL $0001 $00\n.FILL $0002 $01\n.FILL $0003 $02\n";
    test_program = {0, 1, 1, 2, 2, 2};
    result = Assembler::from_text(input);
    ASSERT_TRUE(result.is_ok());
    assembler = result.get_ok();
    EXPECT_EQ(assembler.size(), test_program.size());
    prog_bytes = assembler.serialize();
    EXPECT_EQ(prog_bytes.size(), test_program.size());
    EXPECT_EQ(prog_bytes, test_program);
    EXPECT_EQ(assembler.format(), output);
}

} // namespace mos6502
