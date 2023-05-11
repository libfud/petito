#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <format>
#include <string>

#include "arithmetic.hpp"
#include "gen/asm6502Lexer.h"
#include "gen/asm6502Parser.h"


namespace mos6502 {

TEST(TestArithmetic, CopyMove)
{
    using Atom = ArithmeticExpression::Atom;
    ArithmeticExpression expression_1{};
    ArithmeticExpression sub_expression{};
    ArithmeticExpression nested_expression{};
    uint8_t value = 42;
    sub_expression.add_atom(Atom{UnaryOperator::Minus});
    sub_expression.add_atom(Atom{value});
    sub_expression.add_atom(Atom{BinaryOperator::Add});
    nested_expression.add_atom(Atom{value});
    sub_expression.add_expression(std::move(nested_expression));
    expression_1.add_expression(std::move(sub_expression));
    ArithmeticExpression expression_2{expression_1};
    ArithmeticExpression expression_3{};
    expression_3 = expression_1;
    expression_1 = expression_1;
    ASSERT_EQ(expression_1.format(), expression_2.format());
    ASSERT_EQ(expression_1.format(), expression_3.format());
    auto expression_4 = std::move(expression_2);
    auto expression_5{std::move(expression_3)};
    ASSERT_EQ(expression_1.format(), expression_4.format());
    ASSERT_EQ(expression_1.format(), expression_5.format());
}

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

    class TestByteContext : public asm6502Parser::ByteContext {
    public:
        TestByteContext() : ByteContext{nullptr, 0} {}
        auto HEX_BYTE() -> antlr4::tree::TerminalNode* { return nullptr; }
        auto DECIMAL_BYTE() -> antlr4::tree::TerminalNode* { return nullptr; }
        auto OCTAL_BYTE() -> antlr4::tree::TerminalNode* { return nullptr; }
        auto BINARY_BYTE() -> antlr4::tree::TerminalNode* { return nullptr; }
    };

    TestByteContext context{};
    make_byte_result = make_byte(&context);
    ASSERT_TRUE(make_byte_result.is_err());
    ASSERT_EQ(make_byte_result.get_err(), ParseError::LogicError);
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

    class TestWordContext : public asm6502Parser::MultibyteContext {
    public:
        TestWordContext() : MultibyteContext{nullptr, 0} {}
        auto HEX_BYTE() -> antlr4::tree::TerminalNode* { return nullptr; }
        auto DECIMAL_BYTE() -> antlr4::tree::TerminalNode* { return nullptr; }
        auto OCTAL_BYTE() -> antlr4::tree::TerminalNode* { return nullptr; }
        auto BINARY_BYTE() -> antlr4::tree::TerminalNode* { return nullptr; }
    };

    TestWordContext context{};
    make_word_result = make_word(&context);
    ASSERT_TRUE(make_word_result.is_err());
    ASSERT_EQ(make_word_result.get_err(), ParseError::LogicError);
}

TEST(TestArithmetic, UnknownSymbol)
{
    ArithmeticExpression expression_1{};
    ArithmeticExpression expression_2{};
    std::string test_symbol{"test"};
    expression_1.add_atom(ArithmeticAtom{test_symbol});
    expression_2 = expression_1;

    SymbolMap map{};
    auto result_1 = expression_1.evaluate(map, 0);
    map[test_symbol] = 5;
    auto result_2 = expression_2.evaluate(map, 0);

    ASSERT_TRUE(result_1.is_err());
    EXPECT_EQ(result_1.get_err(), ParseError::SymbolUndefined);
    ASSERT_TRUE(result_2.is_ok());
    EXPECT_EQ(result_2.get_ok(), map[test_symbol]);
}

