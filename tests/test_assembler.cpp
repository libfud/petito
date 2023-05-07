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
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), expected_bytes.begin()));
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
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), test_program.begin()));
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
    EXPECT_TRUE(std::equal(prog_bytes.begin(), prog_bytes.end(), test_program.begin()));
}

} // namespace mos6502
