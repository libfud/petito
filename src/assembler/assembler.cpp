#include "assembler.hpp"
#include "gen/asm6502Lexer.h"
#include "gen/asm6502Parser.h"
#include "../logger/logger.hpp"

#include <cctype>
#include <iostream>
#include <format>

namespace mos6502 {

auto Assembler::from_file_name(const std::string& name) -> AsmParseResult
{
    return from_file_name(std::string{name});
}

auto Assembler::from_file_name(std::string&& name) -> AsmParseResult
{
    using RetType = AsmParseResult;

    Assembler assembler{};
    assembler.file_name = name;
    std::ifstream stream;
    stream.open(assembler.file_name.value());

    if (!stream.is_open())
    {
        return RetType::err(ParseError::FailedToLoad);
    }

    auto parse_error = assembler.from_stream(stream);
    if (parse_error != std::nullopt)
    {
        return RetType::err(parse_error.value());
    }
    return RetType::ok(assembler);
}

auto Assembler::from_text(const std::string& text) -> AsmParseResult
{
    using RetType = AsmParseResult;
    std::istringstream stream(text);

    Assembler assembler{};

    auto parse_error = assembler.from_stream(stream);
    if (parse_error != std::nullopt)
    {
        return RetType::err(parse_error.value());
    }
    return RetType::ok(assembler);
}

auto Assembler::from_stream(std::istream& stream) -> std::optional<ParseError>
{
    antlr4::ANTLRInputStream input(stream);
    asm6502Lexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    asm6502Parser parser(&tokens);
    ProgramContext* program_file = parser.program();

    auto make_lines_result = make_lines(program_file);
    if (make_lines_result != std::nullopt)
    {
        return make_lines_result;
    }

    auto evaluate_result = evaluate();
    if (evaluate_result != std::nullopt)
    {
        logger::error(
            "Error {} decoding  at line {}\nLine: {}",
            static_cast<uint32_t>(evaluate_result.value()),
            line_index + 1,
            program_file->line(line_index)->getText());
    }

    return {};
}

auto Assembler::make_lines(ProgramContext* program_file) -> std::optional<ParseError>
{
    const auto& lines = program_file->line();
    program.reserve(lines.size());

    size_t pc = 0;
    for (size_t idx = 0; idx < lines.size(); ++idx)
    {
        auto instruction_result = AsmLine::make(lines[idx], pc);
        if (instruction_result.is_err())
        {
            return instruction_result.get_err();
        }
        auto instruction = instruction_result.get_ok();
        if (instruction.has_label())
        {
            auto label = instruction.get_label();
            if (symbols.contains(label))
            {
                return ParseError::SymbolRedefined;
            }
            symbols[label] = pc;
            if (label.ends_with(":") && label.size() > 1)
            {
                symbols[label.substr(0, label.size() - 2)] = pc;
            }
        }
        auto size = instruction.size();
        pc += size;
        program.push_back(std::move(instruction));
    }
    program_bytes.reserve(pc);

    return {};
}

auto Assembler::evaluate() -> std::optional<ParseError>
{
    for (size_t idx = 0; idx < program.size(); ++idx)
    {
        auto& instruction = program[idx];
        auto res = instruction.evaluate(symbols);
        if (res != std::nullopt)
        {
            line_index = idx;
            return res;
        }
        std::visit(
            [&](const auto& v){ program_bytes.insert(program_bytes.end(), v.begin(), v.end()); },
            instruction.serialize());
    }
    return {};
}

auto Assembler::format() const -> std::string {
    std::string output{};

    for (const auto& instruction : program)
    {
        output += std::format("\t{}\n", instruction.format());
    }

    return output;
}

auto Assembler::size() const -> uint16_t {
    if (program.size() == 0)
    {
        return 0;
    }
    return program.back().program_counter() + program.back().size();
}

auto Assembler::serialize() const -> const std::vector<uint8_t>&
{
    return program_bytes;
}

} // namespace mos6502
