#include <cstdint>
#include <map>
#include <string>
#include <optional>
#include <variant>
#include <vector>

#include "result/result.hpp"
#include "opcode_table.hpp"

namespace mos6502 {

using result::Result;

using SymbolMap = std::map<std::string, uint16_t>;
using InputStream = std::vector<std::string>;

enum class Base : uint8_t {
    Binary = 2,
    Octal = 8,
    Decimal = 10,
    Hex = 16,
};

const std::map<char, int8_t> HEX_MAP{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
    {'A', 0xA}, {'B', 0xB}, {'C', 0xC}, {'D', 0xD}, {'E', 0xE}, {'F', 0xF},
    {'a', 0xA}, {'b', 0xB}, {'c', 0xC}, {'d', 0xD}, {'e', 0xE}, {'f', 0xF}};

const std::map<char, int8_t> DECIMAL_MAP{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}};

const std::map<char, int8_t> OCTAL_MAP{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}};

const std::map<char, int8_t> BINARY_MAP{{'0', 0}, {'1', 1}};

const std::map<Base, const std::map<char, int8_t>&> BASE_MAP
{
    {Base::Binary, BINARY_MAP},
    {Base::Octal, OCTAL_MAP},
    {Base::Decimal, DECIMAL_MAP},
    {Base::Hex, HEX_MAP}
};

enum class NumberParseError {
    InvalidIndex = 0,
    InvalidZeroPrefix,
    InvalidDigit,
    Generic
};

struct NumericPrefix {
    Base base;
    size_t length;
};

using NumberPrefixParseResult = Result<std::optional<NumericPrefix>, NumberParseError>;
auto check_numeric_prefix(
    const std::string& input,
    const size_t index) -> NumberPrefixParseResult;

using NumberParseResult = Result<std::optional<int32_t>, NumberParseError>;
auto make_number(
    const std::string& input,
    const size_t index,
    size_t& length) -> NumberParseResult;

enum class AsmError {
    FailedToLoad,
    NoTokenToParse,
    InvalidToken,
    InvalidPragma,
    InvalidComma,
    BadNumber,
    BadChar,
};

enum class ArithmeticOp: char {
    Add = '+',
    Subtract = '-',
    Multiply = '*',
    Divide = '/',
};

bool is_arith_op(char c);

enum class Pragma {
    Byte,
    Dbyte,
    Word,
    Text,
    Fill,
    Repeat,
};

const std::map<std::string, Pragma> PRAGMA_MAP {
    {"BYTE", Pragma::Byte},
    {"DBYTE", Pragma::Dbyte},
    {"WORD", Pragma::Word},
    {"TEXT", Pragma::Text},
    {"FILL", Pragma::Fill},
    {"REPEAT", Pragma::Repeat},
};

namespace token {
struct Label { std::string value; };
struct Comment { std::string value; };
struct Mnemonic { OpName value; };
struct Hash {};
struct Char { char value; };
struct Byte { uint8_t value; };
struct Address { uint16_t value; };
struct MathOp { ArithmeticOp value; };
struct LParen {};
struct RParen {};
struct LBracket {};
struct RBracket {};
struct CommaX {};
struct CommaY {};
struct Directive { Pragma value; };
struct Symbol { std::string value; };
using TokenVariant = std::variant<
    Label,
    Comment,
    Mnemonic,
    Hash,
    Char,
    Byte,
    Address,
    MathOp,
    LParen,
    RParen,
    LBracket,
    RBracket,
    CommaX,
    CommaY,
    Directive,
    Symbol>;
} // namespace token

enum class TokenType : uint8_t {
    Label = 0,
    Comment,
    Mnemonic,
    Hash,
    Char,
    Byte,
    Address,
    MathOp,
    LParen,
    RParen,
    LBracket,
    RBracket,
    CommaX,
    CommaY,
    Directive,
    Symbol,
};

using token::TokenVariant;

class Token {
public:
    explicit Token(TokenVariant token_value);
    using ParseTokenResult = Result<std::optional<Token>, AsmError>;
    using TokenStreamResult = Result<std::vector<Token>, AsmError>;

    static auto tokenize_line(const std::string& input) -> TokenStreamResult;
    auto get() const -> const TokenVariant&;
    auto token_type() const -> TokenType;

private:
    static auto tokenize_iter(const std::string& input, size_t& index) -> ParseTokenResult;
    TokenVariant value;

    static auto make_label(
        const std::string& input,
        size_t index,
        size_t& end_index) -> std::optional<Token>;

    static auto make_comment(
        const std::string& input,
        size_t index,
        size_t& end_index) -> std::optional<Token>;

    static auto make_mnemonic(
        const std::string& input,
        size_t index,
        size_t& end_index) -> std::optional<Token>;

    static auto make_hash(
        const std::string& input,
        size_t index,
        size_t& end_index) -> std::optional<Token>;

    static auto make_char(
        const std::string& input,
        size_t index,
        size_t& end_index) -> ParseTokenResult;

    static auto make_byte(
        const std::string& input,
        size_t index,
        size_t& end_index) -> ParseTokenResult;

    static auto make_address(
        const std::string& input,
        size_t index,
        size_t& end_index) -> ParseTokenResult;

    static auto make_math_op(
        const std::string& input,
        size_t index,
        size_t& end_index) -> std::optional<Token>;

    static auto make_bracket(
        const std::string& input,
        size_t index,
        size_t& end_index) -> std::optional<Token>;

    static auto make_comma_register(
        const std::string& input,
        size_t index,
        size_t& end_index) -> ParseTokenResult;

    static auto make_pragma(
        const std::string& input,
        size_t index,
        size_t& end_index) -> ParseTokenResult;

    static auto make_symbol(
        const std::string& input,
        size_t index,
        size_t& end_index) -> std::optional<Token>;
};

} // namespace mos6502