TEST(TestArithmetic, Nesting)
{
    // -[-[42*1]+-[42/2]]
    using Atom = ArithmeticExpression::Atom;
    uint8_t lue = 42;
    uint8_t one = 1;
    uint8_t two = 2;

    // [42*1] = se2;
    ArithmeticExpression sub_expression_2{};
    sub_expression_2.add_atom(Atom{lue});
    sub_expression_2.add_atom(Atom{BinaryOperator::Multiply});
    sub_expression_2.add_atom(Atom{one});

    // [42/2] = se3;
    ArithmeticExpression sub_expression_3{};
    sub_expression_3.add_atom(Atom{lue});
    sub_expression_3.add_atom(Atom{BinaryOperator::Divide});
    sub_expression_3.add_atom(Atom{two});

    // [-se2+-se3] = se1
    ArithmeticExpression sub_expression_1{};
    sub_expression_1.add_atom(Atom{UnaryOperator::Minus});
    sub_expression_1.add_expression(std::move(sub_expression_2));
    sub_expression_1.add_atom(Atom{BinaryOperator::Add});
    sub_expression_1.add_atom(Atom{UnaryOperator::Minus});
    sub_expression_1.add_expression(std::move(sub_expression_3));

    // -[se1] = expression
    ArithmeticExpression expression{};
    expression.add_atom(Atom{UnaryOperator::Minus});
    expression.add_expression(std::move(sub_expression_1));
    std::cout << expression.format() << "\n";

    SymbolMap empty_map{};
    auto expression_res = expression.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_res.is_ok());
    auto expression_value = expression_res.get_ok();
    EXPECT_EQ(expression_value, -(-(lue*one)+-(lue/two)));
}

TEST(TestArithmetic, ByteOps)
{
    using Atom = ArithmeticExpression::Atom;
    uint8_t lue = 42;
    uint8_t two = 2;
    uint16_t combined = lue << 8 | two;
    SymbolMap empty_map{};

    ArithmeticExpression expression{};
    expression.add_atom(Atom{UnaryOperator::LowByte});
    expression.add_atom(Atom{combined});
    auto expression_result = expression.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_result.is_ok());
    EXPECT_EQ(expression_result.get_ok(), two);

    expression = {};
    expression.add_atom(Atom{UnaryOperator::HighByte});
    expression.add_atom(Atom{combined});
    expression_result = expression.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_result.is_ok());
    EXPECT_EQ(expression_result.get_ok(), lue);

    expression = {};
    expression.add_atom(Atom{UnaryOperator::Plus});
    expression.add_atom(Atom{lue});
    expression_result = expression.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_result.is_ok());
    EXPECT_EQ(expression_result.get_ok(), lue);

    expression = {};
    expression.add_atom(Atom{UnaryOperator::Minus});
    expression.add_atom(Atom{lue});
    expression_result = expression.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_result.is_ok());
    EXPECT_EQ(expression_result.get_ok(), -lue);
}

TEST(TestArithmetic, MissingBinaryOp)
{
    // -[-[42*1]+-[42/2]]
    using Atom = ArithmeticExpression::Atom;
    uint8_t lue = 42;
    uint8_t one = 1;
    uint8_t two = 2;
    SymbolMap empty_map{};

    ArithmeticExpression expression{};
    expression.add_atom(Atom{lue});
    expression.add_atom(Atom{one});
    auto expression_result = expression.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::BadEvaluation);

    ArithmeticExpression expression_2 = {};
    expression_2.add_atom(Atom{lue});
    expression_2.add_atom(Atom{BinaryOperator::Multiply});
    expression_2.add_atom(Atom{UnaryOperator::Minus});

    expression_result = expression_2.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::BadEvaluation);

    ArithmeticExpression expression_3 = {};
    expression_3.add_atom(Atom{lue});
    expression_3.add_atom(Atom{BinaryOperator::Multiply});
    expression_3.add_atom(Atom{one});
    expression_3.add_atom(Atom{BinaryOperator::Divide});

    expression_result = expression_3.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::BadEvaluation);
}

TEST(TestArithmetic, LeadingBinaryOp)
{
    // ++42
    using Atom = ArithmeticExpression::Atom;
    uint8_t lue = 42;
    SymbolMap empty_map{};

    ArithmeticExpression expression{};
    expression.add_atom(Atom{UnaryOperator::Plus});
    expression.add_atom(Atom{BinaryOperator::Add});
    expression.add_atom(Atom{lue});
    auto expression_result = expression.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::BadEvaluation);
}

