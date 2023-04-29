#include "opcode_table.hpp"

#include <format>

namespace mos6502 {

const std::string& opid_to_name(OpName opid)
{
    return OP_NAMES[static_cast<uint8_t>(opid)];
}

std::string OpDecode::instr_fmt(uint8_t opcode, uint8_t x, uint8_t y, uint16_t pc) const
{
    OpcodeInfo op_info = OPCODE_INFO_TABLE[opcode];
    auto address_type = op_info.address_type;
    auto addr_data = effective_address;
    if (address_type == AddressMode::REL)
    {
        addr_data = pc + 2 + effective_address;
    }

    std::string meminfo;
    meminfo = "                   ";

    if (opcode != JMP_ABS && opcode != JSR_ABS)
    {
        switch (address_type)
        {
        case AddressMode::ABS:
            meminfo = std::format("= {:02X}               ", data);
            break;
        case AddressMode::ABS_X:
            meminfo = std::format("@ {:04X} = {:02X}        ", addr_data, data);
            break;
        case AddressMode::ABS_Y:
            meminfo = std::format("@ {:04X} = {:02X}        ", addr_data, data);
            break;
        case AddressMode::ZPG:
            meminfo = std::format("= {:02X}                   ", data);
            break;
        case AddressMode::ZPG_X:
            meminfo = std::format("@ {:02X} = {:02X}            ", addr_data, data);
            break;
        case AddressMode::ZPG_Y:
            meminfo = std::format("@ {:02X} = {:02X}            ", addr_data, data);
            break;
        case AddressMode::IND:
            meminfo = std::format("= {:04X}             ", addr_data);
            break;
        case AddressMode::X_IND:
            meminfo = std::format("@ {:02X} = {:04X} = {:02X}   ", (b1 + x) & 0xFF, addr_data, data);
            break;
        case AddressMode::IND_Y:
            meminfo = std::format(
                "= {:04X} @ {:04X} = {:02X} ",
                static_cast<uint16_t>(addr_data - y), addr_data, data);
            break;
        default:
            break;
        }
    }

    switch (address_type)
    {
    case AddressMode::A:
        return std::format("{:02X}        {} A       {}", opcode, opid_to_name(op_info.name), meminfo);
    case AddressMode::ABS:
        return std::format("{:02X} {:02X} {:02X}  {} ${:02X}{:02X} {}  ", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressMode::ABS_X:
        return std::format("{:02X} {:02X} {:02X}  {} ${:02X}{:02X},X {}", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressMode::ABS_Y:
        return std::format("{:02X} {:02X} {:02X}  {} ${:02X}{:02X},Y {}", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressMode::IMM:
        return std::format("{:02X} {:02X}     {} #${:02X}    {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::IMPL:
        return std::format("{:02X}        {}         {}", opcode, opid_to_name(op_info.name), meminfo);
    case AddressMode::IND:
        return std::format("{:02X} {:02X} {:02X}  {} (${:02X}{:02X}) {}", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressMode::X_IND:
        return std::format("{:02X} {:02X}     {} (${:02X},X) {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::IND_Y:
        return std::format("{:02X} {:02X}     {} (${:02X}),Y {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::REL:
        return std::format("{:02X} {:02X}     {} ${:04X}   {}", opcode, b1, opid_to_name(op_info.name), addr_data, meminfo);
    case AddressMode::ZPG:
        return std::format("{:02X} {:02X}     {} ${:02X} {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::ZPG_X:
        return std::format("{:02X} {:02X}     {} ${:02X},X {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::ZPG_Y:
        return std::format("{:02X} {:02X}     {} ${:02X},Y {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    default:
        return std::format("{:02X}        {} ILLEGAL {}", opcode, opid_to_name(op_info.name), meminfo);
    }
}

} // namespace mos6502
