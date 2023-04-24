#include <cstdint>
#include <map>
#include <string>
#include <optional>
#include <variant>
#include <vector>

#include "tokenizer.hpp"
#include "result/result.hpp"
#include "opcode_table.hpp"

namespace mos6502 {

using result::Result;

using SymbolMap = std::map<std::string, uint16_t>;
using InputStream = std::vector<std::string>;

class Instruction {
public:
    using InstructionResult = Result<Instruction, AsmError>;
    using DecodeResult = Result<bool, AsmError>;
    static auto make_instruction(
        const std::string& line,
        const SymbolMap& symbol_map) -> InstructionResult;
    auto complete_decode(const SymbolMap& symbol_map) -> InstructionResult;

private:
    OpName op_id;
    AddressMode foo;
    std::vector<std::string> symbolic_operands;
    std::vector<uint8_t> operands;
    bool complete;
};

enum class LineType {
    Instruction,
    Comment,
    Label,
    Directive,
    Invalid
};

class Assembler {
public:

    using AssemblerResult = Result<Assembler, AsmError>;
    using AsmParseResult = Result<Assembler, AsmError>;

    auto from_file_name(const std::string& name) -> AssemblerResult;
    auto from_file_name(std::string&& name) -> AssemblerResult;

    auto parse() -> AsmParseResult;

private:
    LineType classify_line();

    auto tokenize() -> AsmParseResult;

    std::optional<std::string> file_name;
    InputStream input;
    std::vector<std::vector<Token>> token_lines;
    std::vector<Instruction> program;
};

} // namespace mos6502
