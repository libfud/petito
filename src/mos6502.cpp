#include <chrono>
#include <thread>

#include <fmt/core.h>
#include <fmt/format.h>

#include "mos6502.hpp"
#include "logger/logger.hpp"
#include "nes.hpp"
#include "cartridge/cartridge.hpp"
#include "opcode_table.hpp"

namespace mos6502 {

uint8_t Flags::get()
{
    return
        (static_cast<uint8_t>(negative) << 7) |
        (static_cast<uint8_t>(overflow) << 6) |
        (1 << 5) |
        (static_cast<uint8_t>(brk) << 4) |
        (static_cast<uint8_t>(bcd_arithmetic) << 3) |
        (static_cast<uint8_t>(interrupt_inhibit) << 2) |
        (static_cast<uint8_t>(zero) << 1) |
        static_cast<uint8_t>(carry);
}

uint8_t Flags::get_fmt()
{
    return
        (static_cast<uint8_t>(negative) << 7) |
        (static_cast<uint8_t>(overflow) << 6) |
        (static_cast<uint8_t>(bcd_arithmetic) << 3) |
        (static_cast<uint8_t>(interrupt_inhibit) << 2) |
        (static_cast<uint8_t>(zero) << 1) |
        static_cast<uint8_t>(carry);
}

uint8_t Flags::get_php()
{
    uint8_t flags = get();
    flags |= (1 << 5) | (1 << 4);
    return flags;
}

uint16_t Flags::get_carry()
{
    uint16_t c = 0;
    if (carry)
    {
        c = 0x0100;
    }
    return c;
}

void Flags::set(uint8_t data)
{
    carry = (data & 0x01) == 1;
    zero = ((data >> 1) & 0x01) == 1;
    interrupt_inhibit = ((data >> 2) & 0x01) == 1;
    bcd_arithmetic = ((data >> 3) & 0x01) == 1;
    overflow = ((data >> 6) & 0x01) == 1;
    negative = ((data >> 7) & 0x01) == 1;
}

void Flags::set_n_and_z(uint8_t data)
{
    zero = data == 0;
    negative = data >> 7;
}

MOS6502::MOS6502(int32_t cpu_clock_rate) :
    flags(),
    pc(RESET_VECTOR),
    acc(0),
    x(0),
    y(0),
    stack_ptr(0x00),
    clock_rate(cpu_clock_rate),
    clock_counter(0),
    irq_signal(false),
    memory(nullptr),
    diagnostics(true),
    heavy_diagnostics(false)
{
    flags.set(0x34);
}

void MOS6502::set_memory(Memory* external_memory)
{
    memory = external_memory;
}

uint8_t MOS6502::read(uint16_t address)
{
    return memory->read(address);
}

void MOS6502::write(uint16_t address, uint8_t data)
{
    memory->write(address, data);
    if ((address == 0x4010 && (data & 0x80)) ||
        (address == 0x4017 && !(data & 0xC0)))
    {
        if (!flags.interrupt_inhibit)
        {
            irq_signal = true;
        }
    }
}

void MOS6502::load_reg(uint8_t& reg, uint8_t data)
{
    reg = data;
    flags.set_n_and_z(reg);
}

void MOS6502::push(uint8_t data)
{
    write(0x100 | stack_ptr, data);
    stack_ptr -= 1;
}

void MOS6502::push_pc()
{
    push(static_cast<uint8_t>(pc >> 8));
    push(static_cast<uint8_t>(pc & 0xFF));
}

uint8_t MOS6502::pull()
{
    stack_ptr += 1;
    uint8_t data = read(0x100 | stack_ptr);
    return data;
}

void MOS6502::pull_pc()
{
    uint8_t addr_low = pull();
    uint8_t addr_high = pull();
    pc = make_address(addr_low, addr_high);
}

uint16_t MOS6502::make_address(uint8_t addr_low, uint8_t addr_high) const
{
    return (static_cast<uint16_t>(addr_high) << 8) | addr_low;
}

uint16_t MOS6502::absolute(uint8_t addr_low, uint8_t addr_high) const
{
    return make_address(addr_low, addr_high);
}

uint16_t MOS6502::absolute_idx(uint8_t addr_low, uint8_t addr_high, uint8_t idx)
{
    uint16_t new_addr = ((static_cast<uint16_t>(addr_high) << 8) | addr_low) + idx;
    clock_counter += ((new_addr >> 8) - addr_high) & 0x01;
    return new_addr;
}

uint8_t MOS6502::zero_page_x(uint8_t addr_low) const { return addr_low + x; }

uint8_t MOS6502::zero_page_y(uint8_t addr_low) const { return addr_low + y; }

uint16_t MOS6502::indirect(uint8_t addr_low, uint8_t addr_high)
{
    uint16_t indirect_addr = make_address(addr_low, addr_high);
    uint8_t new_addr_low = read(indirect_addr);
    uint8_t new_addr_high = read((indirect_addr & 0xFF00) | ((indirect_addr + 1) & 0x0FF));
    return make_address(new_addr_low, new_addr_high);
}

uint16_t MOS6502::x_indirect(uint8_t offset)
{
    uint8_t target_addr_1 = x + offset;
    uint8_t target_addr_2 = target_addr_1 + 1;
    uint8_t addr_low = read(target_addr_1);
    uint8_t addr_high = read(target_addr_2);
    return make_address(addr_low, addr_high);
}

uint16_t MOS6502::indirect_y(uint8_t offset)
{
    uint8_t addr_low = read(offset);
    uint8_t addr_high = read(static_cast<uint8_t>(offset + 1));
    uint16_t new_addr = make_address(addr_low, addr_high) + static_cast<uint16_t>(y);
    clock_counter += ((new_addr >> 8) - addr_high) & 0x01;
    return new_addr;
}

uint16_t MOS6502::rel_addr(uint8_t offset)
{
    int8_t relative_address = *reinterpret_cast<int8_t*>(&offset);
    uint16_t effective_address = pc + 2 + relative_address;
    clock_counter += 1 + (((effective_address - pc) & 0x100) >> 8);
    return relative_address;
}

void MOS6502::branch(uint16_t relative_address, bool flag)
{
    uint16_t effective_address = pc + relative_address * flag;
    pc = effective_address;
}

void MOS6502::compare(uint8_t reg, uint8_t value)
{
    uint8_t diff = reg - value;
    flags.set_n_and_z(diff);
    flags.carry = reg >= value;
}

void MOS6502::adc(uint8_t value)
{
    uint16_t sum = acc + value + flags.carry;
    uint8_t new_acc = sum & 0xFF;
    flags.set_n_and_z(new_acc);
    flags.overflow = ((acc ^ new_acc) & (value ^ new_acc) & 0x80) != 0;
    flags.carry = sum & 0x100;
    acc = new_acc;
}

void MOS6502::arr(uint8_t value)
{
    and_op(value);
    bool overflow = static_cast<bool>(acc & 0x40) != static_cast<bool>(acc & 0x80);
    bool carry = acc & 0x80;
    ror(acc);
    flags.overflow = overflow;
    flags.carry = carry;
}

void MOS6502::sbc(uint8_t value)
{
    uint16_t diff = acc - value - !flags.carry;
    uint8_t new_acc = diff & 0xFF;
    flags.set_n_and_z(new_acc);
    flags.overflow = (acc ^ diff) & (~value ^ diff) & 0x80;
    flags.carry = !(diff & 0x100);
    acc = new_acc;
}

void MOS6502::decrement(uint8_t& value)
{
    value--;
    flags.set_n_and_z(value);
}

void MOS6502::increment(uint8_t& value)
{
    value++;
    flags.set_n_and_z(value);
}

void MOS6502::and_op(uint8_t value)
{
    acc &= value;
    flags.set_n_and_z(acc);
}

void MOS6502::asl(uint8_t& value)
{
    uint16_t new_value = static_cast<uint16_t>(value) << 1;
    flags.set_n_and_z(static_cast<uint8_t>(new_value & 0xFF));
    flags.carry = new_value >> 8;
    value = new_value;
}

void MOS6502::bit_test(uint8_t value)
{
    flags.negative = value >> 7 == 0x01;
    flags.overflow = (value >> 6) & 0x01;
    value &= acc;
    flags.zero = value == 0;
}

void MOS6502::eor(uint8_t value)
{
    acc ^= value;
    flags.set_n_and_z(acc);
}

void MOS6502::lsr(uint8_t& value)
{
    uint8_t new_value = value >> 1;
    flags.carry = value & 0x01;
    flags.negative = false;
    flags.zero = new_value == 0;
    value = new_value;
}

void MOS6502::ora(uint8_t value)
{
    acc |= value;
    flags.set_n_and_z(acc);
}

void MOS6502::rol(uint8_t& value)
{
    uint16_t compound_value = (value << 1) | flags.carry;
    flags.carry = value >> 7;
    value = compound_value;
    flags.set_n_and_z(value);
}

void MOS6502::ror(uint8_t& value)
{
    uint16_t compound_value = (flags.carry << 7) | (value >> 1);
    flags.carry = value & 0x01;
    value = compound_value;
    flags.set_n_and_z(compound_value);
}

CpuData MOS6502::save_state()
{
    return {flags, pc, acc, x, y, stack_ptr, clock_counter};
}

OpDecode MOS6502::decode(uint8_t opcode)
{
    OpDecode op_decode{
        .op_info = OPCODE_INFO_TABLE[opcode],
        .effective_address = 0,
        .data = 0,
        .b1 = 0,
        .b2 = 0,
        .read_bytes = 0
    };

    const auto& address_type = op_decode.op_info.address_type;
    op_decode.read_bytes = address_mode_num_bytes(address_type);

    switch (op_decode.read_bytes)
    {
    case 2:
        op_decode.b2 = read(pc + 2);
    case 1:
        op_decode.b1 = read(pc + 1);
    case 0:
        break;
    default:
        throw std::runtime_error("invalid number of bytes to read");
    }

    switch (address_type)
    {
    case AddressType::A:
    case AddressType::IMM:
    case AddressType::IMPL:
        break;
    case AddressType::ABS:
        op_decode.effective_address = absolute(op_decode.b1, op_decode.b2);
        op_decode.data = read(op_decode.effective_address);
        break;
    case AddressType::ABS_X:
        op_decode.effective_address = absolute_idx(op_decode.b1, op_decode.b2, x);
        op_decode.data = read(op_decode.effective_address);
        break;
    case AddressType::ABS_Y:
        op_decode.effective_address = absolute_idx(op_decode.b1, op_decode.b2, y);
        op_decode.data = read(op_decode.effective_address);
        break;
    case AddressType::IND:
        op_decode.effective_address = indirect(op_decode.b1, op_decode.b2);
        op_decode.data = read(op_decode.effective_address);
        break;
    case AddressType::X_IND:
        op_decode.effective_address = x_indirect(op_decode.b1);
        op_decode.data = read(op_decode.effective_address);
        break;
    case AddressType::IND_Y:
        op_decode.effective_address = indirect_y(op_decode.b1);
        op_decode.data = read(op_decode.effective_address);
        break;
    case AddressType::REL:
        op_decode.effective_address = rel_addr(op_decode.b1);
        break;
    case AddressType::ZPG:
        op_decode.effective_address = op_decode.b1;
        op_decode.data = read(op_decode.effective_address);
        break;
    case AddressType::ZPG_X:
        op_decode.effective_address = zero_page_x(op_decode.b1);
        op_decode.data = read(op_decode.effective_address);
        break;
    case AddressType::ZPG_Y:
        op_decode.effective_address = zero_page_y(op_decode.b1);
        op_decode.data = read(op_decode.effective_address);
        break;
    default:
        logger::log(logger::LogLevel::Critical, "Invalid addressing mode PC={:04X} opcode={:02X} {}",
                    pc, opcode, static_cast<uint8_t>(address_type));
        throw std::runtime_error("Invalid addressing mode");
    }

    return op_decode;
}

void MOS6502::step_diagnostics(uint8_t opcode, OpDecode& op_decode)
{
    uint8_t status = read(0x6000);

    if (heavy_diagnostics)
    {
        logger::log(
            logger::LogLevel::Debug,
            "{:04X}  {} A:{:02X} X:{:02X} Y:{:02X} P:{:02X} SP:{:02X} CYC:{:>3}",
            pc, op_decode.instr_fmt(opcode, x, y, pc),
            acc, x, y, flags.get(), stack_ptr,
            static_cast<unsigned int>(clock_counter % 1000)//,
        );
    }
    if (status == 0x80)
    {
        std::string message{reinterpret_cast<const char*>(
                &(dynamic_cast<nes::NesMemory*>(memory)->get_cart().prg_ram[4]))};
        if (message.size() > 6)
        {
            logger::log(
                logger::LogLevel::Warn,
                "Test in progress {:02X} {:02X} {:02X}\nmessage={}",
                dynamic_cast<nes::NesMemory*>(memory)->get_cart().prg_ram[1],
                dynamic_cast<nes::NesMemory*>(memory)->get_cart().prg_ram[2],
                dynamic_cast<nes::NesMemory*>(memory)->get_cart().prg_ram[3],
                message
            );
        }
    }
}

void MOS6502::step()
{
    uint8_t opcode = read(pc);

    OpDecode op_decode = decode(opcode);

    if (diagnostics)
    {
        step_diagnostics(opcode, op_decode);
    }

    // std::this_thread::sleep_for(std::chrono::milliseconds(0));

    bool update_pc = true;
    /*
     * 11.82%  $A5 LDA zero-page
     * 10.37%  $D0 BNE
     * 7.33%  $4C JMP absolute
     * 6.97%  $E8 INX
     * 4.46%  $10 BPL
     * 3.82%  $C9 CMP immediate
     * 3.49%  $30 BMI
     * 3.32%  $F0 BEQ
     * 3.32%  $24 BIT zero-page
     * 2.94%  $85 STA zero-page
     * 2.00%  $88 DEX
     * 1.98%  $C8 INY
     * 1.77%  $A8 TAY
     * 1.74%  $E6 INC zero-page
     * 1.74%  $B0 BCS
     * 1.66%  $BD LDA absolute,X
     * 1.64%  $B5 LDA zero-page,X
     * 1.51%  $AD LDA absolute
     * 1.41%  $20 JSR absolute
     * 1.38%  $4A LSR A
     * 1.37%  $60 RTS
     * 1.35%  $B1 LDA (zero-page),Y
     * 1.32%  $29 AND immediate
     * 1.27%  $9D STA absolute,X
     * 1.24%  $8D STA absolute
     * 1.08%  $18 CLC
     * 1.03%  $A9 LDA immediate
     */
    switch (opcode)
    {
    case LDA_ZPG:
    case LDA_X_IND:
    case LDA_ABS:
    case LDA_IND_Y:
    case LDA_ZPG_X:
    case LDA_ABS_Y:
    case LDA_ABS_X:
        load_reg(acc, op_decode.data);
        break;

    case BNE_REL:
        branch(op_decode.effective_address, !flags.zero);
        break;

    case JMP_ABS:
        update_pc = false;
        pc = op_decode.effective_address;
        break;

    case INX_IMPL:
        increment(x);
        break;

    case BPL_REL:
        branch(op_decode.effective_address, !flags.negative);
        break;

    case CMP_IMM:
        compare(acc, op_decode.b1);
        break;

    case BMI_REL:
        branch(op_decode.effective_address, flags.negative);
        break;

    case BEQ_REL:
        branch(op_decode.effective_address, flags.zero);
        break;

    case BIT_ZPG:
    case BIT_ABS:
        bit_test(op_decode.data);
        break;

    case STA_X_IND:
    case STA_ZPG:
    case STA_ABS:
    case STA_IND_Y:
    case STA_ZPG_X:
    case STA_ABS_Y:
    case STA_ABS_X:
        write(op_decode.effective_address, acc);
        break;

    case DEX_IMPL:
        decrement(x);
        break;

    case INY_IMPL:
        increment(y);
        break;

    case TAY_IMPL:
        y = acc;
        flags.set_n_and_z(y);
        break;

    case INC_ZPG:
    case INC_ABS:
    case INC_ZPG_X:
    case INC_ABS_X:
        increment(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case BCS_REL:
        branch(op_decode.effective_address, flags.carry);
        break;

    case JSR_ABS:
        update_pc = false;
        pc += 2;
        push_pc();
        pc = op_decode.effective_address;
        break;

    case LSR_A:
        lsr(acc);
        break;

    case RTS_IMPL:
        pull_pc();
        break;

    case AND_IMM:
        and_op(op_decode.b1);
        break;

    case CLC_IMPL:
        flags.carry = false;
        break;

    case BRK_IMPL:
        update_pc = false;
        flags.brk = true;
        break;

    case ORA_X_IND:
    case ORA_ZPG:
    case ORA_ABS:
    case ORA_IND_Y:
    case ORA_ZPG_X:
    case ORA_ABS_Y:
    case ORA_ABS_X:
        ora(op_decode.data);
        break;

    case ASL_ZPG:
    case ASL_ABS:
    case ASL_ZPG_X:
    case ASL_ABS_X:
        asl(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case PHP_IMPL:
        push(flags.get_php());
        break;

    case ORA_IMM:
        ora(op_decode.b1);
        break;

    case ASL_A:
        asl(acc);
        break;

    case AND_X_IND:
    case AND_ZPG:
    case AND_ABS:
    case AND_IND_Y:
    case AND_ZPG_X:
    case AND_ABS_Y:
    case AND_ABS_X:
        and_op(op_decode.data);
        break;

    case ROL_ZPG:
    case ROL_ABS:
    case ROL_ZPG_X:
    case ROL_ABS_X:
        rol(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case PLP_IMPL:
        op_decode.data = pull();
        flags.set(op_decode.data);
        break;

    case ROL_A:
        rol(acc);
        break;

    case SEC_IMPL:
        flags.carry = true;
        break;

    case RTI_IMPL:
        update_pc = false;
        op_decode.data = pull();
        flags.set(op_decode.data);
        pull_pc();
        break;

    case EOR_X_IND:
    case EOR_ZPG:
    case EOR_ABS:
        eor(read(op_decode.effective_address));
        break;

    case LSR_ZPG:
    case LSR_ABS:
    case LSR_ZPG_X:
    case LSR_ABS_X:
        lsr(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case PHA_IMPL:
        push(acc);
        break;

    case EOR_IMM:
        eor(op_decode.b1);
        break;

    case BVC_REL:
        branch(op_decode.effective_address, !flags.overflow);
        break;

    case EOR_IND_Y:
    case EOR_ZPG_X:
    case EOR_ABS_Y:
    case EOR_ABS_X:
        eor(op_decode.data);
        break;

    case CLI_IMPL:
        flags.interrupt_inhibit = false;
        break;

    case ADC_X_IND:
    case ADC_ZPG:
    case ADC_ABS:
    case ADC_IND_Y:
    case ADC_ZPG_X:
    case ADC_ABS_Y:
    case ADC_ABS_X:
        adc(op_decode.data);
        break;

    case ROR_ZPG:
    case ROR_ABS:
    case ROR_ZPG_X:
    case ROR_ABS_X:
        ror(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case PLA_IMPL:
        acc = pull();
        flags.set_n_and_z(acc);
        break;

    case ADC_IMM:
        adc(op_decode.b1);
        break;

    case ROR_A:
        ror(acc);
        break;

    case JMP_IND:
        update_pc = false;
        pc = op_decode.effective_address;
        break;

    case BVS_REL:
        branch(op_decode.effective_address, flags.overflow);
        break;

    case SEI_IMPL:
        flags.interrupt_inhibit = true;
        break;

    case STY_ZPG:
    case STY_ABS:
    case STY_ZPG_X:
        write(op_decode.effective_address, y);
        break;

    case STX_ZPG:
    case STX_ABS:
    case STX_ZPG_Y:
        write(op_decode.effective_address, x);
        break;

    case DEY_IMPL:
        decrement(y);
        break;

    case TXA_IMPL:
        acc = x;
        flags.set_n_and_z(acc);
        break;

    case BCC_REL:
        branch(op_decode.effective_address, !flags.carry);
        break;

    case LDX_IMM:
        load_reg(x, op_decode.b1);
        break;

    case TYA_IMPL:
        acc = y;
        flags.set_n_and_z(acc);
        break;

    case TXS_IMPL:
        stack_ptr = x;
        break;

    case LDY_IMM:
        load_reg(y, op_decode.b1);
        break;

    case LDY_ZPG:
    case LDY_ABS:
    case LDY_ZPG_X:
    case LDY_ABS_X:
        load_reg(y, op_decode.data);
        break;

    case LDX_ZPG:
    case LDX_ABS:
    case LDX_ZPG_Y:
    case LDX_ABS_Y:
        load_reg(x, op_decode.data);
        break;

    case LDA_IMM:
        load_reg(acc, op_decode.b1);
        break;

    case TAX_IMPL:
        x = acc;
        flags.set_n_and_z(x);
        break;

    case CLV_IMPL:
        flags.overflow = false;
        break;

    case TSX_IMPL:
        x = stack_ptr;
        flags.set_n_and_z(x);
        break;

    case CPY_IMM:
        compare(y, op_decode.b1);
        break;

    case CMP_X_IND:
    case CMP_ZPG:
    case CMP_ABS:
    case CMP_IND_Y:
    case CMP_ZPG_X:
    case CMP_ABS_Y:
    case CMP_ABS_X:
        compare(acc, op_decode.data);
        break;

    case CPY_ZPG:
    case CPY_ABS:
        compare(y, op_decode.data);
        break;

    case DEC_ZPG:
    case DEC_ABS:
    case DEC_ZPG_X:
    case DEC_ABS_X:
        decrement(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case CLD_IMPL:
        flags.bcd_arithmetic = false;
        break;

    case CPX_IMM:
        compare(x, op_decode.b1);
        break;

    case SBC_X_IND:
    case SBC_ZPG:
    case SBC_ABS:
    case SBC_IND_Y:
    case SBC_ZPG_X:
    case SBC_ABS_Y:
    case SBC_ABS_X:
        sbc(op_decode.data);
        break;

    case CPX_ZPG:
    case CPX_ABS:
        compare(x, op_decode.data);
        break;

    case SBC_IMM:
        sbc(op_decode.b1);
        break;

    case SED_IMPL:
        flags.bcd_arithmetic = true;
        break;

    case NOP_IMPL:
    case NOP_IMM_1:
    case NOP_IMM_2:
    case NOP_IMM_3:
    case NOP_IMM_4:
    case NOP_IMM_5:
    case NOP_ZPG_0:
    case NOP_ZPX_1:
    case NOP_ZPX_3:
    case NOP_ZPG_4:
    case NOP_ZPG_5:
    case NOP_ZPG_6:
    case NOP_ZPX_7:
    case NOP_ZPX_D:
    case NOP_ZPX_F:
    case NOP_ABS_0:
    case NOP_ABSX1:
    case NOP_ABSX3:
    case NOP_ABSX5:
    case NOP_ABSX7:
    case NOP_ABSXD:
    case NOP_ABSXF:
    case NOP_IMPL1:
    case NOP_IMPL3:
    case NOP_IMPL5:
    case NOP_IMPL7:
    case NOP_IMPLD:
    case NOP_IMPLF:
        break;

    case LAX_ZPG:
    case LAX_ZPG_Y:
    case LAX_ABS:
    case LAX_ABS_Y:
    case LAX_X_IND:
    case LAX_IND_Y:
        acc = op_decode.data;
        x = op_decode.data;
        flags.set_n_and_z(x);
        break;

    case LXA_IMM:
        ora(0xFF);
        and_op(op_decode.b1);
        x = acc;
        break;

    case SAX_ZPG:
    case SAX_ZPG_Y:
    case SAX_ABS:
    case SAX_X_IND:
        op_decode.data = acc & x;
        write(op_decode.effective_address, op_decode.data);
        break;

    case SBX_IMM:
        compare(acc & x, op_decode.b1);
        x = (acc & x) - op_decode.b1;
        break;

    case USBC_IMM:
        sbc(op_decode.b1);
        break;

    case DCP_ZPG:
    case DCP_ZPG_X:
    case DCP_ABS:
    case DCP_ABS_X:
    case DCP_ABS_Y:
    case DCP_X_IND:
    case DCP_IND_Y:
        decrement(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        compare(acc, op_decode.data);
        break;

    case ISB_ZPG:
    case ISB_ZPG_X:
    case ISB_ABS:
    case ISB_ABS_X:
    case ISB_ABS_Y:
    case ISB_X_IND:
    case ISB_IND_Y:
        increment(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        sbc(op_decode.data);
        break;

    case SLO_ZPG:
    case SLO_ZPG_X:
    case SLO_ABS:
    case SLO_ABS_X:
    case SLO_ABS_Y:
    case SLO_X_IND:
    case SLO_IND_Y:
        asl(op_decode.data);
        ora(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case RLA_ZPG:
    case RLA_ZPG_X:
    case RLA_ABS:
    case RLA_ABS_X:
    case RLA_ABS_Y:
    case RLA_X_IND:
    case RLA_IND_Y:
        rol(op_decode.data);
        and_op(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case SRE_ZPG:
    case SRE_ZPG_X:
    case SRE_ABS:
    case SRE_ABS_X:
    case SRE_ABS_Y:
    case SRE_X_IND:
    case SRE_IND_Y:
        lsr(op_decode.data);
        eor(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case RRA_ZPG:
    case RRA_ZPG_X:
    case RRA_ABS:
    case RRA_ABS_X:
    case RRA_ABS_Y:
    case RRA_X_IND:
    case RRA_IND_Y:
        ror(op_decode.data);
        adc(op_decode.data);
        write(op_decode.effective_address, op_decode.data);
        break;

    case ALR_IMM:
        and_op(op_decode.b1);
        lsr(acc);
        break;

    case ANC_IMM1:
    case ANC_IMM2:
        and_op(op_decode.b1);
        flags.carry = acc & 0x80;
        break;

    case ARR_IMM:
        arr(op_decode.b1);
        break;

    case SHY_ABS_X:
        op_decode.effective_address = ((y & ((op_decode.effective_address >> 8) + 1)) << 8) | (op_decode.effective_address & 0xFF);
        write(op_decode.effective_address, op_decode.effective_address >> 8);

        break;

    case SHX_ABS_Y:
        op_decode.effective_address = ((x & ((op_decode.effective_address >> 8) + 1)) << 8) | (op_decode.effective_address & 0xFF);
        write(op_decode.effective_address, op_decode.effective_address >> 8);
        break;

    case JAM_X00:
    case JAM_X01:
    case JAM_X02:
    case JAM_X03:
    case JAM_X04:
    case JAM_X05:
    case JAM_X06:
    case JAM_X07:
        logger::log(logger::LogLevel::Critical, "Unimplemented opcode=0x{:02X} encountered at clock {}", opcode, clock_counter);
        throw std::runtime_error("unimplemented opcode");
        break;

    default:
        logger::log(logger::LogLevel::Critical, "Unimplemented opcode=0x{:02X} encountered at clock {}", opcode, clock_counter);
        throw std::runtime_error("unimplemented opcode");
        break;
    }

    clock_counter += op_decode.op_info.min_cycles;

    if (update_pc)
    {
        pc += 1 + op_decode.read_bytes;
    }

    if (flags.brk || irq_signal && !flags.interrupt_inhibit)
    {
        irq();
    }

    if (clock_counter > static_cast<int32_t>(clock_rate))
    {
        clock_counter -= clock_rate;
    }
}

void MOS6502::reset()
{
    stack_ptr -= 3;
    uint8_t low_addr = read(RESET_VECTOR);
    uint8_t high_addr = read(RESET_VECTOR + 1);
    pc = make_address(low_addr, high_addr);
    // pc = make_address(high_addr, low_addr);
    flags.interrupt_inhibit = true;

    clock_counter += 7;

    logger::log(logger::LogLevel::Debug, "Reset: PC=0x{:04X} from 0x{:02X} 0x{:02X}", pc, high_addr, low_addr);
}

void MOS6502::irq()
{
    irq_signal = false;
    std::string interrupt_type;
    uint8_t p_flags;
    if (flags.brk)
    {
        interrupt_type = "BRK";
        pc += 2;
        p_flags = flags.get_php();
        logger::log(logger::LogLevel::Debug, "FLAGS = 0x{:08b}", p_flags);
        flags.brk = false;
        flags.interrupt_inhibit = true;
    }
    else
    {
        interrupt_type = "IRQ";
        p_flags = flags.get();
        pc -= 1;
    }
    push_pc();
    push(p_flags);

    uint8_t low_addr = read(IRQ_VECTOR);
    uint8_t high_addr = read(IRQ_VECTOR + 1);
    pc = make_address(low_addr, high_addr);

    clock_counter += 7;

    logger::log(
        logger::LogLevel::Debug, "{}: PC=0x{:04X} from 0x{:02X} 0x{:02X}",
        interrupt_type,
        pc, high_addr, low_addr);
}

void MOS6502::nmi()
{
    push_pc();
    push(flags.get());

    uint8_t low_addr = read(NMI_VECTOR);
    uint8_t high_addr = read(NMI_VECTOR + 1);
    pc = make_address(low_addr, high_addr);

    clock_counter += 8;

    logger::log(logger::LogLevel::Debug, "NMI: PC=0x{:04X} from 0x{:02X} 0x{:02X}", pc, high_addr, low_addr);
}

} // namespace mos6502
