#ifndef ASM_LINE_HPP
#define ASM_LINE_HPP

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <variant>

#include "assembler_types.hpp"
#include "opcode_table.hpp"
#include "gen/asm6502Parser.h"
#include "result/result.hpp"

namespace mos6502 {

using result::Result;

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
};

struct PcStar {};

using ArithAtomV = std::variant<
    BinaryOperator,
    UnaryOperator,
    uint8_t,
    uint16_t,
    char,
    PcStar,
    std::string>;

enum class ArithAtomType {
    BinaryOp,
    UnaryOp,
    Byte,
    Word,
    Character,
    PcStar,
    Symbol
};

template <typename T>
concept ArithmeticAtomType =
    std::same_as<T, BinaryOperator> || std::same_as<T, UnaryOperator> ||
    std::same_as<T, uint8_t> || std::same_as<T, uint16_t> ||
    std::same_as<T, char> || std::same_as<T, PcStar> ||
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
    ArithmeticExpression() = default;
    ArithmeticExpression(const ArithmeticExpression& expr);
    ArithmeticExpression(ArithmeticExpression&& expr);
    ArithmeticExpression& operator=(const ArithmeticExpression& expr);
    ArithmeticExpression& operator=(ArithmeticExpression&& expr);

    using Context = asm6502Parser::ExpressionContext;
    using ExprResult = Result<ArithmeticExpression, ParseError>;

    static auto make(Context* context) -> ExprResult;

    auto has_symbols() const -> bool;
    auto has_words() const -> bool;

    auto evaluate(const SymbolMap& symbol_map, uint16_t pc) -> Result<int32_t, AsmError>;

    using Atom = ArithmeticAtom;
    using Expr = ArithmeticExpression;
    using SExpr = std::variant<Atom, std::unique_ptr<Expr>>;
    auto add_atom(Atom&& atom) -> void;
    auto add_expression(Expr&& nested_expression) -> void;

    using NumberContext = asm6502Parser::AtomContext;
    using BinaryOpContext = asm6502Parser::Binary_opContext;
    using UnaryOpContext = asm6502Parser::Unary_opContext;
private:
    auto unary_expr(UnaryOperator op, uint16_t rhs) -> int32_t;
    auto binary_expr(int32_t acc, BinaryOperator op, uint16_t rhs) -> int32_t;
    auto handle_atom(Context* context) -> std::optional<ParseError>;
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

template <typename T>
concept HasExpression = requires(T t) {
    { t.expression() } -> std::same_as<asm6502Parser::ExpressionContext*>;
};

template <typename T>
concept HasShiftAndMnemonic = requires(T t) {
    requires(HasExpression<T>);
    { t.mnemonic() } -> std::same_as<asm6502Parser::MnemonicContext*>;
    { t.shift() } -> std::same_as<asm6502Parser::ShiftContext*>;
};

class Line {
public:
    using LineResult = Result<Line, AsmError>;
    using BuilderResult = std::optional<ParseError>;
    using DecodeResult = Result<bool, AsmError>;
    static auto make(asm6502Parser::LineContext* line) -> LineResult;
    auto has_label() const -> bool;
    auto get_label() const -> const std::string&;
    auto size() const -> uint16_t;
    auto complete_decode(SymbolMap& symbol_map, uint16_t pc) -> std::optional<AsmError>;
    auto format() const -> std::string;
    auto instruction_format() const -> std::string;

private:
    using InstructionContext = asm6502Parser::InstructionContext;
    using ImmediateContext = asm6502Parser::ImmediateContext;
    using XIndexContext = asm6502Parser::X_indexContext;
    using YIndexContext = asm6502Parser::Y_indexContext;
    using RelativeContext = asm6502Parser::RelativeContext;
    using JumpContext = asm6502Parser::JumpContext;
    using JsrContext = asm6502Parser::JsrContext;

    auto handle_instruction_rule(InstructionContext* rule) -> BuilderResult;
    auto handle_immediate_rule(ImmediateContext* rule) -> BuilderResult;
    auto handle_x_index_rule(XIndexContext* rule) -> BuilderResult;
    auto handle_y_index_rule(YIndexContext* rule) -> BuilderResult;
    auto handle_relative_rule(RelativeContext* rule) -> BuilderResult;
    auto handle_jump_rule(JumpContext* rule) -> BuilderResult;
    auto handle_jsr_rule(JsrContext* rule) -> BuilderResult;
    auto check_mnemonic(const std::string& name, AddressMode mode) -> BuilderResult;
    template <typename T>
    auto helper(T* rule, AddressMode mode) -> BuilderResult
        requires(HasShiftAndMnemonic<T>)
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

        auto arith_result = handle_arithmetic(rule);
        if (arith_result != std::nullopt)
        {
            std::cout << "Invalid arithmetic!\n";
            return arith_result;
        }

        return {};
    }

    template <typename T>
    auto handle_arithmetic(T* parent_context) -> BuilderResult
        requires(HasExpression<T>)
    {
        auto* context = parent_context->expression();
        auto result = ArithmeticExpression::make(context);
        if (result.is_ok())
        {
            arithmetic_expression = result.get_ok();
            return {};
        }
        std::cerr << "Error: " << context->getText() << "\n";
        return result.get_err();
    }

    std::optional<std::string> label = {};
    std::optional<std::string> comment = {};
    std::optional<OpName> op_id = {};
    std::optional<AddressMode> address_mode = {};
    std::optional<ArithmeticExpression> arithmetic_expression = {};
    std::vector<uint8_t> operands = {};
    std::optional<std::string> symbol = {};
    std::optional<uint16_t> symbol_value = {};
    LineType line_type = LineType::Empty;
    bool complete = false;
};

} // namespace mos6502

#endif
