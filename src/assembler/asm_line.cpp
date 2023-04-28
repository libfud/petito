#include "asm_line.hpp"
#include "logger/logger.hpp"

namespace mos6502 {

auto ArithmeticAtom::get_type() const -> ArithAtomType
{
    return static_cast<ArithAtomType>(value.index());
}

auto make_number(Base base, int start_idx, const std::string &input) -> Result<int32_t, ParseError>
{
    using RetType = Result<int32_t, ParseError>;
    const std::map<char, int8_t>& char_map = BASE_MAP.at(base);

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
    uint16_t pc) -> Result<int32_t, AsmError>
{
    using RetType = Result<int32_t, AsmError>;
    using AtomType = ArithAtomType;

    std::optional<UnaryOperator> unary_op{};
    std::optional<BinaryOperator> binary_op{};
    std::optional<uint16_t> rhs{};
    std::string symbol;

    size_t idx = 0;
    int32_t acc = 0;

    auto evaluate_sub_expr = [&](const SExpr& sub_expr) -> std::optional<AsmError> {
        if (sub_expr.index() == 0)
        {
            const auto& atom = std::get<Atom>(sub_expr);
            switch (atom.get_type())
            {
            case AtomType::BinaryOp:
                binary_op = atom.get<BinaryOperator>();
                break;
            case AtomType::UnaryOp:
                unary_op = atom.get<UnaryOperator>();
                break;
            case AtomType::Byte:
                rhs = atom.get<uint8_t>();
                break;
            case AtomType::Word:
                rhs = atom.get<uint16_t>();
                break;
            case AtomType::Character:
                rhs = static_cast<uint8_t>(atom.get<char>());
                break;
            case AtomType::PcStar:
                rhs = pc;
                break;
            case AtomType::Symbol:
                symbol = atom.get<std::string>();
                if (!symbol_map.contains(symbol))
                {
                    logger::error("Undefined symbol {} ", symbol);
                    return AsmError::SymbolUndefined;
                }
                rhs = symbol_map.at(symbol);
                break;
            }
        }
        else
        {
            auto result = std::get<std::unique_ptr<Expr>>(sub_expr)->evaluate(symbol_map, pc);
            if (result.is_err())
            {
                return result.get_err();
            }
            rhs = result.get_ok();
        }
        return {};
    };

    {
        const auto& sub_expr = expression[idx];
        idx++;
        const auto res = evaluate_sub_expr(sub_expr);
        if (res != std::nullopt)
        {
            return RetType::err(res.value());
        }
    }

    if (binary_op != std::nullopt)
    {
        return RetType::err(AsmError::BadEvaluation);
    }
    if (unary_op != std::nullopt)
    {
        const auto& sub_expr = expression[idx];
        idx++;
        const auto res = evaluate_sub_expr(sub_expr);
        if (res != std::nullopt)
        {
            return RetType::err(res.value());
        }
        if (rhs == std::nullopt)
        {
            return RetType::err(AsmError::BadEvaluation);
        }
        acc = unary_expr(unary_op.value(), rhs.value());
        unary_op = {};
        rhs = {};
    }
    else
    {
        acc = rhs.value();
        rhs = {};
    }

    while (idx < expression.size())
    {
        // expect a binary expression
        const auto& binary_op_expr = expression[idx];
        idx++;
        auto res = evaluate_sub_expr(binary_op_expr);
        if (res != std::nullopt)
        {
            return RetType::err(res.value());
        }

        if (binary_op == std::nullopt)
        {
            return RetType::err(AsmError::BadEvaluation);
        }

        // next may either be a unary operator or a value
        const auto& sub_expr_0 = expression[idx];
        idx++;
        res = evaluate_sub_expr(sub_expr_0);
        if (res != std::nullopt)
        {
            return RetType::err(res.value());
        }
        if (unary_op != std::nullopt)
        {
            // next must be a value
            const auto& sub_expr = expression[idx];
            idx++;
            const auto res = evaluate_sub_expr(sub_expr);
            if (res != std::nullopt)
            {
                return RetType::err(res.value());
            }
            if (rhs == std::nullopt)
            {
                return RetType::err(AsmError::BadEvaluation);
            }
            rhs = unary_expr(unary_op.value(), rhs.value());
            unary_op = {};
        }
        if (rhs == std::nullopt)
        {
            return RetType::err(AsmError::BadEvaluation);
        }

        acc = binary_expr(acc, binary_op.value(), rhs.value());
        binary_op = {};
        rhs = {};
    }

    return RetType::ok(acc);
}

auto ArithmeticExpression::unary_expr(UnaryOperator op, uint16_t rhs) -> int32_t
{
    switch (op)
    {
    case UnaryOperator::Plus:
        return rhs;
    case UnaryOperator::Minus:
        return -static_cast<int32_t>(rhs);
    case UnaryOperator::LowByte:
        return rhs & 0xFF;
    case UnaryOperator::HighByte:
    default:
        return (rhs >> 8) & 0xFF;
    }
}

auto ArithmeticExpression::binary_expr(int32_t acc, BinaryOperator op, uint16_t rhs) -> int32_t
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

