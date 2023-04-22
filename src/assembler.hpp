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

enum class AsmError {
    FailedToLoad,
    InvalidToken,
};

namespace token {
struct Label { std::string value; };
struct Comment { std::string value; };
struct Mnemonic { OpName value; };
struct Hash {};
struct Quote {};
struct Dollar {};
struct LParen {};
struct RParen {};
struct CommaX {};
struct CommaY {};
struct Char { char value; };
struct Symbol { std::string value; };
using TokenVariant = std::variant<
    Label,
    Comment,
    Mnemonic,
    Hash,
    Quote,
    Dollar,
    LParen,
    RParen,
    CommaX,
    CommaY,
    Char,
    Symbol>;
} // namespace token

enum class TokenType {
    Label = 0,
    Comment,
    Mnemonic,
    Hash,
    Quote,
    Dollar,
    LParen,
    RParen,
    CommaX,
    CommaY,
    Char,
    Symbol
};

using token::TokenVariant;

class Token {
public:
    explicit Token(TokenVariant token_value);
    using TokenStreamResult = Result<std::vector<Token>, AsmError>;
    static auto tokenize_line(const std::string& input) -> TokenStreamResult;
    auto get() const -> const TokenVariant&;
    auto token_type() const -> TokenType;

private:
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
};

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
