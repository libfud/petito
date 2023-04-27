#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <cstdint>
#include <map>
#include <string>
#include <optional>
#include <variant>
#include <set>
#include <vector>

#include "result/result.hpp"
#include "opcode_table.hpp"
#include "gen/asm6502Parser.h"

namespace mos6502 {

using result::Result;

using SymbolMap = std::map<std::string, uint16_t>;

enum class Base : uint8_t {
    Binary = 2,
    Octal = 8,
    Decimal = 10,
    Hex = 16,
};

const std::map<char, int8_t> HEX_MAP{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
    {'A', 0xA}, {'B', 0xB}, {'C', 0xC}, {'D', 0xD}, {'E', 0xE}, {'F', 0xF},
    {'a', 0xA}, {'b', 0xB}, {'c', 0xC}, {'d', 0xD}, {'e', 0xE}, {'f', 0xF}};

const std::map<char, int8_t> DECIMAL_MAP{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}};

const std::map<char, int8_t> OCTAL_MAP{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}};

const std::map<char, int8_t> BINARY_MAP{{'0', 0}, {'1', 1}};

const std::map<Base, const std::map<char, int8_t>&> BASE_MAP
{
    {Base::Binary, BINARY_MAP},
    {Base::Octal, OCTAL_MAP},
    {Base::Decimal, DECIMAL_MAP},
    {Base::Hex, HEX_MAP}
};

enum class AsmError {
    FailedToLoad,
    NoTokenToParse,
    InvalidToken,
    InvalidPragma,
    InvalidKeyword,
    InvalidComma,
    BadNumber,
    BadChar,
    BadAssign,
    SymbolUndefined,
    SymbolRedefined,
    BadEvaluation,
    BadParse,
    InvalidRange,
    BadDecode,
    Unimplemented,
};

enum class ParseError {
  InvalidLabelParse,
  InvalidCommentParse,
  InvalidOpIdParse,
  InvalidHashParse,
  BadArithmetic,
  BadAssign,
  BadNumber,
  LogicError,
};

enum class BinaryOperator {
    Add,
    Subtract,
    Multiply,
    Divide,
};

enum class UnaryOperator {
    LowByte,
    HighByte,
    Plus,
    Minus,
    Star
};

using ArithAtomV = std::variant<
    BinaryOperator,
    UnaryOperator,
    uint8_t,
    uint16_t,
    char,
    std::string>;

enum class ArithAtomType {
    BinaryOp,
    UnaryOp,
    Byte,
    Word,
    Character,
    Symbol
};

template <typename T>
concept ArithmeticAtomType =
    std::same_as<T, BinaryOperator> || std::same_as<T, UnaryOperator> ||
    std::same_as<T, uint8_t> || std::same_as<T, uint16_t> ||
    std::same_as<T, char> ||
    std::same_as<T, std::string>;

class ArithmeticAtom {
public:
    template <typename T> requires(ArithmeticAtomType<T>)
    explicit ArithmeticAtom(const T& value)
        : value(value)
    {}

    auto get_type() const -> ArithAtomType;

    template <typename T>
    const T& get() const
        requires(ArithmeticAtomType<T>)
    {
        return std::get<T>(value);
    }

private:
    ArithAtomV value;
};

class ArithmeticExpression
{
public:
    using Context = asm6502Parser::ArithmeticContext;
    using ExprResult = Result<ArithmeticExpression, ParseError>;

    static auto make(Context* context) -> ExprResult;

    auto has_symbols() const -> bool;
    auto has_words() const -> bool;

    auto evaluate(const SymbolMap& symbol_map, uint16_t pc) -> Result<int32_t, AsmError>;

    using Atom = ArithmeticAtom;
    using Expr = ArithmeticExpression;
    using SExpr = std::variant<Atom, Expr*>;
    auto add_atom(Atom&& atom) -> void;
    auto add_expression(Expr* nested_expression) -> void;

