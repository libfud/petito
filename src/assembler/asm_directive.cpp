#include "asm_directive.hpp"

#include <ranges>

namespace mos6502 {

auto OrgLine::make(OrgContext* line, uint16_t pc, const SymbolMap& symbol_map) -> OrgResult
{
    OrgLine directive{};
    auto expr_result = ArithmeticExpression::make(line->expression());
    if (expr_result.is_err())
    {
        return OrgResult::err(expr_result.get_err());
    }
    auto expression = expr_result.get_ok();
    auto eval_result = expression.evaluate(symbol_map, pc);
    if (eval_result.is_err())
    {
        return OrgResult::err(expr_result.get_err());
    }
    auto value = eval_result.get_ok();
    if (value > 0xFFFF || value < 0)
    {
        return OrgResult::err(ParseError::InvalidRange);
    }
    directive.pc = static_cast<uint16_t>(value);
    return OrgResult::ok(directive);
}

auto ByteDirectiveLine::make(
    asm6502Parser::Byte_directiveContext* line,
    uint16_t pc) -> ByteDirResult
{
    ByteDirectiveLine directive{};
    const auto& byte_expressions = line->byte_directive_value();
    directive.bytes.reserve(byte_expressions.size());
    directive.expressions.reserve(byte_expressions.size());
    for (const auto& byte_expression : byte_expressions)
    {
        auto expression_result = ArithmeticExpression::make(byte_expression->expression());
        if (expression_result.is_err())
        {
            return ByteDirResult::err(expression_result.get_err());
        }
        directive.expressions.push_back(expression_result.get_ok());
    }

    directive.pc = pc;
    return ByteDirResult::ok(directive);
}

auto ByteDirectiveLine::format() const -> std::string
{
    if (bytes.size() == 0)
    {
        throw std::logic_error{"Byte Directive can't be constructed without bytes"};
    }
    std::string output = std::format(".BYTE ${:02X}", bytes[0]);
    if (bytes.size() == 1)
    {
        return output;
    }

    for (auto elt : bytes | std::views::drop(1))
    {
        output += std::format(", ${:02X}", elt);
    }
    return output;
}

auto ByteDirectiveLine::evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
{
    for (auto& expression : expressions)
    {
        auto value_result = expression.evaluate(symbol_map, pc);
        if (value_result.is_err())
        {
            return value_result.get_err();
        }
        auto value = value_result.get_ok();
        if (value > 0xFF || value < 0)
        {
            return ParseError::InvalidRange;
        }
        bytes.push_back(static_cast<uint8_t>(value));
    }
    return {};
}

auto DByteDirectiveLine::make(
    asm6502Parser::Dbyte_directiveContext* line,
    uint16_t pc) -> DByteDirResult
{
    DByteDirectiveLine directive{};
    const auto& dbyte_expressions = line->byte_directive_value();
    directive.dbytes.reserve(dbyte_expressions.size());
    directive.expressions.reserve(dbyte_expressions.size());
    for (const auto& byte_expression : dbyte_expressions)
    {
        auto expression_result = ArithmeticExpression::make(byte_expression->expression());
        if (expression_result.is_err())
        {
            return DByteDirResult::err(expression_result.get_err());
        }
        directive.expressions.push_back(expression_result.get_ok());
    }

    directive.pc = pc;
    return DByteDirResult::ok(directive);
}

auto DByteDirectiveLine::format() const -> std::string
{
    if (dbytes.size() == 0)
    {
        throw std::logic_error{"DByte Directive can't be constructed with no bytes"};
    }

    std::string output = std::format(".DBYTE ${:02X}{:02X}", dbytes[0].high, dbytes[0].low);
    if (dbytes.size() == 1)
    {
        return output;
    }
    output.reserve(size() * 4);

    for (auto elt : dbytes | std::views::drop(1))
    {
        output += std::format(", ${:02X}{:02X}", elt.high, elt.low);
    }
    return output;
}

auto DByteDirectiveLine::serialize() const -> std::vector<uint8_t>
{
    std::vector<uint8_t> bytes{};
    bytes.reserve(size() * 2);
    for (auto elt : dbytes)
    {
        bytes.push_back(elt.high);
        bytes.push_back(elt.low);
    }
    return bytes;
}

auto DByteDirectiveLine::evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
{
    for (auto& expression : expressions)
    {
        auto value_result = expression.evaluate(symbol_map, pc);
        if (value_result.is_err())
        {
            return value_result.get_err();
        }
        auto value = value_result.get_ok();
        if (value > 0xFFFF | value < 0)
        {
            return ParseError::InvalidRange;
        }
        auto low = static_cast<uint8_t>(value & 0xFF);
        auto high = static_cast<uint8_t>((value >> 8) & 0xFF);
        dbytes.push_back(DByte{low, high});
    }
    return {};
}

auto WordDirectiveLine::make(
    asm6502Parser::Word_directiveContext* line,
    uint16_t pc) -> WordDirResult
{
    WordDirectiveLine directive{};
    const auto& word_expressions = line->byte_directive_value();
    directive.words.reserve(word_expressions.size());
    directive.expressions.reserve(word_expressions.size());
    for (const auto& byte_expression : word_expressions)
    {
        auto expression_result = ArithmeticExpression::make(byte_expression->expression());
        if (expression_result.is_err())
        {
            return WordDirResult::err(expression_result.get_err());
        }
        directive.expressions.push_back(expression_result.get_ok());
    }

    directive.pc = pc;
    return WordDirResult::ok(directive);
}

auto WordDirectiveLine::format() const -> std::string
{
    if (words.size() == 0)
    {
        throw std::logic_error{"Word Directive can't be constructed with no bytes"};
    }

    std::string output = std::format(".WORD ${:02X}{:02X}", words[0].high, words[0].low);
    if (words.size() == 1)
    {
        return output;
    }
    output.reserve(size() * 4);

    for (auto elt : words | std::views::drop(1))
    {
        output += std::format(", ${:02X}{:02X}", elt.high, elt.low);
    }
    return output;
}

auto WordDirectiveLine::serialize() const -> std::vector<uint8_t>
{
    std::vector<uint8_t> bytes{};
    bytes.reserve(size() * 2);
    for (auto elt : words)
    {
        bytes.push_back(elt.low);
        bytes.push_back(elt.high);
    }
    return bytes;
}

auto WordDirectiveLine::evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
{
    for (auto& expression : expressions)
    {
        auto value_result = expression.evaluate(symbol_map, pc);
        if (value_result.is_err())
        {
            return value_result.get_err();
        }
        auto value = value_result.get_ok();
        if (value > 0xFFFF | value < 0)
        {
            return ParseError::InvalidRange;
        }
        auto low = static_cast<uint8_t>(value & 0xFF);
        auto high = static_cast<uint8_t>((value >> 8) & 0xFF);
        words.push_back(Word{low, high});
    }
    return {};
}

auto TextDirectiveLine::make(
    asm6502Parser::Text_directiveContext* line, uint16_t pc) -> TextDirResult
{
    TextDirectiveLine directive{};
    directive.pc = pc;
    const auto& text_contents = line->string()->stringContents();
    directive.text = "";
    for (const auto& content : text_contents)
    {
        if (content->TEXT())
        {
            directive.text += content->TEXT()->getText();
        }
        else
        {
            directive.escape_count++;
            std::string escape_sequence{content->ESCAPE_SEQUENCE()->getText()};
            char escape_char = escape_sequence[1];
            switch (escape_char)
            {
            case '"':
                directive.text += '"';
                break;
            case 't':
                directive.text += '\t';
                break;
            case 'n':
                directive.text += '\n';
                break;
            case 'r':
                directive.text += '\r';
                break;
            default:
                return TextDirResult::err(ParseError::BadEscape);
            }
        }
    }

    return TextDirResult::ok(directive);
}

auto TextDirectiveLine::format() const -> std::string
{
    std::string output{};
    output.reserve(text.size() + escape_count);
    for (const char letter : text) {
        switch (letter)
        {
            case '"':
                output += "\"";
                break;
            case '\t':
                output += "\\t";
                break;
            case '\n':
                output += "\\n";
                break;
            case '\r':
                output += "\\r";
                break;
            default:
                output += letter;
                break;
        }
    }
    return std::format(".TEXT \"{}\"", output);
}

auto TextDirectiveLine::serialize() const -> std::vector<uint8_t>
{
    return std::vector<uint8_t>{text.begin(), text.end()};
}

auto AlignDirectiveLine::make(
    asm6502Parser::Align_directiveContext* line,
    uint16_t pc) -> AlignDirResult
{
    AlignDirectiveLine directive{};
    directive.pc = pc;

    const auto& expressions = line->expression();

    if (expressions.size() == 0)
    {
        return AlignDirResult::ok(directive);
    }

    if (expressions.size() > 2)
    {
        return AlignDirResult::err(ParseError::LogicError);
    }

    auto alignment_expr_result = ArithmeticExpression::make(expressions[0]);
    if (alignment_expr_result.is_err())
    {
        return AlignDirResult::err(alignment_expr_result.get_err());
    }
    directive.alignment_expression = alignment_expr_result.get_ok();
    if (expressions.size() == 1)
    {
        return AlignDirResult::ok(directive);
    }

    auto fill_expr_result = ArithmeticExpression::make(expressions[1]);
    if (fill_expr_result.is_err())
    {
        return AlignDirResult::err(fill_expr_result.get_err());
    }
    directive.fill_expression = fill_expr_result.get_ok();

    return AlignDirResult::ok(directive);
}

auto AlignDirectiveLine::format() const -> std::string
{
    return std::format(".ALIGN ${:04X} ${:02X}", alignment, fill);
}

auto AlignDirectiveLine::evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
{
    if (alignment_expression != std::nullopt)
    {
        auto alignment_eval = alignment_expression.value().evaluate(symbol_map, pc);
        if (alignment_eval.is_err())
        {
            return alignment_eval.get_err();
        }
        auto alignment_value = alignment_eval.get_ok();
        if (alignment_value > 0xFFFF | alignment_value < 0)
        {
            return ParseError::InvalidRange;
        }
        alignment = alignment_value & 0xFFFF;
    }

    if (fill_expression != std::nullopt)
    {
        auto fill_eval = fill_expression.value().evaluate(symbol_map, pc);
        if (fill_eval.is_err())
        {
            return fill_eval.get_err();
        }
        auto fill_value = fill_eval.get_ok();
        if (fill_value > 0xFF || fill_value < 0)
        {
            return ParseError::InvalidRange;
        }
        fill = fill_value & 0xFF;
    }

    return {};
}

auto FillDirectiveLine::make(
    asm6502Parser::Fill_directiveContext* line, uint16_t pc) -> FillDirResult
{
    return FillDirResult::err(ParseError::LogicError);
}

auto FillDirectiveLine::format() const -> std::string
{
    return std::format(".FILL ${:04X} ${:02X}", count, fill);
}

auto FillDirectiveLine::evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
{
    return ParseError::LogicError;
}

auto DirectiveLine::make(
    LineContext* line,
    uint16_t pc,
    const SymbolMap& symbol_map) -> DirectiveResult
{
    DirectiveLine directive_line{};
    auto directive = line->directive();
    if (line->comment())
    {
        directive_line.comment = line->comment()->COMMENT()->getText();
    }

    if (directive->org())
    {
        auto result = OrgLine::make(directive->org(), pc, symbol_map);
        if (result.is_err())
        {
            return DirectiveResult::err(result.get_err());
        }
        directive_line.directive = result.get_ok();
        return DirectiveResult::ok(directive_line);
    }

    auto handle_rule = [&](auto* rule, auto maker){
        auto result = maker(rule, pc);
        if (result.is_err())
        {
            return DirectiveResult::err(result.get_err());
        }
        directive_line.directive = result.get_ok();
        return DirectiveResult::ok(directive_line);
    };

    if (directive->byte_directive())
    {
        return handle_rule(directive->byte_directive(), ByteDirectiveLine::make);
    }
    if (directive->dbyte_directive())
    {
        return handle_rule(directive->dbyte_directive(), DByteDirectiveLine::make);
    }
    if (directive->word_directive())
    {
        return handle_rule(directive->word_directive(), WordDirectiveLine::make);
    }
    if (directive->text_directive())
    {
        return handle_rule(directive->text_directive(), TextDirectiveLine::make);
    }
    if (directive->align_directive())
    {
        return handle_rule(directive->align_directive(), AlignDirectiveLine::make);
    }
    if (directive->fill_directive())
    {
        return handle_rule(directive->fill_directive(), FillDirectiveLine::make);
    }

    return DirectiveResult::err(ParseError::LogicError);
}

auto DirectiveLine::format() const -> std::string
{
    std::string comment_str{""};
    if (comment != std::nullopt)
    {
        comment_str = "\t" + comment.value();
    }
    return std::format(
        "{}{}",
        std::visit([](const auto& v){return v.format();}, directive),
        comment_str
    );
}

auto DirectiveLine::serialize() const -> std::vector<uint8_t>
{
    return std::visit([](const auto& v){return v.serialize();}, directive);
}

auto DirectiveLine::program_counter() const -> uint16_t
{
    return std::visit([](const auto& v){return v.program_counter();}, directive);
}

auto DirectiveLine::size() const -> uint16_t
{
    return std::visit([](const auto& v){return v.size();}, directive);
}

auto DirectiveLine::evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
{
    return std::visit([&](auto& v){return v.evaluate(symbol_map);}, directive);
}

} // namespace mos6502
