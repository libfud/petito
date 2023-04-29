#include "asm_line.hpp"
#include "logger/logger.hpp"

namespace mos6502 {

constexpr InstructionLine::InstructionLine(
    uint16_t pc,
    OpName op_id,
    std::optional<std::string>&& label,
    std::optional<std::string>&& comment)
    :
    pc{pc},
    op_id{op_id},
    label{label},
    comment{comment}
{}

constexpr auto InstructionLine::format() const -> std::string
{
    return std::format(
        "{}{}{}",
        label != std::nullopt ? std::format("{}:\t", comment.value()) : "",
        format_instruction(),
        comment != std::nullopt ? std::format("\t;{}", comment.value()) : ""
    );
}

constexpr auto InstructionLine::has_label() const -> bool
{
    return label != std::nullopt;
}

constexpr auto InstructionLine::get_label() const -> const std::string&
{
    return label.value();
}

constexpr auto InstructionLine::size() const -> uint16_t
{
    return 1 + address_mode_num_bytes(address_mode());
}

auto InstructionLine::evaluate(const SymbolMap&) -> std::optional<AsmError>
{
    return {};
}

NOperandInstructionLine::NOperandInstructionLine(
    uint16_t pc,
    OpName op_id,
    std::optional<std::string>&& label,
    std::optional<std::string>&& comment,
    ArithmeticExpression&& expression)
    : InstructionLine{pc, op_id, std::move(label), std::move(comment)},
      expression{std::move(expression)}
{
}

auto OneOperandInstructionLine::evaluate(const SymbolMap& symbol_map) -> std::optional<AsmError>
{
    auto result = expression.evaluate(symbol_map, pc);
    if (result.is_err())
    {
        return result.get_err();
    }

    auto value = result.get_ok();
    if (value < 0 || value > 0xFF)
    {
        return AsmError::InvalidRange;
    }

    operand = value;
    return {};
}

auto TwoOperandInstructionLine::evaluate(const SymbolMap& symbol_map) -> std::optional<AsmError>
{
    auto result = expression.evaluate(symbol_map, pc);
    if (result.is_err())
    {
        return result.get_err();
    }

    auto value = result.get_ok();
    if (value < 0 || value > 0xFFFF)
    {
        return AsmError::InvalidRange;
    }

    operand_1 = value & 0xFF;
    operand_2 = (value >> 8) & 0xFF;
    return {};
}

auto RelativeInstructionLine::evaluate(const SymbolMap& symbol_map) -> std::optional<AsmError>
{
    auto result = expression.evaluate(symbol_map, pc);
    if (result.is_err())
    {
        return result.get_err();
    }

    auto value = result.get_ok();
    if (value < -127 || value > 128)
    {
        return AsmError::InvalidRange;
    }
    // ((lambda (x) (if (> x 127) (- (- 256 x)) x)) #xF4)
    operand = value & 0xFF;

    return {};
}

auto AsmInstructionLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> ParseResult
{
    if (line->assign() != nullptr)
    {
        return ParseResult::err(ParseError::LogicError);
    }

    auto* instruction_rule = line->instruction();
    if (!instruction_rule)
    {
        return ParseResult::err(ParseError::LogicError);
    }

    std::optional<std::string> label{};
    if (line->label())
    {
        label = line->label()->SYMBOL()->getText();
    }
    std::optional<std::string> comment{};
    if (line->comment())
    {
        comment = line->comment()->COMMENT()->getText();
    }

    AsmInstructionLine instruction{};
    instruction.parse(instruction_rule, pc, std::move(label), std::move(comment));

    return ParseResult::ok(instruction);
}

auto AsmInstructionLine::parse(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    if (rule->nop())
    {
        instruction = ImplicitInstructionLine{
            pc, OpName::NOP, std::move(label), std::move(comment)};
        return {};
    }

    if (rule->implicit())
    {
        return parse_implicit(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->acc())
    {
        return parse_acc(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->immediate())
    {
        return parse_immediate(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->x_index())
    {
        return parse_x_index(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->y_index())
    {
        return parse_y_index(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->x_indirect())
    {
        return parse_x_indirect(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->indirect_y())
    {
        return parse_indirect_y(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->absolute())
    {
        return parse_absolute(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->relative())
    {
        return parse_relative(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->jump())
    {
        return parse_jump(rule, pc, std::move(label), std::move(comment));
    }

    if (rule->jsr())
    {
        return parse_jsr(rule, pc, std::move(label), std::move(comment));
    }

    return {};
}

auto AsmInstructionLine::parse_implicit(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto* implicit_rule = rule->implicit();
    std::string implicit_name{implicit_rule->getText()};
    auto invalid_mnemonic = check_mnemonic(implicit_name, AddressMode::IMPL);
    if (invalid_mnemonic.is_err())
    {
        return invalid_mnemonic.get_err();
    }
    auto op_id = invalid_mnemonic.get_ok();

    instruction = ImplicitInstructionLine{pc, op_id, std::move(label), std::move(comment)};
    return {};
}

auto AsmInstructionLine::parse_acc(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto* acc_rule = rule->acc();
    std::string acc_name{acc_rule->shift()->SHIFT()->getText()};
    auto invalid_mnemonic = check_mnemonic(acc_name, AddressMode::A);
    if (invalid_mnemonic.is_err())
    {
        return invalid_mnemonic.get_err();
    }
    auto op_id = invalid_mnemonic.get_ok();
    instruction = AccInstructionLine{pc, op_id, std::move(label), std::move(comment)};
    return {};
}

auto AsmInstructionLine::parse_immediate(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto* context = rule->immediate();
    std::string imm_name{context->mnemonic()->MNEMONIC()->getText()};

    auto invalid_mnemonic = check_mnemonic(imm_name, AddressMode::IMM);
    if (invalid_mnemonic.is_err())
    {
        return invalid_mnemonic.get_err();
    }
    auto op_id = invalid_mnemonic.get_ok();

    auto arith_result = ArithmeticExpression::make(context->expression());
    if (arith_result.is_err())
    {
        return arith_result.get_err();
    }
    instruction = ImmediateInstructionLine{
        pc, op_id, std::move(label), std::move(comment), arith_result.get_ok()};

    return {};
}

auto AsmInstructionLine::parse_x_index(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto opcode_info_result = parse_xy_index(rule, AddressMode::ZPG_X, AddressMode::ABS_X);
    if (opcode_info_result.is_err())
    {
        return opcode_info_result.get_err();
    }
    auto opcode_info = opcode_info_result.get_ok();
    if (opcode_info.address_mode == AddressMode::ZPG_X)
    {
        instruction = ZeroPageXInstructionLine{
            pc,
            opcode_info.op_id,
            std::move(label),
            std::move(comment),
            std::move(opcode_info.expression)};
    }
    else
    {
        instruction = AbsoluteXInstructionLine{
            pc,
            opcode_info.op_id,
            std::move(label),
            std::move(comment),
            std::move(opcode_info.expression)};
    }
    return {};
}

auto AsmInstructionLine::parse_y_index(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto opcode_info_result = parse_xy_index(rule, AddressMode::ZPG_Y, AddressMode::ABS_Y);
    if (opcode_info_result.is_err())
    {
        return opcode_info_result.get_err();
    }
    auto opcode_info = opcode_info_result.get_ok();
    if (opcode_info.address_mode == AddressMode::ZPG_Y)
    {
        instruction = ZeroPageYInstructionLine{
            pc,
            opcode_info.op_id,
            std::move(label),
            std::move(comment),
            std::move(opcode_info.expression)};
    }
    else
    {
        instruction = AbsoluteYInstructionLine{
            pc,
            opcode_info.op_id,
            std::move(label),
            std::move(comment),
            std::move(opcode_info.expression)};
    }
    return {};
}

auto AsmInstructionLine::parse_xy_index(
        InstructionContext* rule,
        AddressMode zpg_mode,
        AddressMode abs_mode) -> Result<OpInfo, ParseError>
{
    using RetType = Result<OpInfo, ParseError>;
    std::string name;
    auto* context = rule->x_index();
    if (context->mnemonic())
    {
        name = context->mnemonic()->MNEMONIC()->getText();
    }
    else
    {
        name = context->shift()->SHIFT()->getText();
    }

    auto zpg_invalid_mnemonic = check_mnemonic(name, zpg_mode);
    auto abs_invalid_mnemonic = check_mnemonic(name, abs_mode);

    if (zpg_invalid_mnemonic.is_err() && abs_invalid_mnemonic.is_err())
    {
        return RetType::err(zpg_invalid_mnemonic.get_err());
    }

    auto arith_result = ArithmeticExpression::make(context->expression());
    if (arith_result.is_err())
    {
        return RetType::err(arith_result.get_err());
    }
    auto expression = arith_result.get_ok();
    if (!(expression.has_symbols()) ||
        expression.has_words() ||
        zpg_invalid_mnemonic.is_err())
    {
        SymbolMap empty_map{};
        auto res = expression.evaluate(empty_map, 0);
        if (res.is_err())
        {
            return RetType::err(ParseError::BadArithmetic);
        }
        if (res.get_ok() < 0xFF)
        {
            return RetType::ok({zpg_invalid_mnemonic.get_ok(), zpg_mode, expression});
        }
    }

    return RetType::ok({abs_invalid_mnemonic.get_ok(), abs_mode, expression});
}

auto AsmInstructionLine::parse_x_indirect(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto* context = rule->x_indirect();
    return parse_helper(
        instruction_line_wrapper<XIndirectInstructionLine>,
        context,
        AddressMode::X_IND,
        pc,
        std::move(label),
        std::move(comment));
}

auto AsmInstructionLine::parse_indirect_y(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto* context = rule->indirect_y();
    return parse_helper(
        instruction_line_wrapper<IndirectYInstructionLine>,
        context,
        AddressMode::IND_Y,
        pc,
        std::move(label),
        std::move(comment));
    return {};
}

auto AsmInstructionLine::parse_absolute(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto* context = rule->absolute();
    return parse_helper(
        instruction_line_wrapper<AbsoluteInstructionLine>,
        context,
        AddressMode::ABS,
        pc,
        std::move(label),
        std::move(comment));
}

auto AsmInstructionLine::parse_relative(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto* context = rule->relative();
    std::string name{context->BRANCH()->getText()};

    auto invalid_mnemonic = check_mnemonic(name, AddressMode::REL);

    if (invalid_mnemonic.is_err())
    {
        return invalid_mnemonic.get_err();
    }
    auto op_id = invalid_mnemonic.get_ok();

    auto arith_result = ArithmeticExpression::make(context->expression());
    if (arith_result.is_err())
    {
        return arith_result.get_err();
    }
    auto expression = arith_result.get_ok();
    instruction = RelativeInstructionLine{
        pc, op_id, std::move(label), std::move(comment), std::move(expression)};
    return {};
}

auto AsmInstructionLine::parse_jump(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto* context = rule->jump();
    auto op_id = OpName::JMP;

    auto arith_result = ArithmeticExpression::make(context->expression());
    if (arith_result.is_err())
    {
        return arith_result.get_err();
    }
    auto expression = arith_result.get_ok();
    if (context->LPAREN())
    {
        instruction = IndirectInstructionLine{
            pc, op_id, std::move(label), std::move(comment), std::move(expression)};
    }
    else
    {
        instruction = AbsoluteInstructionLine{
            pc, op_id, std::move(label), std::move(comment), std::move(expression)};
    }

    return {};
}

auto AsmInstructionLine::parse_jsr(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
{
    auto* context = rule->jump();
    auto op_id = OpName::JSR;
    auto arith_result = ArithmeticExpression::make(context->expression());
    if (arith_result.is_err())
    {
        return arith_result.get_err();
    }
    auto expression = arith_result.get_ok();
    instruction = AbsoluteInstructionLine{
        pc, op_id, std::move(label), std::move(comment), std::move(expression)};
    return {};
}

auto AsmInstructionLine::check_mnemonic(
    const std::string& name,
    AddressMode mode) -> Result<OpName, ParseError>
{
    using RetType = Result<OpName, ParseError>;
    if (!MNEMONIC_MAP.contains(name))
    {
        logger::error("Mnemonic {} not in MNEMONIC_MAP", name);
        return RetType::err(ParseError::InvalidOpIdParse);
    }
    auto op_id = MNEMONIC_MAP.at(name);
    if (!ADDRESS_MODE_MAP.at(mode).contains(op_id))
    {
        logger::error(
            "Address mode {} does not have {}",
            static_cast<uint8_t>(mode),
            name);
        return RetType::err(ParseError::InvalidOpIdParse);
    }

    return RetType::ok(op_id);
}

auto AsmInstructionLine::complete_decode(SymbolMap& symbol_map) -> std::optional<ParseError>
{
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
    default:
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
