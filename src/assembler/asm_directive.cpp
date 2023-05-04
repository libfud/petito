#include "asm_directive.hpp"

#include <ranges>

namespace mos6502 {

auto OrgLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> OrgResult
{
    return OrgResult::err(ParseError::LogicError);
}

auto ByteDirectiveLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> ByteDirResult
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

auto DByteDirectiveLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> DByteDirResult
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

auto WordDirectiveLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> WordDirResult
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

auto TextDirectiveLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> TextDirResult
{
    return TextDirResult::err(ParseError::LogicError);
}

auto TextDirectiveLine::serialize() const -> std::vector<uint8_t>
{
    return std::vector<uint8_t>{text.begin(), text.end()};
}

auto AlignDirectiveLine::format() const -> std::string
{
    return std::format(".ALIGN ${:04X} ${:02X}", alignment, fill);
}

auto AlignDirectiveLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> AlignDirResult
{
    return AlignDirResult::err(ParseError::LogicError);
}

auto FillDirectiveLine::make(asm6502Parser::LineContext* line, uint16_t pc) -> FillDirResult
{
    return FillDirResult::err(ParseError::LogicError);
}

} // namespace mos6502