    using NumberContext = asm6502Parser::NumberContext;
    using BinaryOpContext = asm6502Parser::Binary_opContext;
    using UnaryOpContext = asm6502Parser::Unary_opContext;
private:
    auto unary_expr(UnaryOperator op, uint16_t rhs, uint16_t pc) -> int32_t;
    auto binary_expr(int32_t acc, BinaryOperator op, uint16_t rhs) -> int32_t;
    static auto handle_number(
        Context* context,
        Expr& expression) -> std::optional<ParseError>;
    auto handle_number_context(NumberContext* context) -> std::optional<ParseError>;
    auto handle_unary_op(UnaryOpContext* context) -> std::optional<ParseError>;
    auto handle_binary_op(BinaryOpContext* context) -> std::optional<ParseError>;
    std::vector<SExpr> expression = {};
    bool symbols_encountered = false;
    bool words_encountered = false;
};

struct Symbol
{
    std::string name = {};
    ArithmeticExpression value = {};
};

enum class LineType {
    Instruction,
    Comment,
    Label,
    Assign,
    Directive,
    Empty,
};

class Instruction {
public:
    using InstructionResult = Result<Instruction, AsmError>;
    using BuilderResult = std::optional<ParseError>;
    using DecodeResult = Result<bool, AsmError>;
    static auto make(asm6502Parser::LineContext* line) -> InstructionResult;
    auto has_label() const -> bool;
    auto get_label() const -> const std::string&;
    auto size() const -> uint16_t;
    auto complete_decode(SymbolMap& symbol_map, uint16_t pc) -> std::optional<AsmError>;

private:
    auto validate() -> BuilderResult;
    auto handle_instruction_rule(
        asm6502Parser::InstructionContext* rule) -> BuilderResult;
    auto handle_immediate_rule(
        asm6502Parser::ImmediateContext* rule) -> BuilderResult;
    auto handle_x_index_rule(
        asm6502Parser::X_indexContext* rule) -> BuilderResult;
    auto handle_y_index_rule(
        asm6502Parser::Y_indexContext* rule) -> BuilderResult;
    auto handle_relative_rule(
        asm6502Parser::RelativeContext* rule) -> BuilderResult;
    auto handle_jump_rule(
        asm6502Parser::JumpContext* rule) -> BuilderResult;
    auto handle_jsr_rule(
        asm6502Parser::JsrContext* rule) -> BuilderResult;
    auto check_mnemonic(const std::string& name, AddressMode mode) -> BuilderResult;
    template <typename T>
    auto helper(T* rule, AddressMode mode) -> BuilderResult
    {
        std::string name;
        if (rule->mnemonic())
        {
            name = rule->mnemonic()->MNEMONIC()->getText();
        }
        else
        {
            name = rule->shift()->SHIFT()->getText();
        }

        auto invalid_mnemonic = check_mnemonic(name, mode);

        if (invalid_mnemonic != std::nullopt)
        {
            std::cout << "Invalid mnemonic!\n";
            return invalid_mnemonic;
        }

        auto* arithmetic_context = rule->arithmetic();
        auto arith_result = handle_arithmetic(arithmetic_context);
        if (arith_result != std::nullopt)
        {
            std::cout << "Invalid arithmetic!\n";
            return arith_result;
        }

        return {};
    }
    auto handle_arithmetic(
        asm6502Parser::ArithmeticContext* context) -> BuilderResult;

    std::optional<std::string> label = {};
    std::optional<std::string> comment = {};
    std::optional<OpName> op_id = {};
    std::optional<AddressMode> address_mode = {};
    std::optional<ArithmeticExpression> arithmetic_expression = {};
    std::vector<uint8_t> operands = {};
    std::optional<std::string> symbol = {};
    LineType line_type = LineType::Empty;
    bool complete = false;
};

class Assembler {
public:

    using AssemblerResult = Result<Assembler, AsmError>;
    using AsmParseResult = Result<Assembler, AsmError>;

    static auto from_file_name(const std::string& name) -> AssemblerResult;
    static auto from_file_name(std::string&& name) -> AssemblerResult;

    auto parse() -> AsmParseResult;

private:
    std::optional<std::string> file_name = {};
    std::map<std::string, std::set<size_t>> label_lines = {};
    SymbolMap symbols = {};
    std::vector<Instruction> program = {};
    std::vector<size_t> program_counter_lines = {};
};

} // namespace mos6502

#endif
