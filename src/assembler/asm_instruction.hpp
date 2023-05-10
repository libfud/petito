#ifndef ASM_INSTRUCTION_HPP
#define ASM_INSTRUCTION_HPP

#include <cstdint>
#include <format>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <variant>

#include "assembler_types.hpp"
#include "arithmetic.hpp"
#include "opcode_table.hpp"
#include "gen/asm6502Parser.h"
#include "result/result.hpp"

namespace mos6502 {

using result::Result;

class InstructionLine {
public:
    constexpr InstructionLine() = default;
    constexpr InstructionLine(uint16_t pc, OpName op_id);

    virtual ~InstructionLine() = default;
    virtual auto address_mode() const -> AddressMode = 0;

    constexpr auto format() const -> std::string;

    constexpr auto program_counter() const -> uint16_t
    {
        return pc;
    }
    constexpr auto size() const -> uint16_t
    {
        return 1 + address_mode_num_bytes(address_mode());
    }
    auto opcode() const -> uint8_t
    {
        return OPCODE_MAP.at(address_mode()).at(op_id);
    }

    virtual auto evaluate(const SymbolMap&) -> std::optional<ParseError>;

protected:
    virtual constexpr auto format_instruction() const -> std::string = 0;
    uint16_t pc = {};
    OpName op_id = {};
};

class NIModeInstructionLine : public InstructionLine
{
public:
    using InstructionLine::InstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::NI; }
    auto serialize() const -> std::array<uint8_t, 1> { return {opcode()}; }

protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{}", opid_to_name(op_id));
    }
};

class ImplicitInstructionLine : public InstructionLine
{
public:
    using InstructionLine::InstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::IMPL; }
    auto serialize() const -> std::array<uint8_t, 1> { return {opcode()}; }

protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{}", opid_to_name(op_id));
    }
};

class AccInstructionLine : public InstructionLine
{
public:
    using InstructionLine::InstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::A; }
    auto serialize() const -> std::array<uint8_t, 1> { return {opcode()}; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} A", opid_to_name(op_id));
    }
};

class NOperandInstructionLine : public InstructionLine
{
public:
    NOperandInstructionLine(
        uint16_t pc,
        OpName op_id,
        ArithmeticExpression&& expression);
protected:
    ArithmeticExpression expression = {};
};

template <class T>
auto instruction_line_wrapper(
    uint16_t pc,
    OpName op_id,
    ArithmeticExpression&& expression) -> T
    requires(std::is_base_of<NOperandInstructionLine, T>::value)
{
    return T{pc, op_id, std::move(expression)};
}

class OneOperandInstructionLine : public NOperandInstructionLine
{
public:
    using NOperandInstructionLine::NOperandInstructionLine;
    virtual ~OneOperandInstructionLine() = default;
    virtual auto evaluate(const SymbolMap& symbol_map) -> std::optional<ParseError> override;
    auto serialize() const -> std::array<uint8_t, 2> {
        return {opcode(), operand};
    }

protected:
    uint8_t operand = 0;
};

class TwoOperandInstructionLine : public NOperandInstructionLine
{
public:
    using NOperandInstructionLine::NOperandInstructionLine;
    virtual ~TwoOperandInstructionLine() = default;
    virtual auto evaluate(const SymbolMap& symbol_map) -> std::optional<ParseError> override;
    auto serialize() const -> std::array<uint8_t, 3> {
        return {opcode(), operand_1, operand_2};
    }

protected:
    uint8_t operand_1 = 0;
    uint8_t operand_2 = 0;
};

class ImmediateInstructionLine : public OneOperandInstructionLine
{
public:
    using OneOperandInstructionLine::OneOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::IMM; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} #${:02X}", opid_to_name(op_id), operand);
    }
};

class RelativeInstructionLine : public OneOperandInstructionLine
{
public:
    using OneOperandInstructionLine::OneOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::REL; }
    virtual auto evaluate(const SymbolMap& symbol_map) -> std::optional<ParseError> override;
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} ${:04X} (${:02X})", opid_to_name(op_id), target_address, operand);
    }
private:
    uint16_t target_address = 0;
};

class ZeroPageInstructionLine : public OneOperandInstructionLine
{
public:
    using OneOperandInstructionLine::OneOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::ZPG; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} ${:02X}", opid_to_name(op_id), operand);
    }
};

class ZeroPageXInstructionLine : public OneOperandInstructionLine
{
public:
    using OneOperandInstructionLine::OneOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::ZPG_X; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} ${:02X},X", opid_to_name(op_id), operand);
    }
};

class ZeroPageYInstructionLine : public OneOperandInstructionLine
{
public:
    using OneOperandInstructionLine::OneOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::ZPG_Y; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} ${:02X},Y", opid_to_name(op_id), operand);
    }
};