TEST(TestArithmetic, SoleUnary)
{
    using Atom = ArithmeticExpression::Atom;
    SymbolMap empty_map{};

    ArithmeticExpression expression{};
    expression.add_atom(Atom{UnaryOperator::Plus});
    auto expression_result = expression.evaluate(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::BadEvaluation);
}

TEST(TestArithmetic, EvaluateByte)
{
    using Atom = ArithmeticExpression::Atom;
    uint8_t lue = 42;
    uint16_t big_lue = 0x4213;
    SymbolMap empty_map{};

    ArithmeticExpression expression{};
    expression.add_atom(Atom{lue});
    auto expression_result = expression.evaluate_byte(empty_map, 0);
    ASSERT_TRUE(expression_result.is_ok());
    ASSERT_EQ(expression_result.get_ok(), lue);

    expression = {};
    expression.add_atom(Atom{big_lue});
    expression_result = expression.evaluate_byte(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::InvalidRange);

    expression = {};
    expression.add_atom(Atom{big_lue});
    expression_result = expression.evaluate_byte(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::InvalidRange);

    expression = {};
    expression.add_atom(Atom{lue});
    expression.add_atom(Atom{BinaryOperator::Subtract});
    expression.add_atom(Atom{big_lue});
    expression_result = expression.evaluate_byte(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::InvalidRange);
}

TEST(TestArithmetic, EvaluateWord)
{
    using Atom = ArithmeticExpression::Atom;
    uint8_t lue = 42;
    uint16_t big_lue = 0x4213;
    SymbolMap empty_map{};

    ArithmeticExpression expression = {};
    expression.add_atom(Atom{big_lue});
    auto expression_result = expression.evaluate_word(empty_map, 0);
    ASSERT_TRUE(expression_result.is_ok());
    ASSERT_EQ(expression_result.get_ok(), big_lue);

    expression = {};
    expression.add_atom(Atom{lue});
    expression_result = expression.evaluate_word(empty_map, 0);
    ASSERT_TRUE(expression_result.is_ok());
    ASSERT_EQ(expression_result.get_ok(), lue);

    expression = {};
    expression.add_atom(Atom{big_lue});
    expression.add_atom(Atom{BinaryOperator::Multiply});
    expression.add_atom(Atom{big_lue});
    expression_result = expression.evaluate_word(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::InvalidRange);

    expression = {};
    expression.add_atom(Atom{lue});
    expression.add_atom(Atom{BinaryOperator::Subtract});
    expression.add_atom(Atom{big_lue});
    expression_result = expression.evaluate_word(empty_map, 0);
    ASSERT_TRUE(expression_result.is_err());
    ASSERT_EQ(expression_result.get_err(), ParseError::InvalidRange);
}

TEST(TestArithmeticAtom, Formatting)
{
    ArithmeticExpression expression{};
    uint8_t one = 1;
    uint16_t 千 = 1000;
    using Atom = ArithmeticExpression::Atom;
    expression.add_atom(Atom{UnaryOperator::LowByte});
    expression.add_atom(Atom{千});
    expression.add_atom(Atom{BinaryOperator::Add});
    expression.add_atom(Atom{UnaryOperator::Minus});
    expression.add_atom(Atom{one});
    expression.add_atom(Atom{BinaryOperator::Subtract});
    expression.add_atom(Atom{UnaryOperator::Plus});
    expression.add_atom(Atom{PcStar{}});
    expression.add_atom(Atom{BinaryOperator::Multiply});
    expression.add_atom(Atom{UnaryOperator::HighByte});
    expression.add_atom(Atom{std::string{"千"}});
    expression.add_atom(Atom{BinaryOperator::Divide});
    expression.add_atom(Atom{'A'});

    ASSERT_EQ(
        expression.format(),
        "<0x03E8+-0x01-+**>千/'A");
}

} // namespace mos6502