    auto check_expr_size = [&](auto expected_size) -> std::optional<ParseError> {
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

auto Line::make(asm6502Parser::LineContext* line) -> LineResult
{
    Line instruction;

    auto* label_rule = line->label();
    auto* comment_rule = line->comment();
    auto* instruction_rule = line->instruction();
    auto* assign_rule = line->assign();

    if (comment_rule != nullptr)
    {
        auto* comment_token = comment_rule->COMMENT();
        auto comment_text = comment_token->getText();
        instruction.comment = comment_text;
        instruction.line_type = LineType::Comment;
    }

    if (assign_rule != nullptr)
    {

        auto expr_result = ArithmeticExpression::make(assign_rule->expression());
        if (expr_result.is_err())
        {
            return LineResult::err(AsmError::BadAssign);
        }
        instruction.arithmetic_expression = expr_result.get_ok();
        instruction.symbol = assign_rule->SYMBOL()->getText();
        instruction.line_type = LineType::Assign;
        return LineResult::ok(instruction);
    }

    if (label_rule != nullptr)
    {
        instruction.label = label_rule->getText();
        instruction.line_type = LineType::Label;
    }

    if (instruction_rule != nullptr)
    {
        auto res = instruction.handle_instruction_rule(instruction_rule);
        if (res != std::nullopt)
        {
            return LineResult::err(AsmError::BadParse);
        }
        instruction.line_type = LineType::Instruction;
    }

    return LineResult::ok(instruction);
}

auto Line::has_label() const -> bool { return label != std::nullopt; }

auto Line::get_label() const -> const std::string&
{
    return label.value();
}

auto Line::size() const -> uint16_t
{
    switch (line_type)
    {
    case LineType::Instruction:
        return address_mode_num_bytes(address_mode.value());
    case LineType::Directive:
    case LineType::Label:
    case LineType::Assign:
    case LineType::Comment:
    case LineType::Empty:
        return 0;
    }
}

auto Line::complete_decode(
    SymbolMap& symbol_map,
    uint16_t pc) -> std::optional<AsmError>
{
    if (arithmetic_expression == std::nullopt)
    {
        return {};
    }

    auto set_operands = [&](int32_t min_val, int32_t max_val) -> std::optional<AsmError> {
        auto result = arithmetic_expression.value().evaluate(symbol_map, pc);
        if (result.is_err())
        {
            return result.get_err();
        }
        auto value = result.get_ok();
        if (value < min_val || value > max_val)
        {
            return AsmError::InvalidRange;
        }
        operands.push_back(value & 0xFF);
        operands.push_back((value >> 8) & 0xFF);
        return {};
    };

    switch (line_type)
    {
    case LineType::Instruction:
        switch (address_mode.value())
        {
        case AddressMode::IMPL:
        case AddressMode::NI:
        case AddressMode::A:
            break;
        case AddressMode::ABS:
        case AddressMode::IND:
        case AddressMode::ABS_X:
        case AddressMode::ABS_Y:
            return set_operands(0, 0xFFFF);
        case AddressMode::REL:
            return set_operands(-128, 127);
        case AddressMode::X_IND:
        case AddressMode::IND_Y:
        case AddressMode::IMM:
        case AddressMode::ZPG:
        case AddressMode::ZPG_X:
        case AddressMode::ZPG_Y:
            return set_operands(0, 0xFF);
        }
        return {};
    case LineType::Assign:
        if (symbol_map.contains(symbol.value()))
        {
            return AsmError::SymbolRedefined;
        }
        else
        {
            auto result = arithmetic_expression.value().evaluate(symbol_map, pc);
            if (result.is_err())
            {
                return result.get_err();
            }
            symbol_map[symbol.value()] = result.get_ok();
            symbol_value = symbol_map[symbol.value()];
        }
        return {};
    case LineType::Directive:
    case LineType::Label:
        if (symbol_map.contains(symbol.value()))
        {
            return AsmError::SymbolRedefined;
        }
        {
            symbol_map[label.value()] = pc;
            symbol_value.value() = symbol_map[symbol.value()];
        }
        return {};
    case LineType::Comment:
    case LineType::Empty:
    default:
        return {};
    }
}

auto Line::handle_instruction_rule(
    asm6502Parser::InstructionContext* rule) -> BuilderResult
{
    if (rule->nop())
    {
        op_id = OpName::NOP;
        address_mode = AddressMode::IMPL;
        return {};
    }

    if (rule->implicit())
    {
        auto* implicit_rule = rule->implicit();
        std::string implicit_name{implicit_rule->getText()};
        auto invalid_mnemonic = check_mnemonic(implicit_name, AddressMode::IMPL);
        if (invalid_mnemonic != std::nullopt)
        {
            return invalid_mnemonic;
        }

        return {};
    }

    if (rule->acc())
    {
        auto* acc_rule = rule->acc();
        std::string acc_name{acc_rule->shift()->SHIFT()->getText()};
        auto invalid_mnemonic = check_mnemonic(acc_name, AddressMode::A);
        if (invalid_mnemonic != std::nullopt)
        {
            return invalid_mnemonic;
        }
        return {};
    }

    if (rule->immediate())
    {
        return handle_immediate_rule(rule->immediate());
    }

    if (rule->x_index())
    {
        return handle_x_index_rule(rule->x_index());
    }

    if (rule->y_index())
    {
        return handle_y_index_rule(rule->y_index());
    }

    if (rule->x_indirect())
    {
        return helper(rule->x_indirect(), AddressMode::X_IND);
    }

    if (rule->indirect_y())
    {
        return helper(rule->indirect_y(), AddressMode::IND_Y);
    }

    if (rule->absolute())
    {
        return helper(rule->absolute(), AddressMode::ABS);
    }

    if (rule->relative())
    {
        return handle_relative_rule(rule->relative());
    }

    if (rule->jump())
    {
        return handle_jump_rule(rule->jump());
    }

    if (rule->jsr())
    {
        return handle_jsr_rule(rule->jsr());
    }

    return {};
}

auto Line::handle_immediate_rule(
    asm6502Parser::ImmediateContext* rule) -> BuilderResult
{
    std::string imm_name{rule->mnemonic()->MNEMONIC()->getText()};

    auto invalid_mnemonic = check_mnemonic(imm_name, AddressMode::IMM);
    if (invalid_mnemonic != std::nullopt)
    {
        return invalid_mnemonic;
    }

    auto arith_result = handle_arithmetic(rule);
    if (arith_result != std::nullopt)
    {
        return arith_result;
    }

    return {};
}

auto Line::handle_x_index_rule(
    asm6502Parser::X_indexContext* rule) -> BuilderResult
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

    auto zpx_invalid_mnemonic = check_mnemonic(name, AddressMode::ZPG_X);
    auto abs_x_invalid_mnemonic = check_mnemonic(name, AddressMode::ABS_X);

    if (zpx_invalid_mnemonic != std::nullopt && abs_x_invalid_mnemonic != std::nullopt)
    {
        return zpx_invalid_mnemonic;
    }

    auto arith_result = handle_arithmetic(rule);
    if (arith_result != std::nullopt)
    {
        return arith_result;
    }

    if (!(arithmetic_expression.value().has_symbols()) ||
        arithmetic_expression.value().has_words() ||
        zpx_invalid_mnemonic != std::nullopt)
    {
        SymbolMap empty_map{};
        auto res = arithmetic_expression.value().evaluate(empty_map, 0);
        if (res.is_err())
        {
            return ParseError::BadArithmetic;
        }
        if (res.get_ok() < 0xFF)
        {
            address_mode = AddressMode::ZPG_X;
        }
    }

    return {};
}

auto Line::handle_y_index_rule(
    asm6502Parser::Y_indexContext* rule) -> BuilderResult
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