class XIndirectInstructionLine : public OneOperandInstructionLine
{
public:
    using OneOperandInstructionLine::OneOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::X_IND; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} (${:02X},X)", opid_to_name(op_id), operand);
    }
};

class IndirectYInstructionLine : public OneOperandInstructionLine
{
public:
    using OneOperandInstructionLine::OneOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::IND_Y; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} (${:02X}),Y", opid_to_name(op_id), operand);
    }
};

class IndirectInstructionLine : public TwoOperandInstructionLine
{
public:
    using TwoOperandInstructionLine::TwoOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::IND; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} (${:02X}{:02X})", opid_to_name(op_id), operand_2, operand_1);
    }
};

class AbsoluteInstructionLine : public TwoOperandInstructionLine
{
public:
    using TwoOperandInstructionLine::TwoOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::ABS; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} ${:02X}{:02X}", opid_to_name(op_id), operand_2, operand_1);
    }
};

class AbsoluteXInstructionLine : public TwoOperandInstructionLine
{
public:
    using TwoOperandInstructionLine::TwoOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::ABS_X; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} ${:02X}{:02X},X", opid_to_name(op_id), operand_2, operand_1);
    }
};

class AbsoluteYInstructionLine : public TwoOperandInstructionLine
{
public:
    using TwoOperandInstructionLine::TwoOperandInstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::ABS_Y; }
protected:
    auto format_instruction() const -> std::string override
    {
        return std::format("{} ${:02X}{:02X},Y", opid_to_name(op_id), operand_2, operand_1);
    }
};

using InstructionLineMode = std::variant<
    NIModeInstructionLine,
    AccInstructionLine,
    AbsoluteInstructionLine,
    AbsoluteXInstructionLine,
    AbsoluteYInstructionLine,
    ImmediateInstructionLine,
    ImplicitInstructionLine,
    IndirectInstructionLine,
    XIndirectInstructionLine,
    IndirectYInstructionLine,
    RelativeInstructionLine,
    ZeroPageInstructionLine,
    ZeroPageXInstructionLine,
    ZeroPageYInstructionLine
    >;

template <typename T>
concept InstructionLineType =
    std::same_as<T, NIModeInstructionLine> ||
    std::same_as<T, AccInstructionLine> ||
    std::same_as<T, AbsoluteInstructionLine> ||
    std::same_as<T, AbsoluteXInstructionLine> ||
    std::same_as<T, AbsoluteYInstructionLine> ||
    std::same_as<T, ImmediateInstructionLine> ||
    std::same_as<T, ImplicitInstructionLine> ||
    std::same_as<T, IndirectInstructionLine> ||
    std::same_as<T, XIndirectInstructionLine> ||
    std::same_as<T, IndirectYInstructionLine> ||
    std::same_as<T, RelativeInstructionLine> ||
    std::same_as<T, ZeroPageInstructionLine> ||
    std::same_as<T, ZeroPageXInstructionLine> ||
    std::same_as<T, ZeroPageYInstructionLine>;

template <typename T>
concept HasExpression = requires(T t) {
    { t.expression() } -> std::same_as<asm6502Parser::ExpressionContext*>;
};

template <typename T>
concept HasShiftAndMnemonic = requires(T t) {
    requires(HasExpression<T>);
    { t.mnemonic() } -> std::same_as<asm6502Parser::MnemonicContext*>;
    { t.shift() } -> std::same_as<asm6502Parser::ShiftContext*>;
};

using AsmLineBytes = std::variant<
    std::array<uint8_t, 0>,
    std::array<uint8_t, 1>,
    std::array<uint8_t, 2>,
    std::array<uint8_t, 3>,
    std::vector<uint8_t>
    >;

class AsmInstructionLine {
public:
    using ParseResult = Result<AsmInstructionLine, ParseError>;
    static auto make(
        asm6502Parser::LineContext* line,
        uint16_t pc,
        SymbolMap& symbol_map) -> ParseResult;

    static auto make_plain(
        asm6502Parser::InstructionContext* instruction_context,
        uint16_t pc,
        SymbolMap& symbol_map) -> ParseResult;

    auto evaluate(SymbolMap& symbol_map) -> std::optional<ParseError>;

    auto format() const -> std::string;
    auto serialize() const -> AsmLineBytes;

    auto program_counter() const -> uint16_t;
    auto size() const -> uint16_t;

protected:
    using BuilderResult = std::optional<ParseError>;
    using InstructionContext = asm6502Parser::InstructionContext;
    auto parse(
        InstructionContext* rule,
        uint16_t pc,
        SymbolMap& symbol_map) -> BuilderResult;

