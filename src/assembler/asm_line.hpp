#ifndef ASM_LINE_HPP
#define ASM_LINE_HPP

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

/*
struct Symbol
{
    std::string name = {};
    ArithmeticExpression value = {};
};
*/

enum class LineType {
    Instruction,
    Comment,
    Label,
    Assign,
    Directive,
    Empty,
};

class InstructionLine {
public:
    constexpr InstructionLine() = default;
    constexpr InstructionLine(
        uint16_t pc,
        OpName op_id,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment);

    virtual ~InstructionLine() = default;
    virtual auto address_mode() const -> AddressMode = 0;
    constexpr auto format() const -> std::string;
    constexpr auto has_label() const -> bool;
    constexpr auto get_label() const -> const std::string&;
    constexpr auto size() const -> uint16_t;

    virtual auto evaluate(const SymbolMap&) -> std::optional<AsmError>;

protected:
    virtual constexpr auto format_instruction() const -> std::string = 0;
    uint16_t pc = {};
    OpName op_id = {};
    std::optional<std::string> label = {};
    std::optional<std::string> comment = {};
};

class NIModeInstructionLine : public InstructionLine
{
public:
    using InstructionLine::InstructionLine;
    constexpr auto address_mode() const  -> AddressMode override { return AddressMode::NI; }
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
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment,
        ArithmeticExpression&& expression);
protected:
    ArithmeticExpression expression = {};
};

template <class T>
auto instruction_line_wrapper(
    uint16_t pc,
    OpName op_id,
    std::optional<std::string>&& label,
    std::optional<std::string>&& comment,
    ArithmeticExpression&& expression) -> T
    requires(std::is_base_of<NOperandInstructionLine, T>::value)
{
    return T{pc, op_id, std::move(label), std::move(comment), std::move(expression)};
}

class OneOperandInstructionLine : public NOperandInstructionLine
{
public:
    using NOperandInstructionLine::NOperandInstructionLine;
    virtual ~OneOperandInstructionLine() = default;
    virtual auto evaluate(const SymbolMap& symbol_map) -> std::optional<AsmError> override;
protected:
    uint8_t operand = 0;
};

class TwoOperandInstructionLine : public NOperandInstructionLine
{
public:
    using NOperandInstructionLine::NOperandInstructionLine;
    virtual ~TwoOperandInstructionLine() = default;
    virtual auto evaluate(const SymbolMap& symbol_map) -> std::optional<AsmError> override;
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
    virtual auto evaluate(const SymbolMap& symbol_map) -> std::optional<AsmError> override;
protected:
    auto format_instruction() const -> std::string override
    {
        int8_t offset = static_cast<int8_t>(
            operand > 127 ? (-(256 - operand)) & 0xFF : operand & 0x7F);
        uint16_t new_pc = pc + offset;
        return std::format("{} ${:04X}", opid_to_name(op_id), new_pc);
    }
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

class AsmInstructionLine {
public:
    using ParseResult = Result<AsmInstructionLine, ParseError>;
    static auto make(asm6502Parser::LineContext* line, uint16_t pc) -> ParseResult;

    auto complete_decode(SymbolMap& symbol_map) -> std::optional<ParseError>;