    auto zpy_invalid_mnemonic = check_mnemonic(name, AddressMode::ZPG_Y);
    auto abs_y_invalid_mnemonic = check_mnemonic(name, AddressMode::ABS_Y);

    if (zpy_invalid_mnemonic != std::nullopt && abs_y_invalid_mnemonic != std::nullopt)
    {
        return zpy_invalid_mnemonic;
    }

    auto arith_result = handle_arithmetic(rule);
    if (arith_result != std::nullopt)
    {
        return arith_result;
    }

    if (!(arithmetic_expression.value().has_symbols()) ||
        arithmetic_expression.value().has_words() ||
        zpy_invalid_mnemonic != std::nullopt)
    {
        SymbolMap empty_map{};
        auto res = arithmetic_expression.value().evaluate(empty_map, 0);
        if (res.is_err())
        {
            return ParseError::BadArithmetic;
        }
        if (res.get_ok() < 0xFF)
        {
            address_mode = AddressMode::ZPG_Y;
        }
    }

    return {};
}

auto Line::handle_relative_rule(
    asm6502Parser::RelativeContext* rule) -> BuilderResult
{
    std::string name{rule->BRANCH()->getText()};

    auto invalid_mnemonic = check_mnemonic(name, AddressMode::REL);

    if (invalid_mnemonic != std::nullopt)
    {
        return invalid_mnemonic;
    }

    auto arith_result = handle_arithmetic(rule);
    if (arith_result != std::nullopt)
    {
        return arith_result;
    }

    return {};
}