    auto parse_implicit(InstructionContext* rule, uint16_t pc) -> BuilderResult;
    auto parse_acc(InstructionContext* rule, uint16_t pc) -> BuilderResult;
    auto parse_immediate(InstructionContext* rule, uint16_t pc) -> BuilderResult;
    auto parse_zero_page(InstructionContext* rule, uint16_t pc) -> BuilderResult;
    auto parse_x_index(
        InstructionContext* rule,
        uint16_t pc,
        SymbolMap& symbol_map) -> BuilderResult;
    auto parse_y_index(
        InstructionContext* rule,
        uint16_t pc,
        SymbolMap& symbol_map) -> BuilderResult;
    auto parse_x_indirect(InstructionContext* rule, uint16_t pc) -> BuilderResult;
    auto parse_indirect_y(InstructionContext* rule, uint16_t pc) -> BuilderResult;
    auto parse_absolute(InstructionContext* rule, uint16_t pc) -> BuilderResult;
    auto parse_relative(InstructionContext* rule, uint16_t pc) -> BuilderResult;
    auto parse_jump(InstructionContext* rule, uint16_t pc) -> BuilderResult;
    auto parse_jsr(InstructionContext* rule, uint16_t pc) -> BuilderResult;

    struct OpInfo {
        OpName op_id;
        AddressMode address_mode;
        ArithmeticExpression expression;
    };

    template <typename IndexContext, typename ZpgMaker, typename AbsMaker>
    auto parse_indexed(
        IndexContext* index_context,
        uint16_t pc,
        SymbolMap& symbol_map,
        AddressMode zpg_mode,
        AddressMode abs_mode,
        ZpgMaker zpg_maker,
        AbsMaker abs_maker) -> BuilderResult
        requires(HasShiftAndMnemonic<IndexContext>)
    {
        if (index_context->FORCED_BYTE())
        {
            return parse_helper(zpg_maker, index_context, zpg_mode, pc);
        }
        if (index_context->FORCED_WORD())
        {
            return parse_helper(abs_maker, index_context, abs_mode, pc);
        }

        std::string name{};
        if (index_context->mnemonic())
        {
            name = index_context->mnemonic()->MNEMONIC()->getText();
        }
        else
        {
            name = index_context->shift()->SHIFT()->getText();
        }

        auto zpg_invalid_mnemonic = check_mnemonic(name, zpg_mode);
        auto abs_invalid_mnemonic = check_mnemonic(name, abs_mode);

        if (zpg_invalid_mnemonic.is_err() && abs_invalid_mnemonic.is_err())
        {
            return zpg_invalid_mnemonic.get_err();
        }

        auto arith_result = ArithmeticExpression::make(index_context->expression());
        if (arith_result.is_err())
        {
            return arith_result.get_err();
        }
        auto expression = arith_result.get_ok();
        if (zpg_invalid_mnemonic.is_ok())
        {
            auto res = expression.evaluate(symbol_map, 0);
            if (res.is_err() && res.get_err() != ParseError::SymbolUndefined)
            {
                return res.get_err();
            }
            else if (res.is_ok() && res.get_ok() < 0xFF)
            {
                auto op_id = zpg_invalid_mnemonic.get_ok();
                instruction = zpg_maker(pc, op_id, std::move(expression));
                return {};
            }
        }

        auto op_id = abs_invalid_mnemonic.get_ok();
        instruction = abs_maker(pc, op_id, std::move(expression));
        return {};
    }

    template <typename T, typename U>
    auto parse_helper(U obj_maker, T* context, AddressMode mode, uint16_t pc) -> BuilderResult
        requires(HasShiftAndMnemonic<T>)
    {
        std::string name{};
        if (context->mnemonic())
        {
            name = context->mnemonic()->MNEMONIC()->getText();
        }
        else
        {
            name = context->shift()->SHIFT()->getText();
        }

        auto invalid_mnemonic = check_mnemonic(name, mode);
        if (invalid_mnemonic.is_err())
        {
            return invalid_mnemonic.get_err();
        }
        auto op_id = invalid_mnemonic.get_ok();

        auto arith_result = ArithmeticExpression::make(context->expression());
        if (arith_result.is_err())
        {
            return arith_result.get_err();
        }
        auto expression = arith_result.get_ok();

        instruction = obj_maker(pc, op_id, std::move(expression));
        return {};
    }

    auto check_mnemonic(
        const std::string& name,
        AddressMode mode) -> Result<OpName, ParseError>;

private:
    InstructionLineMode instruction = {};
    std::optional<std::string> label = {};
    std::optional<std::string> comment = {};
};

} // namespace mos6502

#endif
