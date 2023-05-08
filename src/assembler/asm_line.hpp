#ifndef ASM_LINE_HPP
#define ASM_LINE_HPP

#include <cstdint>
#include <format>
#include <optional>
#include <string>
#include <variant>

#include "assembler_types.hpp"
#include "asm_instruction.hpp"
#include "asm_directive.hpp"
#include "arithmetic.hpp"
#include "gen/asm6502Parser.h"
#include "result/result.hpp"

namespace mos6502 {

using LineContext = asm6502Parser::LineContext;
using result::Result;

struct LabelLine {
    using LabelResult = Result<LabelLine, ParseError>;
    static auto make(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> LabelResult;
    auto format() const -> std::string;
    constexpr auto serialize() const -> std::array<uint8_t, 0> { return {}; }
    constexpr auto program_counter() const -> uint16_t
    {
        return pc;
    }
    constexpr auto size() const -> uint16_t { return 0; }
    constexpr auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
    {
        return {};
    }

    std::string label;
    uint16_t pc;
    std::optional<std::string> comment;
};

struct CommentLine {
    constexpr auto format() const -> std::string {
        return comment;
    }
    constexpr auto serialize() const -> std::array<uint8_t, 0> { return {}; }
    constexpr auto program_counter() const -> uint16_t
    {
        return pc;
    }
    constexpr auto size() const -> uint16_t { return 0; }
    constexpr auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
    {
        return {};
    }

    std::string comment;
    uint16_t pc;
};

class AssignLine {
public:
    using AssignResult = Result<AssignLine, ParseError>;
    static auto make(LineContext* line, uint16_t pc, SymbolMap& symbol_map) -> AssignResult;
    auto format() const -> std::string {
        return std::format("{} EQU {}", name, value.value());
    }
    constexpr auto serialize() const -> std::array<uint8_t, 0> { return {}; }
    constexpr auto program_counter() const -> uint16_t
    {
        return pc;
    }
    constexpr auto size() const -> uint16_t { return 0; }
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;

private:
    std::string name;
    uint16_t pc = 0;
    ArithmeticExpression expression = {};
    std::optional<int16_t> value;
    std::optional<std::string> comment;
};

struct EmptyLine {
    constexpr auto format() const -> std::string { return ""; };
    constexpr auto program_counter() const -> uint16_t
    {
        return pc;
    }
    constexpr auto size() const -> uint16_t { return 0; }
    constexpr auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>
    {
        return {};
    }
    constexpr auto serialize() const -> std::array<uint8_t, 0> { return {}; }
    uint16_t pc = 0;
};

using AsmLineType = std::variant<
    EmptyLine,
    AsmInstructionLine,
    CommentLine,
    LabelLine,
    AssignLine,
    DirectiveLine
    >;

class AsmLine {
public:
    using ParseResult = Result<AsmLine, ParseError>;
    static auto make(LineContext* line, uint16_t pc, SymbolMap& symbols) -> ParseResult;
    auto program_counter() const -> uint16_t;
    auto size() const -> uint16_t;
    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;
    auto format() const -> std::string;
    auto serialize() const -> AsmLineBytes;
    constexpr auto is_empty_line() -> bool {
        return std::holds_alternative<EmptyLine>(line);
    }
protected:
    static auto make_instruction(
        LineContext* line,
        uint16_t pc,
        SymbolMap& symbol_map) -> ParseResult;
    static auto make_assign(
        LineContext* line,
        uint16_t pc,
        SymbolMap& symbol_map) -> ParseResult;
    static auto make_label(
        LineContext* line,
        uint16_t pc,
        SymbolMap& symbol_map) -> ParseResult;
    static auto make_directive(
        LineContext* line,
        uint16_t pc,
        SymbolMap& symbol_map) -> ParseResult;
    static auto make_comment(
        LineContext* line,
        uint16_t pc,
        SymbolMap& symbol_map) -> ParseResult;
private:
    AsmLineType line = EmptyLine{};
};

} // namespace mos6502

#endif
