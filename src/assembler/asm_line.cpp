#include "asm_line.hpp"

namespace mos6502 {

auto LabelLine::make(LineContext* context, uint16_t pc, SymbolMap& symbol_map) -> LabelResult
{
    LabelLine label_line{};
    auto label = context->label()->SYMBOL()->getText();
    std::cout << "LABEL is " << label << "\n";
    if (symbol_map.contains(label))
    {
        std::cerr << "Redefined " << label << "\n";
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
    const auto comment_str = comment == std::nullopt ?
        "" : std::format("\t;{}", comment.value());
    return std::format("{}:{}", label, comment_str);
}

auto AssignLine::make(LineContext* context, uint16_t pc, SymbolMap& symbol_map) -> AssignResult
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
        std::cerr << "Redefined " << name << "\n";
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

auto AsmLine::make(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> ParseResult
{
    auto* label_rule = line->label();
    auto* comment_rule = line->comment();
    auto* assign_rule = line->assign();

    if (line->instruction() != nullptr)
    {
        if (assign_rule != nullptr)
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

    if (assign_rule != nullptr)
    {
        if (label_rule != nullptr)
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

    if (label_rule != nullptr)
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

    if (line->directive() != nullptr)
    {
        auto directive_result = DirectiveLine::make(line, pc);
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
    return std::visit([](const auto& v){return v.has_label();}, line);
}

auto AsmLine::get_label() const -> std::string
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
