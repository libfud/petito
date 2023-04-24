#include "tokenizer.hpp"

#include <cctype>
#include <map>

namespace mos6502 {

bool is_arith_op(char c)
{
    switch (c)
    {
    case '+': return true;
    case '-': return true;
    case '*': return true;
    case '/': return true;
    default: return false;
    }
}

bool is_numeric_delimiter(char c)
{
    return std::isspace(c)
        || c == ','
        || c == ')'
        || is_arith_op(c)
        || c == '[' || c == ']';
}

auto check_numeric_prefix(
    const std::string& input,
    const size_t index) -> NumberPrefixParseResult
{
    using RetType = NumberPrefixParseResult;

    if (index >= input.length())
    {
        return RetType::err(NumberParseError::InvalidIndex);
    }

    const char c0 = input[index];
    const bool at_end = index == (input.length() - 1);
    if (std::isdigit(c0) && (at_end || is_numeric_delimiter(input[index + 1])))
    {
        if (c0 == '0')
        {
            return RetType::ok(NumericPrefix{Base::Octal, 0});
        }
        return RetType::ok(NumericPrefix{Base::Decimal, 0});
    }

    switch (c0)
    {
    case '$':
    case '&':
        return RetType::ok(NumericPrefix{Base::Hex, 1});
    case '@':
        return RetType::ok(NumericPrefix{Base::Octal, 1});
    case '%':
        return RetType::ok(NumericPrefix{Base::Binary, 1});
    default:
        break;
    }

    if (!std::isdigit(c0))
    {
        return RetType::ok({});
    }

    if (c0 != '0')
    {
        return RetType::ok(NumericPrefix{Base::Decimal, 0});
    }

    const auto c1 = input[index + 1];

    if (std::isdigit(c1))
    {
        if (c0 == '0')
        {
            return RetType::ok(NumericPrefix{Base::Octal, 1});
        }
        return RetType::ok(NumericPrefix{Base::Decimal, 0});
    }

    switch(c1)
    {
    case 'x':
        return RetType::ok(NumericPrefix{Base::Hex, 2});
    case 'd':
        return RetType::ok(NumericPrefix{Base::Decimal, 2});
    case 'b':
        return RetType::ok(NumericPrefix{Base::Binary, 2});
    case 'o':
        return RetType::ok(NumericPrefix{Base::Octal, 2});
    default:
        return RetType::err(NumberParseError::InvalidZeroPrefix);
    }
}

auto make_number(
    const std::string& input,
    size_t index,
    size_t& length) -> NumberParseResult
{
    using RetType = NumberParseResult;
    auto prefix_result = check_numeric_prefix(input, index);
    if (prefix_result.is_err())
    {
        return RetType::err(prefix_result.get_err());
    }
    auto prefix_opt = prefix_result.get_ok();
    if (prefix_opt == std::nullopt)
    {
        return RetType::ok({});
    }
    auto prefix = prefix_opt.value();

    const std::map<char, int8_t>& char_map = BASE_MAP.at(prefix.base);

    int32_t acc = 0;
    auto idx = index + prefix.length;
    while (idx < input.length())
    {
        auto letter = input[idx];
        if (is_numeric_delimiter(letter))
        {
            break;
        }
        if (!char_map.contains(letter))
        {
            return RetType::err(NumberParseError::InvalidDigit);
        }
        acc = acc * static_cast<uint8_t>(prefix.base) + char_map.at(letter);
        idx++;
    }
    length = idx - index;
    return RetType::ok(acc);
}

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

