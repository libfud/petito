#include "asm_line.hpp"

namespace mos6502 {

auto LabelLine::make(LineContext* context, uint16_t pc, SymbolMap& symbol_map) -> LabelResult
{
    LabelLine label_line{};
    auto label = context->label()->SYMBOL()->getText();
    if (symbol_map.contains(label))
    {
        return LabelResult::err(ParseError::SymbolRedefined);
    }
    symbol_map[label] = pc;
    label_line.label = label;
    label_line.pc = pc;
    if (context->comment())
    {
        label_line.comment = context->comment()->COMMENT()->getText();
    }
    return LabelResult::ok(label_line);
}

auto LabelLine::format() const -> std::string
{
    std::string comment_str{""};
    if (comment != std::nullopt)
    {
        comment_str = std::format("\t{}", comment.value());
    }
    return std::format("{}:{}", label, comment_str);
}

auto AssignLine::make(LineContext* context, uint16_t pc, SymbolMap& symbol_map) -> AssignResult
{
    auto expr_result = ArithmeticExpression::make(context->assign()->expression());
    if (expr_result.is_err())
    {
        return AssignResult::err(expr_result.get_err());
    }
    AssignLine assign_line{};
    assign_line.expression = expr_result.get_ok();
    assign_line.name = context->assign()->SYMBOL()->getText();

    if (assign_line.name == "R%")
    {
        return AssignResult::err(ParseError::IllegalRepeatVar);
    }

    if (context->comment())
    {
        assign_line.comment = context->comment()->COMMENT()->getText();
    }
    assign_line.pc = pc;
    auto eval_res = assign_line.evaluate(symbol_map);
    if (eval_res)
    {
        return AssignResult::err(eval_res.value());
    }

    return AssignResult::ok(assign_line);
}

auto AssignLine::evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
{
    if (value != std::nullopt)
    {
        return {};
    }

    if (symbol_map.contains(name))
    {
        return ParseError::SymbolRedefined;
    }
    else
    {
        auto result = expression.evaluate(symbol_map, pc);
        if (result.is_err())
        {
            return result.get_err();
        }
        value = result.get_ok();
        symbol_map[name] = value.value();
    }
    return {};
}

auto RepeatDirective::make(
    RepeatContext* line,
    uint16_t pc,
    SymbolMap& symbol_map) -> RepeatResult
{
    RepeatDirective repeat_directive{};

    ArithmeticAtom value{'\0'};
    auto result = Result<ArithmeticAtom, ParseError>::err(ParseError::LogicError);
    if (line->byte() != nullptr)
    {
        result = make_byte(line->byte());
    }
    else if (line->multibyte() != nullptr)
    {
        result = make_word(line->multibyte());
    }

    if (result.is_err())
    {
        return RepeatResult::err(result.get_err());
    }
    value = result.get_ok();
    switch (value.get_type())
    {
    case ArithAtomType::Byte:
        repeat_directive.count = value.get<uint8_t>();
        break;
    case ArithAtomType::Word:
        repeat_directive.count = value.get<uint16_t>();
        break;
    default:
        return RepeatResult::err(ParseError::LogicError);
    }

    if (repeat_directive.count == 0)
    {
        return RepeatResult::err(ParseError::BadCount);
    }

    if (!(line->instruction() == nullptr ^ line->directive() == nullptr))
    {
        return RepeatResult::err(ParseError::LogicError);
    }

    uint16_t iter_pc = pc;
    uint16_t total_size = 0;
    if (line->instruction() != nullptr)
    {
        for (auto idx = 0; idx < repeat_directive.count; ++idx)
        {
            auto* context = line->instruction();
            symbol_map[repeat_var] = idx;
            auto instruction_result = AsmInstructionLine::make_plain(
                context,
                iter_pc,
                symbol_map);
            if (instruction_result.is_err())
            {
                return RepeatResult::err(instruction_result.get_err());
            }
            auto instruction = instruction_result.get_ok();
            if ((iter_pc + instruction.size()) > 0xFFFF)
            {
                return RepeatResult::err(ParseError::LogicError);
            }
            iter_pc += instruction.size();
            total_size += instruction.size();
            repeat_directive.instructions.push_back(instruction);
        }
    }

    if (line->directive() != nullptr)
    {
        for (auto idx = 0; idx < repeat_directive.count; ++idx)
        {
            auto* context = line->directive();
            symbol_map[repeat_var] = idx;
            auto directive_result = DirectiveLine::make_plain(
                context,
                iter_pc,
                symbol_map);
            if (directive_result.is_err())
            {
                return RepeatResult::err(directive_result.get_err());
            }
            auto directive = directive_result.get_ok();
            if ((iter_pc + directive.size()) > 0xFFFF)
            {
                return RepeatResult::err(ParseError::LogicError);
            }
            iter_pc = directive.program_counter() + directive.size();
            total_size += directive.size();
            repeat_directive.directives.push_back(directive);
        }
    }

    symbol_map.erase(repeat_var);
    repeat_directive.total_size = total_size;

    return RepeatResult::ok(repeat_directive);
}

auto RepeatDirective::format() const -> std::string
{
    std::string output{std::format(".REPEAT ${:04X}", count)};

    for (const auto& instruction : instructions)
    {
        output += std::format("\n{}", instruction.format());
    }

    for (const auto& directive : directives)
    {
        output += std::format("\n{}", directive.format());
    }

    return output;
}

auto RepeatDirective::program_counter() const -> uint16_t
{
    if (instructions.size() > 0)
    {
        return instructions[0].program_counter();
    }
    else
    {
        return directives[0].program_counter();
    }
}

auto RepeatDirective::size() const -> uint16_t
{
    return total_size;
}

auto RepeatDirective::evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
{
    uint16_t repetition = 0;

    for (auto& instruction : instructions)
    {
        symbol_map[repeat_var] = repetition;
        auto result = instruction.evaluate(symbol_map);
        if (result != std::nullopt)
        {
            return result;
        }
        repetition++;
    }

    repetition = 0;
    for (auto& directive : directives)
    {
        symbol_map[repeat_var] = repetition;
        auto result = directive.evaluate(symbol_map);
        if (result != std::nullopt)
        {
            return result;
        }
        repetition++;
    }

    symbol_map.erase(repeat_var);

    return {};
}

auto RepeatDirective::serialize() const -> std::vector<uint8_t>
{
    std::vector<uint8_t> output;
    for (const auto& instruction : instructions)
    {
        std::visit(
            [&](const auto& v){ output.insert(output.end(), v.begin(), v.end()); },
            instruction.serialize());
    }
    for (const auto& directive : directives)
    {
        auto bytes = directive.serialize();
        output.insert(output.end(), bytes.begin(), bytes.end());
    }
    return output;
}

auto AsmLine::make(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> ParseResult
{
    auto* comment_rule = line->comment();
    auto* assign_rule = line->assign();

    if (line->instruction() != nullptr) { return make_instruction(line, pc, symbol_map); }

    if (assign_rule != nullptr) { return make_assign(line, pc, symbol_map); }

    if (line->label() != nullptr) { return make_label(line, pc, symbol_map); }

    if (line->directive() != nullptr) { return make_directive(line, pc, symbol_map); }

    if (line->repeat_directive() != nullptr) { return make_repeat(line, pc, symbol_map); }

    if (comment_rule != nullptr) { return make_comment(line, pc, symbol_map); }

    AsmLine asm_line{};
    asm_line.line = EmptyLine{pc};
    return ParseResult::ok(asm_line);
}

auto AsmLine::make_instruction(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> ParseResult
{
    if (line->assign() != nullptr)
    {
        return ParseResult::err(ParseError::LogicError);
    }
    auto instruction_result = AsmInstructionLine::make(line, pc, symbol_map);
    if (instruction_result.is_err())
    {
        return ParseResult::err(instruction_result.get_err());
    }
    AsmLine asm_line{};
    asm_line.line = instruction_result.get_ok();
    return ParseResult::ok(asm_line);
}

auto AsmLine::make_assign(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> ParseResult
{
    if (line->label() != nullptr)
    {
        return ParseResult::err(ParseError::LogicError);
    }

    auto assign_result = AssignLine::make(line, pc, symbol_map);
    if (assign_result.is_err())
    {
        return ParseResult::err(assign_result.get_err());
    }
    AsmLine asm_line{};
    asm_line.line = assign_result.get_ok();
    return ParseResult::ok(asm_line);
}

auto AsmLine::make_label(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> ParseResult
{
    auto label_result = LabelLine::make(line, pc, symbol_map);
    if (label_result.is_err())
    {
        return ParseResult::err(label_result.get_err());
    }
    AsmLine asm_line{};
    asm_line.line = label_result.get_ok();
    return ParseResult::ok(asm_line);
}

auto AsmLine::make_directive(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> ParseResult
{
    auto directive_result = DirectiveLine::make(line, pc, symbol_map);
    if (directive_result.is_err())
    {
        return ParseResult::err(directive_result.get_err());
    }
    AsmLine asm_line{};
    asm_line.line = directive_result.get_ok();
    return ParseResult::ok(asm_line);
}

auto AsmLine::make_repeat(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> ParseResult
{
    auto repeat_result = RepeatDirective::make(line->repeat_directive(), pc, symbol_map);
    if (repeat_result.is_err())
    {
        return ParseResult::err(repeat_result.get_err());
    }
    AsmLine asm_line{};
    asm_line.line = repeat_result.get_ok();
    return ParseResult::ok(asm_line);
}

auto AsmLine::make_comment(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> ParseResult
{
    CommentLine comment_line{line->comment()->COMMENT()->getText(), pc};
    AsmLine asm_line{};
    asm_line.line = comment_line;
    return ParseResult::ok(asm_line);
}

auto AsmLine::program_counter() const -> uint16_t
{
    return std::visit([](const auto& v){return v.program_counter();}, line);
}

auto AsmLine::size() const -> uint16_t
{
    return std::visit([](const auto& v){return v.size();}, line);
}

auto AsmLine::evaluate(SymbolMap &symbol_map) -> std::optional<ParseError>
{
    return std::visit([&](auto& v){return v.evaluate(symbol_map);}, line);
}

auto AsmLine::format() const -> std::string {
    return std::visit([](const auto& v){return v.format();}, line);
}

auto AsmLine::serialize() const -> AsmLineBytes {
    return std::visit(
        [](const auto& v) {return AsmLineBytes{v.serialize()};},
        line);
}

} // namespace mos6502
