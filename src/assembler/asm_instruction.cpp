#include "asm_instruction.hpp"
#include "logger/logger.hpp"

namespace mos6502 {

constexpr InstructionLine::InstructionLine(uint16_t pc, OpName op_id)
    :
    pc{pc},
    op_id{op_id}
{}

constexpr auto InstructionLine::format() const -> std::string
{
    return format_instruction();
}

auto InstructionLine::evaluate(const SymbolMap&) -> std::optional<ParseError>
{
    return {};
}

NOperandInstructionLine::NOperandInstructionLine(
    uint16_t pc,
    OpName op_id,
    ArithmeticExpression&& expression)
    : InstructionLine{pc, op_id}, expression{std::move(expression)}
{
}

auto OneOperandInstructionLine::evaluate(const SymbolMap& symbol_map) -> std::optional<ParseError>
{
    auto result = expression.evaluate_byte(symbol_map, pc);
    if (result.is_err())
    {
        return result.get_err();
    }

    operand = result.get_ok();
    return {};
}

auto TwoOperandInstructionLine::evaluate(const SymbolMap& symbol_map) -> std::optional<ParseError>
{
    auto result = expression.evaluate_word(symbol_map, pc);
    if (result.is_err())
    {
        return result.get_err();
    }

    auto value = result.get_ok();
    operand_1 = value & 0xFF;
    operand_2 = (value >> 8) & 0xFF;
    return {};
}

auto RelativeInstructionLine::evaluate(const SymbolMap& symbol_map) -> std::optional<ParseError>
{
    auto result = expression.evaluate_word(symbol_map, pc);
    if (result.is_err())
    {
        return result.get_err();
    }

    auto value = result.get_ok();

    // Target address is an absolute address, e.g. a label or a label
    // and an offset evaluated to an address.
    target_address = value;
    int32_t offset = target_address - (pc + size());
    // Branch range has to fit in signed 8 bit integer.
    if (offset < -128 || offset > 127)
    {
        return ParseError::InvalidRange;
    }
    operand = static_cast<uint8_t>(offset);

    return {};
}

auto AsmInstructionLine::make(
    asm6502Parser::LineContext* line,
    uint16_t pc,
    SymbolMap& symbol_map) -> ParseResult
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

    AsmInstructionLine instruction{};
    auto parse_result = instruction.parse(instruction_rule, pc, symbol_map);
    if (parse_result != std::nullopt)
    {
        return ParseResult::err(parse_result.value());
    }
    if (line->label())
    {
        auto label = line->label()->SYMBOL()->getText();
        if (symbol_map.contains(label))
        {
            return ParseResult::err(ParseError::SymbolRedefined);
        }
        symbol_map[label] = pc;
        instruction.label = label;
    }
    if (line->comment())
    {
        instruction.comment = line->comment()->COMMENT()->getText();
    }

    return ParseResult::ok(instruction);
}

auto AsmInstructionLine::make_plain(
    asm6502Parser::InstructionContext* instruction_context,
    uint16_t pc,
    SymbolMap& symbol_map) -> ParseResult
{
    AsmInstructionLine instruction{};
    auto parse_result = instruction.parse(instruction_context, pc, symbol_map);
    if (parse_result != std::nullopt)
    {
        return ParseResult::err(parse_result.value());
    }

    return ParseResult::ok(instruction);
}

auto AsmInstructionLine::parse(
    InstructionContext* rule,
    uint16_t pc,
    SymbolMap& symbol_map) -> BuilderResult
{
    if (rule->nop())
    {
        instruction = ImplicitInstructionLine{pc, OpName::NOP};
        return {};
    }

    if (rule->implicit()) { return parse_implicit(rule, pc); }

    if (rule->acc()) { return parse_acc(rule, pc); }

    if (rule->immediate()) { return parse_immediate(rule, pc); }

    if (rule->zero_page()) { return parse_zero_page(rule, pc); }

    if (rule->x_index()) { return parse_x_index(rule, pc, symbol_map); }

    if (rule->y_index()) { return parse_y_index(rule, pc, symbol_map); }

    if (rule->x_indirect()) { return parse_x_indirect(rule, pc); }

    if (rule->indirect_y()) { return parse_indirect_y(rule, pc); }

    if (rule->absolute()) { return parse_absolute(rule, pc); }

    if (rule->relative()) { return parse_relative(rule, pc); }

    if (rule->jump()) { return parse_jump(rule, pc); }

    if (rule->jsr()) { return parse_jsr(rule, pc); }

    return ParseError::LogicError;
}

auto AsmInstructionLine::parse_implicit(InstructionContext* rule, uint16_t pc) -> BuilderResult
{
    auto* implicit_rule = rule->implicit();
    std::string implicit_name{implicit_rule->getText()};
    auto invalid_mnemonic = check_mnemonic(implicit_name, AddressMode::IMPL);
    if (invalid_mnemonic.is_err())
    {
        return invalid_mnemonic.get_err();
    }
    auto op_id = invalid_mnemonic.get_ok();

    instruction = ImplicitInstructionLine{pc, op_id};
    return {};
}

auto AsmInstructionLine::parse_acc(InstructionContext* rule, uint16_t pc) -> BuilderResult
{
    auto* acc_rule = rule->acc();
    std::string acc_name{acc_rule->shift()->SHIFT()->getText()};
    auto invalid_mnemonic = check_mnemonic(acc_name, AddressMode::A);
    if (invalid_mnemonic.is_err())
    {
        return invalid_mnemonic.get_err();
    }
    auto op_id = invalid_mnemonic.get_ok();
    instruction = AccInstructionLine{pc, op_id};
    return {};
}

