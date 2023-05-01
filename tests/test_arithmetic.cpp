#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <format>
#include <string>

#include "arithmetic.hpp"
#include "gen/asm6502Lexer.h"
#include "gen/asm6502Parser.h"


namespace mos6502 {

TEST(TestArithmetic, MakeNumber)
{
    using RetType = Result<int32_t, ParseError>;

    std::array<Base, 4> bases{Base::Binary, Base::Octal, Base::Decimal, Base::Hex};
    std::array<char, 4> prefixes{'b', 'o', 'd', 'x'};

    for (size_t idx = 0; idx < 4; ++idx)
    {
        const auto base = bases[idx];
        const auto& map = BASE_MAP.at(base);
        for (const auto& pair : map)
        {
            std::string input = std::format("0{}{}", prefixes[idx], pair.first);
            auto result = make_number(base, 2, input);
            ASSERT_TRUE(result.is_ok());
            EXPECT_EQ(result.get_ok(), pair.second);
        }
    }
    std::string input{"0xg"};
    auto bad_num_res = make_number(Base::Hex, 2, input);
    ASSERT_TRUE(bad_num_res.is_err());
    EXPECT_EQ(bad_num_res.get_err(), ParseError::BadNumber);

    input = "0dA";
    bad_num_res = make_number(Base::Decimal, 2, input);
    ASSERT_TRUE(bad_num_res.is_err());
    EXPECT_EQ(bad_num_res.get_err(), ParseError::BadNumber);

    input = "0o8";
    bad_num_res = make_number(Base::Octal, 2, input);
    ASSERT_TRUE(bad_num_res.is_err());
    EXPECT_EQ(bad_num_res.get_err(), ParseError::BadNumber);

    input = "0b2";
    bad_num_res = make_number(Base::Binary, 2, input);
    ASSERT_TRUE(bad_num_res.is_err());
    EXPECT_EQ(bad_num_res.get_err(), ParseError::BadNumber);
}

using ProgramContext = asm6502Parser::ProgramContext;

auto get_instruction_context(ProgramContext* program_file, size_t idx)
    -> asm6502Parser::InstructionContext*
{
    if (program_file->line(idx) == nullptr) {
    std::cerr << "null line\n";
        return nullptr;
    }
    if (program_file->line(idx)->instruction() == nullptr) {
        std::cerr << "null instruction\n";
        return nullptr;
    }
    return program_file->line(idx)->instruction();

}

auto get_byte_context(ProgramContext* program_file, size_t idx)
    -> asm6502Parser::ByteContext*
{
    auto instruction_context = get_instruction_context(program_file, idx);
    if (instruction_context == nullptr) { return nullptr; }
    if (instruction_context->immediate() == nullptr) {
        std::cerr << "null immediate\n";
        return nullptr;
    }
    auto* immediate = instruction_context->immediate();
    if (immediate->expression() == nullptr) {
        std::cerr << "null expression\n";
        return nullptr;
    }
    auto* expression = immediate->expression();
    if (expression->atom() == nullptr) {
        std::cerr << "null atom\n";
        return nullptr;
    }
    return expression->atom()->byte();
}

auto get_word_context(ProgramContext* program_file, size_t idx)
    -> asm6502Parser::MultibyteContext*
{
    auto instruction_context = get_instruction_context(program_file, idx);
    if (instruction_context == nullptr) { return nullptr; }
    if (instruction_context->absolute() == nullptr) {
        std::cerr << "null absolute\n";
        return nullptr;
    }
    auto* absolute = instruction_context->absolute();
    if (absolute->expression() == nullptr) {
        std::cerr << "null expression\n";
        return nullptr;
    }
    auto* expression = absolute->expression();
    if (expression->atom() == nullptr) {
        std::cerr << "null atom\n";
        return nullptr;
    }
    return expression->atom()->multibyte();
}

TEST(TestArithmetic, MakeByte)
{
    using RetType = Result<ArithmeticAtom, ParseError>;
    auto call_make_byte = [](const std::string& text) -> RetType
    {
        std::istringstream stream(text);

        antlr4::ANTLRInputStream input(stream);
        asm6502Lexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        asm6502Parser parser(&tokens);
        ProgramContext* program_file = parser.program();

        auto byte_context = get_byte_context(program_file, 0);
        if (byte_context == nullptr)
        {
            return RetType::err(ParseError::FailedToLoad);
        }
        return make_byte(byte_context);
    };

    uint16_t number = 0b10;
    std::string text = std::format("\tLDA #0b{:b}\n", number);

    auto make_byte_result = call_make_byte(text);
    if (make_byte_result.is_err())
    {
        std::cerr << std::format(
            "What? {}\n", static_cast<uint8_t>(make_byte_result.get_err()));
    }
    ASSERT_TRUE(make_byte_result.is_ok());
    auto make_byte_value = make_byte_result.get_ok();
    ASSERT_EQ(make_byte_value.get_type(), ArithAtomType::Byte);
    ASSERT_EQ(make_byte_value.get<uint8_t>(), number);

    number = 16;
    text = std::format("LDA #0x{:X}\n", number);
    make_byte_result = call_make_byte(text);
    ASSERT_TRUE(make_byte_result.is_ok());
    make_byte_value = make_byte_result.get_ok();
    ASSERT_EQ(make_byte_value.get_type(), ArithAtomType::Byte);
    ASSERT_EQ(make_byte_value.get<uint8_t>(), number);

    number = 10;
    text = std::format("LDA #0d{}\n", number);
    make_byte_result = call_make_byte(text);
    ASSERT_TRUE(make_byte_result.is_ok());
    make_byte_value = make_byte_result.get_ok();
    ASSERT_EQ(make_byte_value.get_type(), ArithAtomType::Byte);
    ASSERT_EQ(make_byte_value.get<uint8_t>(), number);

    number = 8;
    text = std::format("LDA #0o{:o}\n", number);
    make_byte_result = call_make_byte(text);
    ASSERT_TRUE(make_byte_result.is_ok());
    make_byte_value = make_byte_result.get_ok();
    ASSERT_EQ(make_byte_value.get_type(), ArithAtomType::Byte);
    ASSERT_EQ(make_byte_value.get<uint8_t>(), number);

    number = 256;
    text = std::format("LDA #0d{}\n", number);
    make_byte_result = call_make_byte(text);
    ASSERT_TRUE(make_byte_result.is_err());
    auto error = make_byte_result.get_err();
    ASSERT_EQ(error, ParseError::BadNumber);
}

TEST(TestArithmetic, MakeWord)
{
    using RetType = Result<ArithmeticAtom, ParseError>;
    auto call_make_word = [](const std::string& text) -> RetType
    {
        std::istringstream stream(text);

        antlr4::ANTLRInputStream input(stream);
        asm6502Lexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        asm6502Parser parser(&tokens);
        ProgramContext* program_file = parser.program();

        auto word_context = get_word_context(program_file, 0);
        if (word_context == nullptr)
        {
            return RetType::err(ParseError::FailedToLoad);
        }
        return make_word(word_context);
    };

    uint32_t number = 3000;
    std::string text = std::format("\tLDA 0b{:b}\n", number);

    auto make_word_result = call_make_word(text);
    ASSERT_TRUE(make_word_result.is_ok());
    auto make_word_value = make_word_result.get_ok();
    ASSERT_EQ(make_word_value.get_type(), ArithAtomType::Word);
    ASSERT_EQ(make_word_value.get<uint16_t>(), number);

    text = std::format("LDA 0x{:X}\n", number);
    make_word_result = call_make_word(text);
    ASSERT_TRUE(make_word_result.is_ok());
    make_word_value = make_word_result.get_ok();
    ASSERT_EQ(make_word_value.get_type(), ArithAtomType::Word);
    ASSERT_EQ(make_word_value.get<uint16_t>(), number);

    text = std::format("LDA 0d{}\n", number);
    make_word_result = call_make_word(text);
    if (make_word_result.is_err())
    {
        std::cerr << std::format(
            "What? {}\n", static_cast<uint8_t>(make_word_result.get_err()));
    }
    ASSERT_TRUE(make_word_result.is_ok());
    make_word_value = make_word_result.get_ok();
    ASSERT_EQ(make_word_value.get_type(), ArithAtomType::Word);
    ASSERT_EQ(make_word_value.get<uint16_t>(), number);

    text = std::format("LDA 0o{:o}\n", number);
    make_word_result = call_make_word(text);
    ASSERT_TRUE(make_word_result.is_ok());
    make_word_value = make_word_result.get_ok();
    ASSERT_EQ(make_word_value.get_type(), ArithAtomType::Word);
    ASSERT_EQ(make_word_value.get<uint16_t>(), number);

    number = 0x1FFFF;
    text = std::format("LDA 0d{}\n", number);
    make_word_result = call_make_word(text);
    ASSERT_TRUE(make_word_result.is_err());
    auto error = make_word_result.get_err();
    ASSERT_EQ(error, ParseError::BadNumber);
}

TEST(TestArithmetic, UnknownSymbol)
{
    ArithmeticExpression expression_1{};
    std::string test_symbol{"test"};
    expression_1.add_atom(ArithmeticAtom{test_symbol});
    ArithmeticExpression expression_2 = expression_1;

    SymbolMap map{};
    auto result_1 = expression_1.evaluate(map, 0);
    map[test_symbol] = 5;
    auto result_2 = expression_2.evaluate(map, 0);

    ASSERT_TRUE(result_1.is_err());
    EXPECT_EQ(result_1.get_err(), ParseError::SymbolUndefined);
    ASSERT_TRUE(result_2.is_ok());
    EXPECT_EQ(result_2.get_ok(), map[test_symbol]);
}

} // namespace mos6502
