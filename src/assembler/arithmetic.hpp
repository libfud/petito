#ifndef ASM_ARITHMETIC_HPP
#define ASM_ARITHMETIC_HPP

#include <cstdint>
#include <optional>
#include <format>

#include "assembler_types.hpp"
#include "result/result.hpp"
#include "gen/asm6502Parser.h"

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
    std::same_as<T, BinaryOperator> ||
    std::same_as<T, UnaryOperator> ||
    std::same_as<T, uint8_t> ||
    std::same_as<T, uint16_t> ||
    std::same_as<T, char> ||
    std::same_as<T, PcStar> ||
    std::same_as<T, std::string>;

class ArithmeticAtom {
public:
    template <typename T> requires(ArithmeticAtomType<T>)
    explicit ArithmeticAtom(const T& value)
        : value(value)
    {}

    constexpr auto get_type() const -> ArithAtomType
    {
        return static_cast<ArithAtomType>(value.index());
    }

    template <typename T>
    const T& get() const
        requires(ArithmeticAtomType<T>)
    {
        return std::get<T>(value);
    }

    constexpr auto format() const -> std::string
    {
        switch (get_type())
        {
        case ArithAtomType::BinaryOp:
            switch (std::get<BinaryOperator>(value))
            {
            case BinaryOperator::Add:
                return "+";
            case BinaryOperator::Subtract:
                return "-";
            case BinaryOperator::Multiply:
                return "*";
            case BinaryOperator::Divide:
            default:
                return "/";
            }
        case ArithAtomType::UnaryOp:
            switch (std::get<UnaryOperator>(value))
            {
            case UnaryOperator::Plus:
                return "+";
            case UnaryOperator::Minus:
                return "-";
            case UnaryOperator::LowByte:
                return "<";
            case UnaryOperator::HighByte:
            default:
                return ">";
            }
        case ArithAtomType::Byte:
            return std::format("0x{:02X}", std::get<uint8_t>(value));
        case ArithAtomType::Word:
            return std::format("0x{:04X}", std::get<uint16_t>(value));
        case ArithAtomType::Character:
            return std::format("'{}", std::get<char>(value));
        case ArithAtomType::PcStar:
            return "*";
        case ArithAtomType::Symbol:
        default:
            return std::get<std::string>(value);
        }
    }

private:
    ArithAtomV value;
};

auto make_number(
    Base base,
    int start_idx,
    const std::string &input) -> Result<int32_t, ParseError>;
auto make_byte(asm6502Parser::ByteContext* byte_context)
    -> Result<ArithmeticAtom, ParseError>;
auto make_word(asm6502Parser::MultibyteContext* word_context)
    -> Result<ArithmeticAtom, ParseError>;

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

    auto evaluate(const SymbolMap& symbol_map, uint16_t pc) -> Result<int32_t, ParseError>;

    auto format() const -> std::string;

    using Atom = ArithmeticAtom;
    using Expr = ArithmeticExpression;
    using SExpr = std::variant<Atom, std::unique_ptr<Expr>>;
    auto add_atom(Atom&& atom) -> void;
    auto add_expression(Expr&& nested_expression) -> void;

    using NumberContext = asm6502Parser::AtomContext;
    using BinaryOpContext = asm6502Parser::Binary_opContext;
    using UnaryOpContext = asm6502Parser::Unary_opContext;

protected:
    struct ArithmeticContext
    {
        std::optional<int32_t> rhs = {};
        std::optional<BinaryOperator> binary_op = {};
        std::optional<UnaryOperator> unary_op = {};
        std::string symbol = {};
        uint16_t pc = 0;
    };
    auto evaluate_init(
        size_t& idx,
        ArithmeticContext& context,
        const SymbolMap& symbol_map) -> Result<int32_t, ParseError>;
    auto evaluate_sub_expr(
        const SExpr& sub_expr,
        ArithmeticContext& context,
        const SymbolMap& symbol_map) -> std::optional<ParseError>;

    auto unary_expr(UnaryOperator op, int32_t rhs) -> int32_t;
    auto binary_expr(int32_t acc, BinaryOperator op, int32_t rhs) -> int32_t;
    auto handle_atom(Context* context) -> std::optional<ParseError>;
    auto handle_unary_op(UnaryOpContext* context) -> std::optional<ParseError>;
    auto handle_binary_op(BinaryOpContext* context) -> std::optional<ParseError>;
private:
    std::vector<SExpr> expression = {};
    bool symbols_encountered = false;
    bool words_encountered = false;
};

} // namespace mos6502


#endif
