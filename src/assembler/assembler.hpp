#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <cstdint>
#include <string>
#include <optional>
#include <variant>
#include <set>
#include <vector>

#include "result/result.hpp"
#include "assembler_types.hpp"
#include "asm_line.hpp"
#include "gen/asm6502Parser.h"

namespace mos6502 {

using result::Result;

class Assembler {
public:
    using AsmParseResult = Result<Assembler, ParseError>;

    static auto from_file_name(const std::string& name) -> AsmParseResult;
    static auto from_file_name(std::string&& name) -> AsmParseResult;
    static auto from_text(const std::string& text) -> AsmParseResult;

    auto format() const -> std::string;
    auto size() const -> uint16_t;

    auto serialize() const -> const std::vector<uint8_t>&;

protected:
    auto from_stream(std::istream& stream) -> std::optional<ParseError>;
    using ProgramContext = asm6502Parser::ProgramContext;
    auto make_lines(ProgramContext* program_file) -> std::optional<ParseError>;
    auto evaluate() -> std::optional<ParseError>;

private:
    std::optional<std::string> file_name = {};
    std::map<std::string, std::set<size_t>> label_lines = {};
    SymbolMap symbols = {};
    std::vector<AsmLine> program = {};
    std::vector<uint8_t> program_bytes = {};
    size_t line_index = 0;
};

} // namespace mos6502

#endif
