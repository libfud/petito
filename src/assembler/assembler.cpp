#include "assembler.hpp"
#include <cctype>

namespace mos6502 {

auto Instruction::make_instruction(
    const std::string& line,
    const SymbolMap& symbol_map) -> InstructionResult
{
    Instruction instruction;
    return InstructionResult::err(AsmError::FailedToLoad);
}

auto Assembler::tokenize() -> AsmParseResult
{
    for (const auto& line : input)
    {
        std::vector<Instruction> line_tokens{};
        auto result = Token::tokenize_line(line);
        if (result.is_ok())
        {
            token_lines.push_back(result.get_ok());
        }
        else
        {
            return AsmParseResult::err(result.get_err());
        }
    }
    return AsmParseResult::err(AsmError::InvalidToken);
}

} // namespace mos6502
