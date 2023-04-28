#include "assembler.hpp"
#include "gen/asm6502Lexer.h"
#include "gen/asm6502Parser.h"
#include "../logger/logger.hpp"

#include <cctype>
#include <iostream>
#include <format>

namespace mos6502 {

auto Assembler::from_file_name(const std::string& name) -> AssemblerResult
{
    return from_file_name(std::string{name});
}

auto Assembler::from_file_name(std::string&& name) -> AssemblerResult
{
    using RetType = AssemblerResult;

    Assembler assembler{};
    assembler.file_name = name;
    std::ifstream stream;
    stream.open(assembler.file_name.value());

    if (!stream.is_open())
    {
        return RetType::err(AsmError::FailedToLoad);
    }

    antlr4::ANTLRInputStream input(stream);
    asm6502Lexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    asm6502Parser parser(&tokens);
    asm6502Parser::ProgramContext* program_file = parser.program();

    const auto& lines = program_file->line();
    assembler.program.reserve(lines.size());
    assembler.program_counter_lines.reserve(lines.size());

    size_t pc = 0;
    for (auto idx = 0; idx < lines.size(); ++idx)
    {
        auto instruction_result = Line::make(lines[idx]);
        if (instruction_result.is_err())
        {
            return RetType::err(AsmError::BadParse);
        }
        auto instruction = instruction_result.get_ok();
        if (instruction.has_label())
        {
            auto label = instruction.get_label();
            if (assembler.symbols.contains(label))
            {
                return RetType::err(AsmError::SymbolRedefined);
            }
            assembler.symbols[label] = pc;
            if (label.ends_with(":"))
            {
                assembler.symbols[label.substr(0, label.size() - 1)] = pc;
            }
        }
        auto size = instruction.size();
        assembler.program_counter_lines.push_back(pc + size);
        assembler.program.push_back(std::move(instruction));
        pc += size;
    }
    for (auto idx = 0; idx < assembler.program.size(); ++idx)
    {
        auto& instruction = assembler.program[idx];
        auto pc_line = assembler.program_counter_lines[idx];
        auto res = instruction.complete_decode(assembler.symbols, pc_line);
        if (res != std::nullopt)
        {
            logger::error(
                "Error {} decoding  at line {}\nLine: {}",
                static_cast<uint32_t>(res.value()),
                idx + 1,
                lines[idx]->getText());
            return RetType::err(res.value());
        }
    }

    return RetType::ok(assembler);
}

auto Assembler::format() const -> std::string {
    std::string output{};

    size_t pc = 0;
    for (const auto& instruction : program)
    {
        output += std::format("{:04X}\t{}\n", pc, instruction.format());
        pc += instruction.size();
    }

    return output;
}

} // namespace mos6502
