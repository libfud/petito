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
    if (value < 0 || value > 0xFFFF)
    {
        return AsmError::InvalidRange;
    }

    target_address = value;
    int32_t offset = target_address - (pc + size());
    if (offset < -128 || offset > 127)
    {
        return AsmError::InvalidRange;
    }
    int8_t sign = offset < 0 ? -1 : 1;
    int8_t offset_8_bit = static_cast<int8_t>(sign * static_cast<int8_t>(std::abs(offset)));
    operand = *reinterpret_cast<const int8_t*>(&offset_8_bit);

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

auto AsmInstructionLine::evaluate(SymbolMap& symbol_map) -> std::optional<AsmError>
{
    return std::visit([&](auto& v){return v.evaluate(symbol_map);}, instruction);
}

auto AsmInstructionLine::format() const -> std::string {
    return std::visit([&](const auto& v){return v.format();}, instruction);
}

auto AsmInstructionLine::has_label() const -> bool {
    return std::visit([&](const auto& v){return v.has_label();}, instruction);
}

auto AsmInstructionLine::get_label() const -> const std::string&
{
    return std::visit(
        [&](const auto& v)->const std::string& { return v.get_label(); },
        instruction);
}

auto AsmInstructionLine::size() const -> uint16_t
{
    return std::visit([&](const auto& v){return v.size();}, instruction);
}

auto LabelLine::make(asm6502Parser::LineContext* context, uint16_t pc) -> LabelResult
{
    LabelLine label_line{};
    label_line.label = context->label()->SYMBOL()->getText();
    label_line.pc = pc;
    if (context->comment())
    {
        label_line.comment = context->comment()->COMMENT()->getText();
    }
    return LabelResult::ok(label_line);
}

auto LabelLine::format() const -> std::string
{
    const auto comment_str = comment == std::nullopt ?
        "" : std::format("\t;{}", comment.value());
    return std::format("{}:{}", label, comment_str);
}

auto AssignLine::make(asm6502Parser::LineContext* context, uint16_t pc) -> AssignResult
{
    auto expr_result = ArithmeticExpression::make(context->assign()->expression());
    if (expr_result.is_err())
    {
        return AssignResult::err(ParseError::BadAssign);
    }
    AssignLine assign_line{};
    assign_line.expression = expr_result.get_ok();
    assign_line.name = context->assign()->SYMBOL()->getText();
    if (context->comment())
    {
        assign_line.comment = context->comment()->COMMENT()->getText();
    }
    assign_line.pc = pc;

    return AssignResult::ok(assign_line);
}

auto AssignLine::evaluate(SymbolMap& symbol_map) -> std::optional<AsmError>
{
    if (symbol_map.contains(name))
    {
        return AsmError::SymbolRedefined;
    }
    else
    {
        auto result = expression.evaluate(symbol_map, pc);
        if (result.is_err())
        {
            return result.get_err();
        }
        value = result.get_ok();
        symbol_map[name] = *reinterpret_cast<uint16_t*>(&value.value());
    }
    return {};
}

auto AsmLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> ParseResult
{
    auto* label_rule = line->label();
    auto* comment_rule = line->comment();
    auto* instruction_rule = line->instruction();
    auto* assign_rule = line->assign();

    if (instruction_rule != nullptr)
    {
        if (assign_rule != nullptr)
        {
            return ParseResult::err(ParseError::LogicError);
        }
        auto instruction_result = AsmInstructionLine::make(line, pc);
        if (instruction_result.is_err())
        {
            return ParseResult::err(instruction_result.get_err());
        }
        AsmLine asm_line{};
        asm_line.line = instruction_result.get_ok();
        return ParseResult::ok(asm_line);
    }

    if (assign_rule != nullptr)
    {
        if (label_rule != nullptr)
        {
            return ParseResult::err(ParseError::LogicError);
        }

        auto assign_result = AssignLine::make(line, pc);
        if (assign_result.is_err())
        {
            return ParseResult::err(assign_result.get_err());
        }
        AsmLine asm_line{};
        asm_line.line = assign_result.get_ok();
        return ParseResult::ok(asm_line);
    }

    if (label_rule != nullptr)
    {
        auto label_result = LabelLine::make(line, pc);
        if (label_result.is_err())
        {
            return ParseResult::err(label_result.get_err());
        }
        AsmLine asm_line{};
        asm_line.line = label_result.get_ok();
        return ParseResult::ok(asm_line);
    }

    if (comment_rule != nullptr)
    {
        CommentLine comment_line{comment_rule->COMMENT()->getText(), pc};
        AsmLine asm_line{};
        asm_line.line = comment_line;
        return ParseResult::ok(asm_line);
    }

    AsmLine asm_line{};
    asm_line.line = EmptyLine{pc};
    return ParseResult::ok(asm_line);
}

auto AsmLine::has_label() const -> bool {
    return std::visit([&](const auto& v){return v.has_label();}, line);
}

auto AsmLine::get_label() const -> const std::string&
{
    if (std::holds_alternative<AsmInstructionLine>(line))
    {
        return std::get<AsmInstructionLine>(line).get_label();
    }
    else if (std::holds_alternative<LabelLine>(line))
    {
        return std::get<LabelLine>(line).get_label();
    }
    else
    {
        throw std::logic_error(
            std::format("Line (index {}) can not have a label", line.index()));
    }
}

auto AsmLine::size() const -> uint16_t
{
    return std::visit([&](const auto& v){return v.size();}, line);
}

auto AsmLine::evaluate(SymbolMap &symbol_map) -> std::optional<AsmError>
{
    return std::visit([&](auto& v){return v.evaluate(symbol_map);}, line);
}

auto AsmLine::format() const -> std::string {
    return std::visit([&](const auto& v){return v.format();}, line);
}

} // namespace mos6502
