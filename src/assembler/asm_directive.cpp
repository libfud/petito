#include "asm_directive.hpp"

#include <ranges>

namespace mos6502 {

auto OrgLine::make(asm6502Parser::OrgContext* line, uint16_t pc) -> OrgResult
{
    return OrgResult::err(ParseError::LogicError);
}

auto ByteDirectiveLine::make(
    asm6502Parser::Byte_directiveContext* line, uint16_t pc) -> ByteDirResult
{
    return ByteDirResult::err(ParseError::LogicError);
}

auto ByteDirectiveLine::format() const -> std::string
{
    if (bytes.size() == 0)
    {
        throw std::logic_error{"Byte Directive can't be constructed with no bytes"};
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

auto DByteDirectiveLine::make(
    asm6502Parser::Dbyte_directiveContext* line, uint16_t pc) -> DByteDirResult
{
    return DByteDirResult::err(ParseError::LogicError);
}

auto DByteDirectiveLine::format() const -> std::string
{
    if (dbytes.size() == 0)
    {
        throw std::logic_error{"DByte Directive can't be constructed with no bytes"};
    }

    std::string output = std::format(".DBYTE ${:02X}{:02X}", dbytes[0].low, dbytes[0].high);
    if (dbytes.size() == 1)
    {
        return output;
    }
    output.reserve(size() * 4);

    for (auto elt : dbytes | std::views::drop(1))
    {
        output += std::format(", ${:02X}{:02X}", elt.low, elt.high);
    }
    return output;
}

auto DByteDirectiveLine::serialize() const -> std::vector<uint8_t>
{
    std::vector<uint8_t> bytes{};
    bytes.reserve(size() * 2);
    for (auto elt : dbytes)
    {
        bytes.push_back(elt.low);
        bytes.push_back(elt.high);
    }
    return bytes;
}

auto WordDirectiveLine::make(
    asm6502Parser::Word_directiveContext* line, uint16_t pc) -> WordDirResult
{
    return WordDirResult::err(ParseError::LogicError);
}

auto WordDirectiveLine::format() const -> std::string
{
    if (dbytes.size() == 0)
    {
        throw std::logic_error{"Word Directive can't be constructed with no bytes"};
    }

    std::string output = std::format(".WORD ${:02X}{:02X}", dbytes[0].low, dbytes[0].high);
    if (dbytes.size() == 1)
    {
        return output;
    }
    output.reserve(size() * 4);

    for (auto elt : dbytes | std::views::drop(1))
    {
        output += std::format(", ${:02X}{:02X}", elt.low, elt.high);
    }
    return output;
}

auto WordDirectiveLine::serialize() const -> std::vector<uint8_t>
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

auto TextDirectiveLine::make(
    asm6502Parser::Text_directiveContext* line, uint16_t pc) -> TextDirResult
{
    return TextDirResult::err(ParseError::LogicError);
}

auto TextDirectiveLine::serialize() const -> std::vector<uint8_t>
{
    return std::vector<uint8_t>{text.begin(), text.end()};
}

auto AlignDirectiveLine::make(
    asm6502Parser::Align_directiveContext* line, uint16_t pc) -> AlignDirResult
{
    return AlignDirResult::err(ParseError::LogicError);
}

auto AlignDirectiveLine::format() const -> std::string
{
    return std::format(".ALIGN ${:04X} ${:02X}", alignment, fill);
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

auto DirectiveLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> DirectiveResult
{
    DirectiveLine directive_line{};
    auto directive = line->directive();
    if (line->comment())
    {
        directive_line.comment = line->comment()->COMMENT()->getText();
    }
#define HANDLE_RULE(HYGIENE_RULE, HYGIENE_CLASS)                        \
    if (directive->HYGIENE_RULE())                                      \
    {                                                                   \
        auto result = HYGIENE_CLASS::make(directive->HYGIENE_RULE(), pc); \
        if (result.is_err())                                            \
        {                                                               \
            return DirectiveResult::err(result.get_err());              \
        }                                                               \
        directive_line.directive = result.get_ok();                     \
        return DirectiveResult::ok(directive_line);                     \
    }

    HANDLE_RULE(org, OrgLine);
    HANDLE_RULE(byte_directive, ByteDirectiveLine);
    HANDLE_RULE(dbyte_directive, DByteDirectiveLine);
    HANDLE_RULE(word_directive, WordDirectiveLine);
    HANDLE_RULE(text_directive, TextDirectiveLine);
    HANDLE_RULE(align_directive, AlignDirectiveLine);
    HANDLE_RULE(fill_directive, FillDirectiveLine);

#undef HANDLE_RULE
    std::cerr << "HANDLED NO RULES\n";
    return DirectiveResult::err(ParseError::LogicError);
}

auto DirectiveLine::format() const -> std::string
{
    std::string comment_str{""};
    if (comment != std::nullopt)
    {
        comment_str = " ;" + comment.value();
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
    return {};
}

} // namespace mos6502
