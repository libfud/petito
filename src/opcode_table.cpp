#include "opcode_table.hpp"

namespace mos6502 {

using fmt::format;

std::string opid_to_name(OpName opid)
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
            meminfo = format("= {:02X}               ", data);
            break;
        case AddressMode::ABS_X:
            meminfo = format("@ {:04X} = {:02X}        ", addr_data, data);
            break;
        case AddressMode::ABS_Y:
            meminfo = format("@ {:04X} = {:02X}        ", addr_data, data);
            break;
        case AddressMode::ZPG:
            meminfo = format("= {:02X}                   ", data);
            break;
        case AddressMode::ZPG_X:
            meminfo = format("@ {:02X} = {:02X}            ", addr_data, data);
            break;
        case AddressMode::ZPG_Y:
            meminfo = format("@ {:02X} = {:02X}            ", addr_data, data);
            break;
        case AddressMode::IND:
            meminfo = format("= {:04X}             ", addr_data);
            break;
        case AddressMode::X_IND:
            meminfo = format("@ {:02X} = {:04X} = {:02X}   ", (b1 + x) & 0xFF, addr_data, data);
            break;
        case AddressMode::IND_Y:
            meminfo = format(
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
        return format("{:02X}        {} A       {}", opcode, opid_to_name(op_info.name), meminfo);
    case AddressMode::ABS:
        return format("{:02X} {:02X} {:02X}  {} ${:02X}{:02X} {}  ", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressMode::ABS_X:
        return format("{:02X} {:02X} {:02X}  {} ${:02X}{:02X},X {}", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressMode::ABS_Y:
        return format("{:02X} {:02X} {:02X}  {} ${:02X}{:02X},Y {}", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressMode::IMM:
        return format("{:02X} {:02X}     {} #${:02X}    {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::IMPL:
        return format("{:02X}        {}         {}", opcode, opid_to_name(op_info.name), meminfo);
    case AddressMode::IND:
        return format("{:02X} {:02X} {:02X}  {} (${:02X}{:02X}) {}", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressMode::X_IND:
        return format("{:02X} {:02X}     {} (${:02X},X) {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::IND_Y:
        return format("{:02X} {:02X}     {} (${:02X}),Y {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::REL:
        return format("{:02X} {:02X}     {} ${:04X}   {}", opcode, b1, opid_to_name(op_info.name), addr_data, meminfo);
    case AddressMode::ZPG:
        return format("{:02X} {:02X}     {} ${:02X} {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::ZPG_X:
        return format("{:02X} {:02X}     {} ${:02X},X {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressMode::ZPG_Y:
        return format("{:02X} {:02X}     {} ${:02X},Y {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    default:
        return format("{:02X}        {} ILLEGAL {}", opcode, opid_to_name(op_info.name), meminfo);
    }
}

uint8_t address_mode_num_bytes(AddressMode address_type)
{
    switch (address_type)
    {
    case AddressMode::A:
        return 0;
    case AddressMode::ABS:
        return 2;
    case AddressMode::ABS_X:
        return 2;
    case AddressMode::ABS_Y:
        return 2;
    case AddressMode::IMM:
        return 1;
    case AddressMode::IMPL:
        return 0;
    case AddressMode::IND:
        return 2;
    case AddressMode::X_IND:
        return 1;
    case AddressMode::IND_Y:
        return 1;
    case AddressMode::REL:
        return 1;
    case AddressMode::ZPG:
        return 1;
    case AddressMode::ZPG_X:
        return 1;
    case AddressMode::ZPG_Y:
        return 1;
    default:
        return 0;
    }
}

}