auto AsmInstructionLine::parse_immediate(InstructionContext* rule, uint16_t pc) -> BuilderResult
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
    instruction = ImmediateInstructionLine{pc, op_id, arith_result.get_ok()};

    return {};
}

auto AsmInstructionLine::parse_zero_page(InstructionContext* rule, uint16_t pc) -> BuilderResult
{
    auto* context = rule->zero_page();

    if (!context->byte())
    {
        return parse_helper(
            instruction_line_wrapper<ZeroPageInstructionLine>,
            context,
            AddressMode::ZPG,
            pc);
    }

    auto byte_result = make_byte(context->byte());
    if (byte_result.is_err())
    {
        return byte_result.get_err();
    }
    auto byte = byte_result.get_ok();
    std::string name{};
    if (context->mnemonic())
    {
        name = context->mnemonic()->MNEMONIC()->getText();
    }
    else
    {
        name = context->shift()->SHIFT()->getText();
    }
    auto invalid_mnemonic = check_mnemonic(name, AddressMode::ZPG);
    if (invalid_mnemonic.is_err())
    {
        return invalid_mnemonic.get_err();
    }
    auto op_id = invalid_mnemonic.get_ok();
    ArithmeticExpression expression{};
    expression.add_atom(std::move(byte));
    instruction = ZeroPageInstructionLine(pc, op_id, std::move(expression));
    return {};
}

auto AsmInstructionLine::parse_x_index(
    InstructionContext* rule,
    uint16_t pc,
    SymbolMap& symbol_map) -> BuilderResult
{
    return parse_indexed(
        rule->x_index(),
        pc,
        symbol_map,
        AddressMode::ZPG_X,
        AddressMode::ABS_X,
        instruction_line_wrapper<ZeroPageXInstructionLine>,
        instruction_line_wrapper<AbsoluteXInstructionLine>);
}

auto AsmInstructionLine::parse_y_index(
    InstructionContext* rule,
    uint16_t pc,
    SymbolMap& symbol_map) -> BuilderResult
{
    return parse_indexed(
        rule->y_index(),
        pc,
        symbol_map,
        AddressMode::ZPG_Y,
        AddressMode::ABS_Y,
        instruction_line_wrapper<ZeroPageYInstructionLine>,
        instruction_line_wrapper<AbsoluteYInstructionLine>);
}

auto AsmInstructionLine::parse_x_indirect(InstructionContext* rule, uint16_t pc) -> BuilderResult
{
    auto* context = rule->x_indirect();
    return parse_helper(
        instruction_line_wrapper<XIndirectInstructionLine>,
        context,
        AddressMode::X_IND,
        pc);
}

auto AsmInstructionLine::parse_indirect_y(InstructionContext* rule, uint16_t pc) -> BuilderResult
{
    auto* context = rule->indirect_y();
    return parse_helper(
        instruction_line_wrapper<IndirectYInstructionLine>,
        context,
        AddressMode::IND_Y,
        pc);
    return {};
}

auto AsmInstructionLine::parse_absolute(InstructionContext* rule, uint16_t pc) -> BuilderResult
{
    auto* context = rule->absolute();
    return parse_helper(
        instruction_line_wrapper<AbsoluteInstructionLine>,
        context,
        AddressMode::ABS,
        pc);
}

auto AsmInstructionLine::parse_relative(InstructionContext* rule, uint16_t pc) -> BuilderResult
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
    instruction = RelativeInstructionLine{pc, op_id, std::move(expression)};
    return {};
}

auto AsmInstructionLine::parse_jump(InstructionContext* rule, uint16_t pc) -> BuilderResult
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
        instruction = IndirectInstructionLine{pc, op_id, std::move(expression)};
    }
    else
    {
        instruction = AbsoluteInstructionLine{pc, op_id, std::move(expression)};
    }

    return {};
}

auto AsmInstructionLine::parse_jsr(InstructionContext* rule, uint16_t pc) -> BuilderResult
{
    auto* context = rule->jsr();
    auto op_id = OpName::JSR;
    auto arith_result = ArithmeticExpression::make(context->expression());
    if (arith_result.is_err())
    {
        return arith_result.get_err();
    }
    auto expression = arith_result.get_ok();
    instruction = AbsoluteInstructionLine{pc, op_id, std::move(expression)};
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

auto AsmInstructionLine::evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
{
    return std::visit([&](auto& v){return v.evaluate(symbol_map);}, instruction);
}

auto AsmInstructionLine::format() const -> std::string {
    return std::format(
        "{}\t{}{}",
        label != std::nullopt ? std::format("{}:", label.value()) : "",
        std::visit([](const auto& v){return v.format();}, instruction),
        comment != std::nullopt ? std::format("\t;{}", comment.value()) : ""
    );
}

auto AsmInstructionLine::serialize() const -> AsmLineBytes {
    return std::visit(
        [](const auto& v){return AsmLineBytes{v.serialize()};},
        instruction);
}

auto AsmInstructionLine::program_counter() const -> uint16_t
{
    return std::visit([](const auto& v){return v.program_counter();}, instruction);
}

auto AsmInstructionLine::size() const -> uint16_t
{
    return std::visit([](const auto& v){return v.size();}, instruction);
}

} // namespace mos6502