    auto check_token_type = [&](size_t& end_index, auto tokenizer) -> bool {
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

    auto check_token_result = [&](size_t& end_index, auto tokenizer) {
        auto token_end_index = end_index;
        auto maybe_token_result = tokenizer(input, index, token_end_index);
        if (maybe_token_result.is_err())
        {
            return Result<bool, AsmError>::err(maybe_token_result.get_err());
        }
        auto maybe_token = maybe_token_result.get_ok();
        if (maybe_token)
        {
            tokens.push_back(maybe_token.value());
            end_index = token_end_index;
            index = end_index + 1;
        }

        return Result<bool, AsmError>::ok(maybe_token != std::nullopt);
    };

    while (index < input.length())
    {
        size_t end_index = index + 1;

        bool token_found = false;

        if (!token_found)
        {
            token_found = check_token_type(end_index, make_label);
        }

        if (!token_found)
        {
            token_found = check_token_type(end_index, make_comment);
        }

        if (!token_found)
        {
            token_found = check_token_type(end_index, make_mnemonic);
        }

        if (!token_found)
        {
            token_found = check_token_type(end_index, make_hash);
        }

        if (!token_found)
        {
            auto char_token_found_result = check_token_result(end_index, make_char);
            if (char_token_found_result.is_err()) {
                return TokenStreamResult::err(char_token_found_result.get_err());
            }
            token_found = char_token_found_result.get_ok();
        }

        if (!token_found)
        {
            auto num_token_found_result = check_token_result(end_index, make_byte);
            if (num_token_found_result.is_err()) {
                return TokenStreamResult::err(num_token_found_result.get_err());
            }
            token_found = num_token_found_result.get_ok();
        }

        if (!token_found)
        {
            auto num_token_found_result = check_token_result(end_index, make_address);
            if (num_token_found_result.is_err()) {
                return TokenStreamResult::err(num_token_found_result.get_err());
            }
            token_found = num_token_found_result.get_ok();
        }

        if (!token_found)
        {
            token_found = check_token_type(end_index, make_math_op);
        }

        if (!token_found)
        {
            token_found = check_token_type(end_index, make_bracket);
        }

        if (!token_found)
        {
            auto register_token_found_result = check_token_result(end_index, make_comma_register);
            if (register_token_found_result.is_err()) {
                return TokenStreamResult::err(register_token_found_result.get_err());
            }
            token_found = register_token_found_result.get_ok();
        }

        if (!token_found)
        {
            auto pragma_token_found_result = check_token_result(end_index, make_comma_register);
            if (pragma_token_found_result.is_err()) {
                return TokenStreamResult::err(pragma_token_found_result.get_err());
            }
            token_found = pragma_token_found_result.get_ok();
        }

        if (!token_found)
        {
            token_found = check_token_type(end_index, make_symbol);
        }

        if (!token_found)
        {
            index++;
            // return TokenStreamResult::err(AsmError::NoTokenToParse);
            // do nothing for now I guess
        }
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

    end_index = index + 2;
    return Token{TokenVariant{token::Mnemonic{MNEMONIC_MAP.at(mnemonic)}}};
}

auto make_char_token(
    const std::string& input,
    size_t index,
    size_t& end_index,
    char c,
    TokenVariant v) -> std::optional<Token>
{
    if (input[index] == c)
    {
        end_index = index;
        return Token{v};
    }
    return {};
}

auto Token::make_hash(
    const std::string& input,
    size_t index,
    size_t& end_index) -> std::optional<Token>
{
    return make_char_token(input, index, end_index, '#', TokenVariant{token::Hash{}});
}

auto Token::make_char(
    const std::string& input,
    size_t index,
    size_t& end_index) -> ParseTokenResult
{
    if (input[index] == '\'')
    {
        if (index + 1 == input.length())
        {
            return ParseTokenResult::err(AsmError::BadChar);
        }
        char c = input[index + 1];
        if (!std::isprint(c))
        {
            return ParseTokenResult::err(AsmError::BadChar);
        }
        return ParseTokenResult::ok(Token{TokenVariant{token::Char{c}}});
    }
    return ParseTokenResult::ok({});
}

auto Token::make_byte(
    const std::string& input,
    size_t index,
    size_t& end_index) -> ParseTokenResult
{
    using RetType = ParseTokenResult;
    using token::Byte;
    size_t length = 0;
    auto number_option_result = make_number(input, index, length);
    if (number_option_result.is_err())
    {
        return RetType::err(AsmError::BadNumber);
    }
    auto number_option = number_option_result.get_ok();
    if (number_option == std::nullopt)
    {
        return RetType::ok({});
    }
    auto number = number_option.value();
    if (number > 0xFF)
    {
        return RetType::ok({});
    }
    end_index = index + length;
    return RetType::ok(Token{TokenVariant{Byte{static_cast<uint8_t>(number)}}});
}

auto Token::make_address(
    const std::string& input,
    size_t index,
    size_t& end_index) -> ParseTokenResult
{
    using RetType = ParseTokenResult;
    using token::Address;
    size_t length = 0;
    auto number_option_result = make_number(input, index, length);
    if (number_option_result.is_err())
    {
        return RetType::err(AsmError::BadNumber);
    }
    auto number_option = number_option_result.get_ok();
    if (number_option == std::nullopt)
    {
        return RetType::ok({});
    }
    auto number = number_option.value();
    if (number > 0xFFFF)
    {
        return RetType::err(AsmError::BadNumber);
    }
    end_index = index + length;
    return RetType::ok(Token{TokenVariant{Address{static_cast<uint16_t>(number)}}});
}

auto Token::make_math_op(
    const std::string& input,
    size_t index,
    size_t& end_index) -> std::optional<Token>
{
    char c = input[index];
    if (is_arith_op(c))
    {
        end_index = index;
        return Token{token::MathOp{static_cast<ArithmeticOp>(c)}};
    }
    return {};
}

auto Token::make_bracket(
    const std::string& input,
    size_t index,
    size_t& end_index) -> std::optional<Token>
{
    char c = input[index];
    std::optional<TokenVariant> v{};
    switch (c)
    {
    case '(':
        v = token::LParen{};
        break;
    case ')':
        v = token::RParen{};
        break;
    case '[':
        v = token::LBracket{};
        break;
    case ']':
        v = token::RBracket{};
        break;
    default: break;
    }
    if (v != std::nullopt)
    {
        end_index = index;
        return Token{v.value()};
    }
    return {};
}
auto Token::make_comma_register(
    const std::string& input,
    size_t index,
    size_t& end_index) -> ParseTokenResult
{
    using RetType = ParseTokenResult;
    using token::CommaX;
    using token::CommaY;

    const char c = input[index];
    if (c != ',')
    {
        return RetType::ok({});
    }

    if (index + 1 >= input.length())
    {
        return RetType::err(AsmError::InvalidComma);
    }

    const auto reg_name = input[index + 1];

    if (reg_name == 'x')
    {
        end_index = index + 1;
        return RetType::ok(Token{TokenVariant{CommaX{}}});
    }

    if (reg_name == 'y')
    {
        end_index = index + 1;
        return RetType::ok(Token{TokenVariant{CommaY{}}});
    }

    return RetType::err(AsmError::InvalidComma);
}

auto Token::make_pragma(
    const std::string& input,
    size_t index,
    size_t& end_index) -> ParseTokenResult
{
    using RetType = ParseTokenResult;
    using token::Directive;

    const char c = input[index];
    if (c != '.')
    {
        return RetType::ok({});
    }
    const auto start_index = index + 1;
    size_t substr_end_idx = start_index;

    if (substr_end_idx >= input.length())
    {
        return RetType::err(AsmError::InvalidPragma);
    }

    while (!isspace(input[substr_end_idx]) && substr_end_idx < input.length())
    {
        ++substr_end_idx;
    }

    const int length = substr_end_idx - start_index;
    if (length <= 0)
    {
        return RetType::err(AsmError::InvalidPragma);
    }
    const auto pragma{input.substr(start_index, length)};

    if (!PRAGMA_MAP.contains(pragma))
    {
        return RetType::err(AsmError::InvalidPragma);
    }

    end_index = substr_end_idx;
    return RetType::ok(Token{TokenVariant{Directive{PRAGMA_MAP.at(pragma)}}});
}

auto Token::make_symbol(
    const std::string& input,
    size_t index,
    size_t& end_index) -> std::optional<Token>
{
    using token::Symbol;

    const char c = input[index];
    if (!std::isalpha(c))
    {
        return {};
    }

    size_t substr_end_idx = index + 1;
    while (!isspace(input[substr_end_idx]) && substr_end_idx < input.length())
    {
        ++substr_end_idx;
    }
    const auto length = substr_end_idx - index;
    const auto symbol{input.substr(index, length)};

    if (MNEMONIC_MAP.contains(symbol))
    {
        return {};
    }

    end_index = substr_end_idx;
    return Token{TokenVariant{Symbol{symbol}}};
}

} // namespace mos6502
