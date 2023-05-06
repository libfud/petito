#ifndef ASM_DIRECTIVE_HPP
#define ASM_DIRECTIVE_HPP

#include "assembler_types.hpp"
#include "asm_instruction.hpp"
#include "arithmetic.hpp"
#include "result/result.hpp"

#include <cstdint>
#include <optional>
#include <variant>

namespace mos6502
{

using result::Result;

class OrgLine {
public:
    using OrgResult = Result<OrgLine, ParseError>;
    static auto make(asm6502Parser::OrgContext* line, uint16_t pc) -> OrgResult;
    auto format() const -> std::string {
        return std::format(".ORG ${:04X}", pc);
    }
    constexpr auto serialize() const -> std::vector<uint8_t> { return {}; }
    constexpr auto size() const -> uint16_t { return 0; }
    constexpr auto program_counter() const -> uint16_t { return pc; }
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;
private:
    uint16_t pc;
};


class ByteDirectiveLine {
public:
    using ByteDirResult = Result<ByteDirectiveLine, ParseError>;
    static auto make(asm6502Parser::Byte_directiveContext* line, uint16_t pc) -> ByteDirResult;
    auto format() const -> std::string;
    constexpr auto serialize() const -> std::vector<uint8_t> { return bytes; }
    constexpr auto size() const -> uint16_t { return bytes.size(); }
    constexpr auto program_counter() const -> uint16_t { return pc; }
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;
private:
    uint16_t pc;
    std::vector<uint8_t> bytes;
};

class DByteDirectiveLine {
public:
    struct DByte {
        uint8_t low;
        uint8_t high;
    };
    using DByteDirResult = Result<DByteDirectiveLine, ParseError>;
    static auto make(asm6502Parser::Dbyte_directiveContext* line, uint16_t pc) -> DByteDirResult;
    auto format() const -> std::string;
    auto serialize() const -> std::vector<uint8_t>;
    constexpr auto size() const -> uint16_t { return 2 * dbytes.size(); }
    constexpr auto program_counter() const -> uint16_t { return pc; }
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;
private:
    uint16_t pc;
    std::vector<DByte> dbytes;
};

class WordDirectiveLine {
public:
    struct Word {
        uint8_t low;
        uint8_t high;
    };
    using WordDirResult = Result<WordDirectiveLine, ParseError>;
    static auto make(asm6502Parser::Word_directiveContext* line, uint16_t pc) -> WordDirResult;
    auto format() const -> std::string;
    auto serialize() const -> std::vector<uint8_t>;
    constexpr auto size() const -> uint16_t { return 2 * dbytes.size(); }
    constexpr auto program_counter() const -> uint16_t { return pc; }
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;
private:
    uint16_t pc;
    std::vector<Word> dbytes;
};

class TextDirectiveLine {
public:
    using TextDirResult = Result<TextDirectiveLine, ParseError>;
    static auto make(asm6502Parser::Text_directiveContext* line, uint16_t pc) -> TextDirResult;
    constexpr auto format() const -> std::string { return text; }
    auto serialize() const -> std::vector<uint8_t>;
    constexpr auto size() const -> uint16_t { return text.size(); }
    constexpr auto program_counter() const -> uint16_t { return pc; }
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;
private:
    uint16_t pc;
    std::string text;
    std::vector<char> characters;
};

class AlignDirectiveLine {
public:
    using AlignDirResult = Result<AlignDirectiveLine, ParseError>;
    static auto make(asm6502Parser::Align_directiveContext* line, uint16_t pc) -> AlignDirResult;
    auto format() const -> std::string;
    auto serialize() const -> std::vector<uint8_t> {
        return std::vector<uint8_t>(size(), fill);
    }
    constexpr auto size() const -> uint16_t {
        return (pc / alignment + 1) * alignment - pc;
    }
    constexpr auto program_counter() const -> uint16_t { return pc; }
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;
private:
    uint16_t pc;
    uint16_t alignment = 2;
    uint8_t fill = 0;
};

class FillDirectiveLine {
public:
    using FillDirResult = Result<FillDirectiveLine, ParseError>;
    static auto make(asm6502Parser::Fill_directiveContext* line, uint16_t pc) -> FillDirResult;
    auto format() const -> std::string;
    auto serialize() const -> std::vector<uint8_t> {
        return std::vector<uint8_t>(size(), fill);
    }
    constexpr auto size() const -> uint16_t { return count; }
    constexpr auto program_counter() const -> uint16_t { return pc; }
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;
private:
    uint16_t pc;
    uint16_t count;
    uint8_t fill = 0;
};

using DirectiveType = std::variant<
    OrgLine,
    ByteDirectiveLine,
    DByteDirectiveLine,
    WordDirectiveLine,
    TextDirectiveLine,
    AlignDirectiveLine,
    FillDirectiveLine
    >;

class DirectiveLine {
public:
    using DirectiveResult = Result<DirectiveLine, ParseError>;
    static auto make(asm6502Parser::LineContext* line, uint16_t pc) -> DirectiveResult;
    auto format() const -> std::string;
    auto serialize() const -> std::vector<uint8_t>;
    constexpr auto has_label() const -> bool { return false; }
    auto program_counter() const -> uint16_t;
    auto size() const -> uint16_t;
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;

private:
    DirectiveType directive;
    std::optional<std::string> comment;
};

} // namespace mos6502


#endif
