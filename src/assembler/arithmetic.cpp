#include <format>

#include "arithmetic.hpp"
#include "logger/logger.hpp"

namespace mos6502 {

auto make_number(Base base, int start_idx, const std::string &input) -> Result<int32_t, ParseError>
{
    using RetType = Result<int32_t, ParseError>;
    const auto& char_map = BASE_MAP.at(base);

    int32_t acc = 0;
    for (int idx = start_idx; idx < input.length(); ++idx)
    {
        auto letter = input[idx];

        if (!char_map.contains(letter))
        {
            return RetType::err(ParseError::BadNumber);
        }
        acc = acc * static_cast<uint8_t>(base) + char_map.at(letter);
    }
    return RetType::ok(acc);
}

auto make_byte(asm6502Parser::ByteContext* byte_context) -> Result<ArithmeticAtom, ParseError>
{
    using RetType = Result<ArithmeticAtom, ParseError>;
    std::string byte_string{};
    int start_index{};
    Base base{};
    if (byte_context->HEX_BYTE())
    {
        byte_string = byte_context->HEX_BYTE()->getText();
        start_index = byte_string.starts_with("0x") ? 2 : 1;
        base = Base::Hex;
    }
    else if (byte_context->DECIMAL_BYTE())
    {
        byte_string = byte_context->DECIMAL_BYTE()->getText();
        start_index = byte_string.starts_with("0d") ? 2 : 0;
        base = Base::Decimal;
    }
    else if (byte_context->OCTAL_BYTE())
    {
        byte_string = byte_context->OCTAL_BYTE()->getText();
        start_index = byte_string.starts_with("0o") ? 2 : 1;
        base = Base::Octal;
    }
    else if (byte_context->BINARY_BYTE())
    {
        byte_string = byte_context->BINARY_BYTE()->getText();
        start_index = byte_string.starts_with("0b") ? 2 : 1;
        base = Base::Binary;
    }
    else
    {
        return RetType::err(ParseError::LogicError);
    }

    auto result = make_number(base, start_index, byte_string);
    if (result.is_err())
    {
        return RetType::err(result.get_err());
    }
    auto num = result.get_ok();
    if (num > 0xFF)
    {
        return RetType::err(ParseError::BadNumber);
    }
    return RetType::ok(ArithmeticAtom(static_cast<uint8_t>(num & 0xFF)));
}

auto make_word(asm6502Parser::MultibyteContext* word_context) -> Result<ArithmeticAtom, ParseError>
{
    using RetType = Result<ArithmeticAtom, ParseError>;
    std::string word_string{};
    int start_index{};
    Base base{};
    if (word_context->HEX_NUMBER())
    {
        word_string = word_context->HEX_NUMBER()->getText();
        start_index = word_string.starts_with("0x") ? 2 : 1;
        base = Base::Hex;
    }
    else if (word_context->DECIMAL_NUMBER())
    {
        word_string = word_context->DECIMAL_NUMBER()->getText();
        start_index = word_string.starts_with("0d") ? 2 : 0;
        base = Base::Decimal;
    }
    else if (word_context->OCTAL_NUMBER())
    {
        word_string = word_context->OCTAL_NUMBER()->getText();
        start_index = word_string.starts_with("0o") ? 2 : 1;
        base = Base::Octal;
    }
    else if (word_context->BINARY_NUMBER())
    {
        word_string = word_context->BINARY_NUMBER()->getText();
        start_index = word_string.starts_with("0b") ? 2 : 1;
        base = Base::Binary;
    }
    else
    {
        return RetType::err(ParseError::LogicError);
    }

    auto result = make_number(base, start_index, word_string);
    if (result.is_err())
    {
        return RetType::err(result.get_err());
    }
    auto num = result.get_ok();
    if (num > 0xFFFF)
    {
        return RetType::err(ParseError::BadNumber);
    }
    return RetType::ok(ArithmeticAtom(static_cast<uint16_t>(num & 0xFFFF)));
}

ArithmeticExpression::ArithmeticExpression(const ArithmeticExpression& expr)
    : expression{},
      symbols_encountered{expr.symbols_encountered},
      words_encountered{expr.words_encountered}
{
    expression.reserve(expr.expression.size());
    for (const auto& sub_expr : expr.expression)
    {
        if (sub_expr.index() == 0)
        {
            expression.push_back(std::get<Atom>(sub_expr));
        }
        else
        {
            expression.push_back(
                std::make_unique<Expr>(*std::get<std::unique_ptr<Expr>>(sub_expr)));
        }
    }
}

ArithmeticExpression::ArithmeticExpression(ArithmeticExpression&& expr)
    : expression(std::move(expr.expression)),
      symbols_encountered(expr.symbols_encountered),
      words_encountered(expr.words_encountered)
{
}

ArithmeticExpression& ArithmeticExpression::operator=(const ArithmeticExpression& expr)
{
    if (this == &expr)
    {
        return *this;
    }

    expression.reserve(expr.expression.size());
    for (const auto& sub_expr : expr.expression)
    {
        if (sub_expr.index() == 0)
        {
            expression.push_back(std::get<Atom>(sub_expr));
        }
        else
        {
            expression.push_back(
                std::make_unique<Expr>(*std::get<std::unique_ptr<Expr>>(sub_expr)));
        }
    }
    symbols_encountered = expr.symbols_encountered;
    words_encountered = expr.words_encountered;

    return *this;
}

ArithmeticExpression& ArithmeticExpression::operator=(ArithmeticExpression&& expr)
{
    symbols_encountered = expr.symbols_encountered;
    words_encountered = expr.words_encountered;
    expression = std::move(expr.expression);
    return *this;
}

auto ArithmeticExpression::has_symbols() const -> bool { return symbols_encountered; }

auto ArithmeticExpression::has_words() const -> bool { return words_encountered; }

auto ArithmeticExpression::evaluate(
    const SymbolMap& symbol_map,
    uint16_t pc) -> Result<int32_t, ParseError>
{
    using RetType = Result<int32_t, ParseError>;

    ArithmeticContext context{};
    context.pc = pc;

    size_t idx = 0;
    auto init_result = evaluate_init(idx, context, symbol_map);
    if (init_result.is_err())
    {
        return init_result;
    }
    int32_t acc = init_result.get_ok();

    while (idx < expression.size())
    {
        // expect a binary expression
        const auto& binary_op_expr = expression[idx];
        idx++;
        auto res = evaluate_sub_expr(binary_op_expr, context, symbol_map);
        if (res != std::nullopt)
        {
            return RetType::err(res.value());
        }

        if (context.binary_op == std::nullopt)
        {
            return RetType::err(ParseError::BadEvaluation);
        }

        // next may either be a unary operator or a value
        const auto& sub_expr_0 = expression[idx];
        idx++;
        res = evaluate_sub_expr(sub_expr_0, context, symbol_map);
        if (res != std::nullopt)
        {
            return RetType::err(res.value());
        }
        if (context.unary_op != std::nullopt)
        {
            // next must be a value
            const auto& sub_expr = expression[idx];
            idx++;
            const auto res = evaluate_sub_expr(sub_expr, context, symbol_map);
            if (res != std::nullopt)
            {
                return RetType::err(res.value());
            }
            if (context.rhs == std::nullopt)
            {
                return RetType::err(ParseError::BadEvaluation);
            }
            context.rhs = unary_expr(context.unary_op.value(), context.rhs.value());
            context.unary_op = {};
        }
        if (context.rhs == std::nullopt)
        {
            return RetType::err(ParseError::BadEvaluation);
        }

        acc = binary_expr(acc, context.binary_op.value(), context.rhs.value());
        context.binary_op = {};
        context.rhs = {};
    }

    return RetType::ok(acc);
}

auto ArithmeticExpression::evaluate_init(
    size_t& idx,
    ArithmeticContext& context,
    const SymbolMap& symbol_map) -> Result<int32_t, ParseError>
{
    using RetType = Result<int32_t, ParseError>;
    int32_t acc = 0;

    // Get the first atom.
    idx = 0;
    const auto first_sub_expr_res = evaluate_sub_expr(expression[idx], context, symbol_map);
    idx = 1;
    if (first_sub_expr_res != std::nullopt)
    {
        return RetType::err(first_sub_expr_res.value());
    }

    // A leading binary operation is illegal as there is no LHS (accumulator) yet.
    if (context.binary_op != std::nullopt)
    {
        return RetType::err(ParseError::BadEvaluation);
    }
    // A leading unary operation is legal if the next atom is a value.
    if (context.unary_op != std::nullopt)
    {
        const auto& sub_expr = expression[idx];
        idx++;
        const auto res = evaluate_sub_expr(sub_expr, context, symbol_map);
        if (res != std::nullopt)
        {
            return RetType::err(res.value());
        }
        // No value found - no viable evaluation is possible.
        if (context.rhs == std::nullopt)
        {
            return RetType::err(ParseError::BadEvaluation);
        }
        acc = unary_expr(context.unary_op.value(), context.rhs.value());
        // Clear the operands.
        context.unary_op = {};
        context.rhs = {};
    }
    // No unary operation - set acc to RHS and clear RHS.
    else
    {
        acc = context.rhs.value();
        context.rhs = {};
    }

    return RetType::ok(acc);
}

auto ArithmeticExpression::evaluate_sub_expr(
    const SExpr& sub_expr,
    ArithmeticContext& context,
    const SymbolMap& symbol_map) -> std::optional<ParseError>
{
    using AtomType = ArithAtomType;

    if (sub_expr.index() == 0)
    {
        const auto& atom = std::get<Atom>(sub_expr);
        switch (atom.get_type())
        {
        case AtomType::BinaryOp:
            context.binary_op = atom.get<BinaryOperator>();
            break;
        case AtomType::UnaryOp:
            context.unary_op = atom.get<UnaryOperator>();
            break;
        case AtomType::Byte:
            context.rhs = atom.get<uint8_t>();
            break;
        case AtomType::Word:
            context.rhs = atom.get<uint16_t>();
            break;
        case AtomType::Character:
            context.rhs = static_cast<uint8_t>(atom.get<char>());
            break;
        case AtomType::PcStar:
            context.rhs = context.pc;
            break;
        case AtomType::Symbol:
        default:
            context.symbol = atom.get<std::string>();
            if (!symbol_map.contains(context.symbol))
            {
                logger::error("Undefined symbol {} ", context.symbol);
                return ParseError::SymbolUndefined;
            }
            context.rhs = symbol_map.at(context.symbol);
            break;
        }
    }
    else
    {
        auto result = std::get<std::unique_ptr<Expr>>(sub_expr)->evaluate(symbol_map, context.pc);
        if (result.is_err())
        {
            return result.get_err();
        }
        context.rhs = result.get_ok();
    }
    return {};
}

auto ArithmeticExpression::unary_expr(UnaryOperator op, int32_t rhs) -> int32_t
{
    switch (op)
    {
    case UnaryOperator::Plus:
        return rhs;
    case UnaryOperator::Minus:
        return -rhs;
    case UnaryOperator::LowByte:
        return rhs & 0xFF;
    case UnaryOperator::HighByte:
    default:
        return (rhs >> 8) & 0xFF;
    }
}

auto ArithmeticExpression::binary_expr(int32_t acc, BinaryOperator op, int32_t rhs) -> int32_t
{
    switch (op)
    {
    case BinaryOperator::Add:
        return acc + rhs;
    case BinaryOperator::Subtract:
        return acc - rhs;
    case BinaryOperator::Multiply:
        return acc * rhs;
    case BinaryOperator::Divide:
    default:
        return acc / rhs;
    }
}

auto ArithmeticExpression::format() const -> std::string
{
    std::string output{};
    for (const auto& elt : expression)
    {
        if (elt.index() == 0)
        {
            output += std::get<Atom>(elt).format();
        }
        else
        {
            output += std::format("[{}]", std::get<std::unique_ptr<Expr>>(elt)->format());
        }
    }
    return output;
}

auto ArithmeticExpression::add_atom(Atom&& atom) -> void
{
    expression.push_back(atom);
}

auto ArithmeticExpression::add_expression(Expr&& nested_expression) -> void
{
    symbols_encountered = nested_expression.has_symbols();
    words_encountered = nested_expression.has_words();
    expression.push_back(std::make_unique<Expr>(std::move(nested_expression)));
}

auto ArithmeticExpression::make(Context* context) -> ExprResult
{
    ArithmeticExpression expression{};

    auto check_expr_size = [&](size_t expected_size) -> std::optional<ParseError> {
        const auto& sub_expression_vec = context->expression();
        if (sub_expression_vec.size() != expected_size)
        {
            std::cerr <<
                std::format(
                    "Violated parse assumption for [expr], expected expr size={} got {}\n",
                    expected_size,
                    sub_expression_vec.size());
            return ParseError::BadArithmetic;
        }
        return {};
    };

    auto add_sub_expression = [&](auto* sub_expression) -> std::optional<ParseError> {
        auto expr_res = make(sub_expression);
        if (expr_res.is_err())
        {
            return expr_res.get_err();
        }
        expression.add_expression(std::move(expr_res.get_ok()));

        return {};
    };

    if (context->atom())
    {
        auto expect_zero = check_expr_size(0);
        if (expect_zero != std::nullopt)
        {
            return ExprResult::err(expect_zero.value());
        }
        auto result = expression.handle_atom(context);
        if (result != std::nullopt)
        {
            return ExprResult::err(result.value());
        }
    }
    else if (context->binary_op())
    {
        auto expect_two = check_expr_size(2);
        if (expect_two != std::nullopt)
        {
            return ExprResult::err(expect_two.value());
        }
        const auto& sub_expression_vec = context->expression();

        auto expr_1_res = add_sub_expression(sub_expression_vec[0]);
        if (expr_1_res != std::nullopt)
        {
            return ExprResult::err(expr_1_res.value());
        }

        auto result = expression.handle_binary_op(context->binary_op());
        if (result != std::nullopt)
        {
            return ExprResult::err(result.value());
        }

        auto expr_2_res = add_sub_expression(sub_expression_vec[1]);
        if (expr_2_res != std::nullopt)
        {
            return ExprResult::err(expr_2_res.value());
        }
    }
    else
    {
        if (!(context->LBRACKET() && context->RBRACKET()))
        {
            return ExprResult::err(ParseError::BadArithmetic);
        }

        auto expect_one = check_expr_size(1);
        if (expect_one != std::nullopt)
        {
            return ExprResult::err(expect_one.value());
        }

        if (context->unary_op())
        {
            auto unary_res = expression.handle_unary_op(context->unary_op());
            if (unary_res != std::nullopt)
            {
                return ExprResult::err(unary_res.value());
            }
        }

        const auto& sub_expression_vec = context->expression();

        auto expr_1_res = add_sub_expression(sub_expression_vec[0]);
        if (expr_1_res != std::nullopt)
        {
            return ExprResult::err(expr_1_res.value());
        }
    }

    return ExprResult::ok(expression);
}

auto ArithmeticExpression::handle_atom(Context* context) -> std::optional<ParseError>
{
    auto ctx = context->atom();
    if (ctx->unary_op())
    {
        auto res = handle_unary_op(ctx->unary_op());
        if (res != std::nullopt)
        {
            return res;
        }
    }

    if (ctx->byte())
    {
        auto result = make_byte(ctx->byte());
        if (result.is_err())
        {
            return result.get_err();
        }
        add_atom(result.get_ok());
        return {};
    }

    if (ctx->multibyte())
    {
        symbols_encountered = true;
        auto result = make_word(ctx->multibyte());
        if (result.is_err())
        {
            return result.get_err();
        }
        add_atom(result.get_ok());
        return {};
    }

    if (ctx->character())
    {
        add_atom(Atom{ctx->character()->getText()[1]});
    }

    if (ctx->STAR())
    {
        add_atom(Atom{PcStar{}});
    }

    if (ctx->SYMBOL())
    {
        symbols_encountered = true;
        add_atom(Atom{ctx->SYMBOL()->getText()});
    }

    return {};
}

auto ArithmeticExpression::handle_unary_op(UnaryOpContext* ctx) -> std::optional<ParseError>
{
    if (ctx->LOW_BYTE_VALUE())
    {
        add_atom(Atom{UnaryOperator::LowByte});
    }
    else if (ctx->HIGH_BYTE_VALUE())
    {
        add_atom(Atom{UnaryOperator::HighByte});
    }
    else if (ctx->PLUS())
    {
        add_atom(Atom{UnaryOperator::Plus});
    }
    else if (ctx->MINUS())
    {
        add_atom(Atom{UnaryOperator::Minus});
    }
    else
    {
        return ParseError::LogicError;
    }

    return {};
}

auto ArithmeticExpression::handle_binary_op(BinaryOpContext* ctx) -> std::optional<ParseError>
{
    if (ctx->PLUS())
    {
        add_atom(Atom{BinaryOperator::Add});
    }
    else if (ctx->MINUS())
    {
        add_atom(Atom{BinaryOperator::Subtract});
    }
    else if (ctx->STAR())
    {
        add_atom(Atom{BinaryOperator::Multiply});
    }
    else if (ctx->SLASH())
    {
        add_atom(Atom{BinaryOperator::Divide});
    }
    else
    {
        return ParseError::LogicError;
    }
    return {};
}

}
