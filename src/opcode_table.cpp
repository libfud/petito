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
    if (address_type == AddressType::REL)
    {
        addr_data = pc + 2 + effective_address;
    }

    std::string meminfo;
    meminfo = "                   ";

    if (opcode != JMP_ABS && opcode != JSR_ABS)
    {
        switch (address_type)
        {
        case AddressType::ABS:
            meminfo = format("= {:02X}               ", data);
            break;
        case AddressType::ABS_X:
            meminfo = format("@ {:04X} = {:02X}        ", addr_data, data);
            break;
        case AddressType::ABS_Y:
            meminfo = format("@ {:04X} = {:02X}        ", addr_data, data);
            break;
        case AddressType::ZPG:
            meminfo = format("= {:02X}                   ", data);
            break;
        case AddressType::ZPG_X:
            meminfo = format("@ {:02X} = {:02X}            ", addr_data, data);
            break;
        case AddressType::ZPG_Y:
            meminfo = format("@ {:02X} = {:02X}            ", addr_data, data);
            break;
        case AddressType::IND:
            meminfo = format("= {:04X}             ", addr_data);
            break;
        case AddressType::X_IND:
            meminfo = format("@ {:02X} = {:04X} = {:02X}   ", (b1 + x) & 0xFF, addr_data, data);
            break;
        case AddressType::IND_Y:
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
    case AddressType::A:
        return format("{:02X}        {} A       {}", opcode, opid_to_name(op_info.name), meminfo);
    case AddressType::ABS:
        return format("{:02X} {:02X} {:02X}  {} ${:02X}{:02X} {}  ", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressType::ABS_X:
        return format("{:02X} {:02X} {:02X}  {} ${:02X}{:02X},X {}", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressType::ABS_Y:
        return format("{:02X} {:02X} {:02X}  {} ${:02X}{:02X},Y {}", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressType::IMM:
        return format("{:02X} {:02X}     {} #${:02X}    {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressType::IMPL:
        return format("{:02X}        {}         {}", opcode, opid_to_name(op_info.name), meminfo);
    case AddressType::IND:
        return format("{:02X} {:02X} {:02X}  {} (${:02X}{:02X}) {}", opcode, b1, b2, opid_to_name(op_info.name), b2, b1, meminfo);
    case AddressType::X_IND:
        return format("{:02X} {:02X}     {} (${:02X},X) {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressType::IND_Y:
        return format("{:02X} {:02X}     {} (${:02X}),Y {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressType::REL:
        return format("{:02X} {:02X}     {} ${:04X}   {}", opcode, b1, opid_to_name(op_info.name), addr_data, meminfo);
    case AddressType::ZPG:
        return format("{:02X} {:02X}     {} ${:02X} {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressType::ZPG_X:
        return format("{:02X} {:02X}     {} ${:02X},X {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    case AddressType::ZPG_Y:
        return format("{:02X} {:02X}     {} ${:02X},Y {}", opcode, b1, opid_to_name(op_info.name), b1, meminfo);
    default:
        return format("{:02X}        {} ILLEGAL {}", opcode, opid_to_name(op_info.name), meminfo);
    }
}

uint8_t address_mode_num_bytes(AddressType address_type)
{
    switch (address_type)
    {
    case AddressType::A:
        return 0;
    case AddressType::ABS:
        return 2;
    case AddressType::ABS_X:
        return 2;
    case AddressType::ABS_Y:
        return 2;
    case AddressType::IMM:
        return 1;
    case AddressType::IMPL:
        return 0;
    case AddressType::IND:
        return 2;
    case AddressType::X_IND:
        return 1;
    case AddressType::IND_Y:
        return 1;
    case AddressType::REL:
        return 1;
    case AddressType::ZPG:
        return 1;
    case AddressType::ZPG_X:
        return 1;
    case AddressType::ZPG_Y:
        return 1;
    default:
        return 0;
    }
}

}
