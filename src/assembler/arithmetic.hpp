#ifndef ASM_ARITHMETIC_HPP
#define ASM_ARITHMETIC_HPP

#include <cstdint>
#include <optional>

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

} // namespace mos6502


#endif
