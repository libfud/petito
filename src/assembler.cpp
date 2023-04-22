#include "assembler.hpp"
#include <cctype>

namespace mos6502 {

bool is_hspace(char c) { return c == ' ' || c == '\t'; }

Token::Token(TokenVariant token_value) : value{token_value} {}

auto Token::get() const -> const TokenVariant& { return value; }

auto Token::token_type() const -> TokenType
{
    return static_cast<TokenType>(value.index());
}

auto Token::tokenize_line(const std::string& input) -> TokenStreamResult
{
    size_t index = 0;
    std::vector<Token> tokens;

    auto check_token_type = [&](size_t end_index, auto tokenizer) -> bool {
        auto token_end_index = end_index;
        auto maybe_token = tokenizer(input, index, token_end_index);
        if (maybe_token)
        {
            tokens.push_back(maybe_token.value());
            end_index = token_end_index;
            index = end_index + 1;
        }

        return maybe_token != std::nullopt;
    };

    while (index < input.length())
    {
        size_t end_index = index + 1;
        if (std::isspace(input[index]))
        {
            index = end_index + 1;
            continue;
        }

        bool token_found = false;

        token_found = check_token_type(end_index, make_label);
        if (token_found) { continue; }

        token_found = check_token_type(end_index, make_comment);
        if (token_found) { continue; }

        token_found = check_token_type(end_index, make_mnemonic);
        if (token_found) { continue; }

        index = end_index;
    }
    return TokenStreamResult::ok(tokens);
}

auto Token::make_label(
    const std::string& input,
    size_t index,
    size_t& end_index) -> std::optional<Token>
{
    if (!std::isalpha(input[index]))
    {
        return {};
    }
    bool found_label = false;
    while (end_index < input.length() && !found_label)
    {
        if (std::isspace(input[end_index]))
        {
            return {};
        }
        if (input[end_index] == ':')
        {
            found_label = true;
        }
        end_index++;
    }
    const auto length = end_index - index - 1;
    if (found_label && end_index < input.length())
    {
        found_label = std::isspace(input[end_index]);
        end_index++;
    }
    if (found_label)
    {
        return Token{TokenVariant{token::Label{input.substr(index, length)}}};
    }
    return {};
}

auto Token::make_comment(
    const std::string& input,
    size_t index,
    size_t& end_index) -> std::optional<Token>
{
    if (input[index] != ';')
    {
        return {};
    }

    size_t start_index = index + 1;
    while (start_index < input.length() && input[start_index] == ';')
    {
        start_index++;
    }
    while (start_index < input.length() && std::isspace(input[start_index]))
    {
        start_index++;
    }

    end_index = input.length() - 1;
    while (std::isspace(input[end_index]) && end_index > (start_index + 1))
    {
        end_index--;
    }

    const auto length = end_index - start_index + 1;
    return Token{TokenVariant{token::Comment{input.substr(start_index, length)}}};
}

auto Token::make_mnemonic(
    const std::string& input,
    size_t index,
    size_t& end_index) -> std::optional<Token>
{
    if (index + 2 >= input.length() ||
        !std::isalpha(input[index + 0]) ||
        !std::isalpha(input[index + 1]) ||
        !std::isalpha(input[index + 2]))
    {
        return {};
    }

    if ((index + 3) < input.length() && !std::isspace(input[index + 3]))
    {
        return {};
    }

    std::string mnemonic{input.substr(index, 3)};
    if (!MNEMONIC_MAP.contains(mnemonic))
    {
        return {};
    }

    end_index = index + 3;
    return Token{TokenVariant{token::Mnemonic{MNEMONIC_MAP.at(mnemonic)}}};
}

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
