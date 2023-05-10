#ifndef ASSEMBLER_TYPES_HPP
#define ASSEMBLER_TYPES_HPP

#include <cstdint>
#include <string>
#include <unordered_map>

namespace mos6502 {

using SymbolMap = std::unordered_map<std::string, uint16_t>;

enum class Base : uint8_t {
    Binary = 2,
    Octal = 8,
    Decimal = 10,
    Hex = 16,
};

const std::unordered_map<char, int8_t> HEX_MAP{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
    {'A', 0xA}, {'B', 0xB}, {'C', 0xC}, {'D', 0xD}, {'E', 0xE}, {'F', 0xF},
    {'a', 0xA}, {'b', 0xB}, {'c', 0xC}, {'d', 0xD}, {'e', 0xE}, {'f', 0xF}};

const std::unordered_map<char, int8_t> DECIMAL_MAP{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}};

const std::unordered_map<char, int8_t> OCTAL_MAP{
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}};

const std::unordered_map<char, int8_t> BINARY_MAP{{'0', 0}, {'1', 1}};

const std::unordered_map<Base, const std::unordered_map<char, int8_t>&> BASE_MAP
{
    {Base::Binary, BINARY_MAP},
    {Base::Octal, OCTAL_MAP},
    {Base::Decimal, DECIMAL_MAP},
    {Base::Hex, HEX_MAP}
};

enum class ParseError {
    FailedToLoad,
    SyntaxError,
    InvalidLabelParse,
    InvalidCommentParse,
    InvalidOpIdParse,
    InvalidHashParse,
    IllegalRepeatVar,
    BadCount,
    BadArithmetic,
    BadAssign,
    BadNumber,
    BadEscape,
    BadEvaluation,
    InvalidRange,
    SymbolUndefined,
    SymbolRedefined,
    LogicError,
};

} // namespace mos6502

#endif
