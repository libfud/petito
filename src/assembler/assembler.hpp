#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <cstdint>
#include <map>
#include <string>
#include <optional>
#include <variant>
#include <set>
#include <vector>

#include "result/result.hpp"
#include "assembler_types.hpp"
#include "asm_line.hpp"

namespace mos6502 {

using result::Result;

class Assembler {
public:

    using AssemblerResult = Result<Assembler, AsmError>;
    using AsmParseResult = Result<Assembler, AsmError>;

    static auto from_file_name(const std::string& name) -> AssemblerResult;
    static auto from_file_name(std::string&& name) -> AssemblerResult;

    auto parse() -> AsmParseResult;

    auto format() const -> std::string;

private:
    std::optional<std::string> file_name = {};
    std::map<std::string, std::set<size_t>> label_lines = {};
    SymbolMap symbols = {};
    std::vector<AsmLine> program = {};
    std::vector<size_t> program_counter_lines = {};
};

} // namespace mos6502

#endif