auto Line::handle_jump_rule(
    asm6502Parser::JumpContext* rule) -> BuilderResult
{
    op_id = OpName::JMP;
    address_mode = AddressMode::ABS;
    if (rule->LPAREN())
    {
        address_mode = AddressMode::IND;
    }

    auto arith_result = handle_arithmetic(rule);
    if (arith_result != std::nullopt)
    {
        return arith_result;
    }

    return {};
}

auto Line::handle_jsr_rule(
    asm6502Parser::JsrContext* rule) -> BuilderResult
{
    op_id = OpName::JSR;
    address_mode = AddressMode::ABS;

    auto arith_result = handle_arithmetic(rule);
    if (arith_result != std::nullopt)
    {
        return arith_result;
    }

    return {};
}

auto Line::check_mnemonic(const std::string& name, AddressMode mode) -> BuilderResult
{
    if (!MNEMONIC_MAP.contains(name))
    {
        logger::error("Mnemonic {} not in MNEMONIC_MAP", name);
        return ParseError::InvalidOpIdParse;
    }
    op_id = MNEMONIC_MAP.at(name);
    if (!ADDRESS_MODE_MAP.at(mode).contains(op_id.value()))
    {
        logger::error(
            "Address mode {} does not have {}",
            static_cast<uint8_t>(mode),
            name);
        return ParseError::InvalidOpIdParse;
    }

    address_mode = mode;
    return {};
}

auto Line::format() const -> std::string
{
    switch (line_type)
    {
    case LineType::Instruction:
        return instruction_format();
    case LineType::Comment:
        return comment.value();
    case LineType::Label:
        return std::format("{}", label.value());
    case LineType::Assign:
        return std::format("{} EQU ${:02X}", symbol.value(), symbol_value.value());
    case LineType::Directive:
    case LineType::Empty:
    default:
        break;
    }
    return "";
}

auto Line::instruction_format() const -> std::string
{
    switch (address_mode.value())
    {
    case AddressMode::IMPL:
    case AddressMode::NI:
    case AddressMode::A:
        return std::format("{}", opid_to_name(op_id.value()));
    case AddressMode::ABS:
        return std::format(
            "{} ${:02X}{:02X}",
            opid_to_name(op_id.value()),
            operands[1],
            operands[0]);
    case AddressMode::IND:
        return std::format(
            "{} (${:02X}{:02X})",
            opid_to_name(op_id.value()),
            operands[1],
            operands[0]);
    case AddressMode::X_IND:
        return std::format(
            "{} ({:02X},X)",
            opid_to_name(op_id.value()),
            operands[0]);
    case AddressMode::IND_Y:
        return std::format(
            "{} (${:02X}),Y",
            opid_to_name(op_id.value()),
            operands[0]);
    case AddressMode::ABS_X:
        return std::format(
            "{} ${:02X}{:02X},X",
            opid_to_name(op_id.value()),
            operands[1],
            operands[0]);
    case AddressMode::ABS_Y:
        return std::format(
            "{} ${:02X}{:02X},Y",
            opid_to_name(op_id.value()),
            operands[1],
            operands[0]);
    case AddressMode::REL:
    case AddressMode::ZPG:
        return std::format(
            "{} ${:02X}",
            opid_to_name(op_id.value()),
            operands[0]);
    case AddressMode::IMM:
        return std::format(
            "{} #${:02X}",
            opid_to_name(op_id.value()),
            operands[0]);
    case AddressMode::ZPG_X:
        return std::format(
            "{} ${:02X},X",
            opid_to_name(op_id.value()),
            operands[0]);
    case AddressMode::ZPG_Y:
    default:
        return std::format(
            "{} ${:02X},Y",
            opid_to_name(op_id.value()),
            operands[0]);
    }
}

} // namespace mos6502