    auto has_label() const -> bool;
    auto get_label() const -> const std::string&;
    constexpr auto size() const -> uint16_t;

protected:
    using BuilderResult = std::optional<ParseError>;
    using InstructionContext = asm6502Parser::InstructionContext;
    auto parse(
        InstructionContext* rule,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult;
#define DEF_PARSE_RULE(M_RULE_NAME) \
    auto M_RULE_NAME( \
        InstructionContext* rule, \
        uint16_t pc, \
        std::optional<std::string>&& label, \
        std::optional<std::string>&& comment) -> BuilderResult
    DEF_PARSE_RULE(parse_implicit);
    DEF_PARSE_RULE(parse_acc);
    DEF_PARSE_RULE(parse_immediate);
    DEF_PARSE_RULE(parse_x_index);
    DEF_PARSE_RULE(parse_y_index);
    DEF_PARSE_RULE(parse_x_indirect);
    DEF_PARSE_RULE(parse_indirect_y);
    DEF_PARSE_RULE(parse_absolute);
    DEF_PARSE_RULE(parse_relative);
    DEF_PARSE_RULE(parse_jump);
    DEF_PARSE_RULE(parse_jsr);
#undef DEF_PARSE_RULE

    struct OpInfo {
        OpName op_id;
        AddressMode address_mode;
        ArithmeticExpression expression;
    };

    template <typename T, typename U>
    auto parse_helper(
        U obj_maker,
        T* context,
        AddressMode mode,
        uint16_t pc,
        std::optional<std::string>&& label,
        std::optional<std::string>&& comment) -> BuilderResult
        requires(HasShiftAndMnemonic<T>)
    {
        std::string name;
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

        instruction = obj_maker(
            pc, op_id, std::move(label), std::move(comment), std::move(expression));
        return {};
    }

    auto parse_xy_index(
        InstructionContext* rule,
        AddressMode zpg_mode,
        AddressMode abs_mode) -> Result<OpInfo, ParseError>;

    auto check_mnemonic(
        const std::string& name,
        AddressMode mode) -> Result<OpName, ParseError>;

private:
    InstructionLineMode instruction = {};
};

struct LabelLine {
    auto format() const -> std::string;
    std::string label;
    uint16_t pc;
    std::optional<std::string> comment;
};

class Line {
public:
    using LineResult = Result<Line, AsmError>;
    using BuilderResult = std::optional<ParseError>;
    static auto make(asm6502Parser::LineContext* line) -> LineResult;
    auto has_label() const -> bool;
    auto get_label() const -> const std::string&;
    auto size() const -> uint16_t;
    auto complete_decode(SymbolMap& symbol_map, uint16_t pc) -> std::optional<AsmError>;
    auto format() const -> std::string;
    auto instruction_format() const -> std::string;

private:
    using InstructionContext = asm6502Parser::InstructionContext;
    using ImmediateContext = asm6502Parser::ImmediateContext;
    using XIndexContext = asm6502Parser::X_indexContext;
    using YIndexContext = asm6502Parser::Y_indexContext;
    using RelativeContext = asm6502Parser::RelativeContext;
    using JumpContext = asm6502Parser::JumpContext;
    using JsrContext = asm6502Parser::JsrContext;

    auto handle_instruction_rule(InstructionContext* rule) -> BuilderResult;
    auto handle_immediate_rule(ImmediateContext* rule) -> BuilderResult;
    auto handle_x_index_rule(XIndexContext* rule) -> BuilderResult;
    auto handle_y_index_rule(YIndexContext* rule) -> BuilderResult;
    auto handle_relative_rule(RelativeContext* rule) -> BuilderResult;
    auto handle_jump_rule(JumpContext* rule) -> BuilderResult;
    auto handle_jsr_rule(JsrContext* rule) -> BuilderResult;
    auto check_mnemonic(const std::string& name, AddressMode mode) -> BuilderResult;
    template <typename T>
    auto helper(T* rule, AddressMode mode) -> BuilderResult
        requires(HasShiftAndMnemonic<T>)
    {
        std::string name;
        if (rule->mnemonic())
        {
            name = rule->mnemonic()->MNEMONIC()->getText();
        }
        else
        {
            name = rule->shift()->SHIFT()->getText();
        }

        auto invalid_mnemonic = check_mnemonic(name, mode);

        if (invalid_mnemonic != std::nullopt)
        {
            std::cout << "Invalid mnemonic!\n";
            return invalid_mnemonic;
        }

        auto arith_result = handle_arithmetic(rule);
        if (arith_result != std::nullopt)
        {
            std::cout << "Invalid arithmetic!\n";
            return arith_result;
        }

        return {};
    }

    template <typename T>
    auto handle_arithmetic(T* parent_context) -> BuilderResult
        requires(HasExpression<T>)
    {
        auto* context = parent_context->expression();
        auto result = ArithmeticExpression::make(context);
        if (result.is_ok())
        {
            arithmetic_expression = result.get_ok();
            return {};
        }
        std::cerr << "Error: " << context->getText() << "\n";
        return result.get_err();
    }

    std::optional<std::string> label = {};
    std::optional<std::string> comment = {};
    std::optional<OpName> op_id = {};
    std::optional<AddressMode> address_mode = {};
    std::optional<ArithmeticExpression> arithmetic_expression = {};
    std::vector<uint8_t> operands = {};
    std::optional<std::string> symbol = {};
    std::optional<uint16_t> symbol_value = {};
    LineType line_type = LineType::Empty;
    bool complete = false;
};

} // namespace mos6502

#endif
