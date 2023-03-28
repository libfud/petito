#include <chrono>
#include <thread>

#include <fmt/core.h>
#include <fmt/format.h>

#include "mos6502.hpp"
#include "logger/logger.hpp"
#include "nes.hpp"
#include "cartridge.hpp"
#include "opcode_table.hpp"

namespace mos6502 {

uint8_t Flags::get()
{
    return
        (negative << 7) |
        (overflow << 6) |
        (1 << 5) |
        (brk << 4) |
        (bcd_arithmetic << 3) |
        (interrupt_inhibit << 2) |
        (zero << 1) |
        carry;
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
    carry = data & 0x01;
    zero = (data >> 1) & 0x01;
    interrupt_inhibit = (data >> 2) & 0x01;
    bcd_arithmetic = (data >> 3) & 0x01;
    overflow = (data >> 6) & 0x01;
    negative = (data >> 7) & 0x01;
}

void Flags::set_n_and_z(uint8_t data)
{
    zero = data == 0;
    negative = data >> 7;
}

MOS6502::MOS6502() :
    flags(),
    pc(RESET_VECTOR),
    acc(0),
    x(0),
    y(0),
    stack_ptr(0x00),
    memory(nullptr),
    clock_counter(0),
    irq_signal(false)
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
    logger::log(logger::LogLevel::Trace, "writing 0x{:04X} 0x{:02X}", address, data);
    memory->write(address, data);
    if ((address == 0x4010 && (data & 0x80)) ||
        (address == 0x4017 && !(data & 0xC0)))
    {
        // logger::log(logger::LogLevel::Debug, "HEYHO {:04X} {:02X}", address, data);
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

unsigned int running_counter = 0;
unsigned int last_clock = 0;
bool reset_triggered = false;

CpuData MOS6502::save_state()
{
    return {flags, pc, acc, x, y, stack_ptr, clock_counter};
}

void MOS6502::step()
{
    uint16_t effective_address = 0;
    uint8_t data = 0;
    uint8_t opcode = read(pc);
    uint8_t status = read(0x6000);

    OpcodeInfo op_info = OPCODE_INFO_TABLE[opcode];
    uint8_t b1 = 0;
    uint8_t b2 = 0;
    uint8_t read_bytes = address_mode_num_bytes(op_info.address_type);
    switch (read_bytes)
    {
    case 2:
        b2 = read(pc + 2);
    case 1:
        b1 = read(pc + 1);
    case 0:
        break;
    default:
        throw std::runtime_error("invalid number of bytes to read");
    }

    switch (op_info.address_type)
    {
    case AddressType::A:
        break;
    case AddressType::ABS:
        effective_address = absolute(b1, b2);
        data = read(effective_address);
        break;
    case AddressType::ABS_X:
        effective_address = absolute_idx(b1, b2, x);
        data = read(effective_address);
        break;
    case AddressType::ABS_Y:
        effective_address = absolute_idx(b1, b2, y);
        data = read(effective_address);
        break;
    case AddressType::IMM:
        break;
    case AddressType::IMPL:
        break;
    case AddressType::IND:
        effective_address = indirect(b1, b2);
        data = read(effective_address);
        break;
    case AddressType::X_IND:
        effective_address = x_indirect(b1);
        data = read(effective_address);
        break;
    case AddressType::IND_Y:
        effective_address = indirect_y(b1);
        data = read(effective_address);
        break;
    case AddressType::REL:
        effective_address = rel_addr(b1);
        break;
    case AddressType::ZPG:
        effective_address = b1;
        data = read(effective_address);
        break;
    case AddressType::ZPG_X:
        effective_address = zero_page_x(b1);
        data = read(effective_address);
        break;
    case AddressType::ZPG_Y:
        effective_address = zero_page_y(b1);
        data = read(effective_address);
        break;
    default:
        logger::log(logger::LogLevel::Critical, "Invalid addressing mode PC={:04X} opcode={:02X} {}",
                    pc, opcode, static_cast<uint8_t>(op_info.address_type));
        throw std::runtime_error("Invalid addressing mode");
    }

    uint16_t extra_info = effective_address;
    if (op_info.address_type == AddressType::REL)
    {
        extra_info = pc + 2 + effective_address;
    }

    std::string instr_fmt = format_opcode6502(opcode, b1, b2, x, y, extra_info, data);
    // if (clock_counter == running_counter)
    {
        logger::log(
            logger::LogLevel::Debug,
            "{:04X}  {} A:{:02X} X:{:02X} Y:{:02X} P:{:02X} SP:{:02X} CYC:{:>3}, EXTRA: {:02X}, {:02X}, {:02X}, {:02X}",
            pc, instr_fmt,
            acc, x, y, flags.get(), stack_ptr,
            static_cast<unsigned int>(clock_counter % 1000),
            dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[00],
            dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[01],
            dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[02],
            dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[03]
        );
    }
    if (status == 0x80)
    {
        // if (running_counter == clock_counter)
        {
            logger::log(
                logger::LogLevel::Debug,
                "Test in progress {:02X} {:02X} {:02X}\nmessage={}",
                dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[1],
                dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[2],
                dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[3],
                reinterpret_cast<char*>(&(dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[4]))
            );
        }
    }
    else if (status == 0x81)
    {
        logger::log(
            logger::LogLevel::Debug,
            "reset status=0x{:02X} message={}",
            status,
            reinterpret_cast<char*>(&(dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[4]))
        );

        if (reset_triggered && (clock_counter - last_clock > 2000))
        {
            logger::log(logger::LogLevel::Debug, "RESET!");
            reset_triggered = false;
            reset();
            last_clock = clock_counter;
            return;
        }
        else
        {
            reset_triggered = true;
            logger::log(logger::LogLevel::Debug, "Future Reset requested");
        }
    }
    else if (status != 0)
    {
        logger::log(
            logger::LogLevel::Debug,
            "Test status=0x{:02X} message={}",
            status,
            reinterpret_cast<char*>(&(dynamic_cast<nes::NesMemory*>(memory)->cart.prg_ram[4]))
        );
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(0));

    switch (opcode)
    {
    case BRK_IMPL:
        flags.brk = true;
        irq_signal = true;
        break;

    case ORA_X_IND:
        ora(data);
        break;

    case ORA_ZPG:
        ora(data);
        break;

    case ASL_ZPG:
        asl(data);
        write(effective_address, data);
        break;

    case PHP_IMPL:
        push(flags.get_php());
        break;

    case ORA_IMM:
        ora(b1);
        break;

    case ASL_A:
        asl(acc);
        break;

    case ORA_ABS:
        ora(data);
        break;

    case ASL_ABS:
        asl(data);
        write(effective_address, data);
        break;

    case BPL_REL:
        branch(effective_address, !flags.negative);
        break;

    case ORA_IND_Y:
        ora(data);
        break;

    case ORA_ZPG_X:
        ora(data);
        break;

    case ASL_ZPG_X:
        asl(data);
        write(effective_address, data);
        break;

    case CLC_IMPL:
        flags.carry = false;
        break;

    case ORA_ABS_Y:
        ora(data);
        break;

    case ORA_ABS_X:
        ora(data);
        break;

    case ASL_ABS_X:
        asl(data);
        write(effective_address, data);
        break;

    case JSR_ABS:
        pc += 2;
        push_pc();
        pc = effective_address;
        break;

    case AND_X_IND:
        and_op(data);
        break;

    case BIT_ZPG:
        bit_test(data);
        break;

    case AND_ZPG:
        and_op(data);
        break;

    case ROL_ZPG:
        rol(data);
        write(effective_address, data);
        break;

    case PLP_IMPL:
        data = pull();
        flags.set(data);
        break;

    case AND_IMM:
        and_op(b1);
        break;

    case ROL_A:
        rol(acc);
        break;

    case BIT_ABS:
        bit_test(data);
        break;

    case AND_ABS:
        and_op(data);
        break;

    case ROL_ABS:
        rol(data);
        write(effective_address, data);
        break;

    case BMI_REL:
        branch(effective_address, flags.negative);
        break;

    case AND_IND_Y:
        and_op(data);
        break;

    case AND_ZPG_X:
        and_op(data);
        break;

    case ROL_ZPG_X:
        rol(data);
        write(effective_address, data);
        break;

    case SEC_IMPL:
        flags.carry = true;
        break;

    case AND_ABS_Y:
        and_op(data);
        break;

    case AND_ABS_X:
        and_op(data);
        break;

    case ROL_ABS_X:
        rol(data);
        write(effective_address, data);
        break;

    case RTI_IMPL:
        data = pull();
        flags.set(data);
        pull_pc();
        pc -= 1;
        break;

    case EOR_X_IND:
        eor(read(effective_address));
        break;

    case EOR_ZPG:
        eor(read(effective_address));
        break;

    case LSR_ZPG:
        lsr(data);
        write(effective_address, data);
        break;

    case PHA_IMPL:
        push(acc);
        break;

    case EOR_IMM:
        eor(b1);
        break;

    case LSR_A:
        lsr(acc);
        break;

    case JMP_ABS:
        pc = effective_address;
        break;

    case EOR_ABS:
        eor(read(effective_address));
        break;

    case LSR_ABS:
        lsr(data);
        write(effective_address, data);
        break;

    case BVC_REL:
        branch(effective_address, !flags.overflow);
        break;

    case EOR_IND_Y:
        eor(data);
        break;

    case EOR_ZPG_X:
        eor(data);
        break;

    case LSR_ZPG_X:
        lsr(data);
        write(effective_address, data);
        break;

    case CLI_IMPL:
        flags.interrupt_inhibit = false;
        break;

    case EOR_ABS_Y:
        eor(data);
        break;

    case EOR_ABS_X:
        eor(data);
        break;

    case LSR_ABS_X:
        lsr(data);
        write(effective_address, data);
        break;

    case RTS_IMPL:
        pull_pc();
        break;

    case ADC_X_IND:
        adc(data);
        break;

    case ADC_ZPG:
        adc(data);
        break;

    case ROR_ZPG:
        ror(data);
        write(effective_address, data);
        break;

    case PLA_IMPL:
        acc = pull();
        flags.set_n_and_z(acc);
        break;

    case ADC_IMM:
        adc(b1);
        break;

    case ROR_A:
        ror(acc);
        break;

    case JMP_IND:
        pc = effective_address;
        break;

    case ADC_ABS:
        adc(data);
        break;

    case ROR_ABS:
        ror(data);
        write(effective_address, data);
        break;

    case BVS_REL:
        branch(effective_address, flags.overflow);
        break;

    case ADC_IND_Y:
        adc(data);
        break;

    case ADC_ZPG_X:
        adc(data);
        break;

    case ROR_ZPG_X:
        ror(data);
        write(effective_address, data);
        break;

    case SEI_IMPL:
        flags.interrupt_inhibit = true;
        break;

    case ADC_ABS_Y:
        adc(data);
        break;

    case ADC_ABS_X:
        adc(data);
        break;

    case ROR_ABS_X:
        ror(data);
        write(effective_address, data);
        break;

    case STA_X_IND:
        write(effective_address, acc);
        break;

    case STY_ZPG:
        write(effective_address, y);
        break;

    case STA_ZPG:
        write(effective_address, acc);
        break;

    case STX_ZPG:
        write(effective_address, x);
        break;

    case DEY_IMPL:
        decrement(y);
        break;

    case TXA_IMPL:
        acc = x;
        flags.set_n_and_z(acc);
        break;

    case STY_ABS:
        write(effective_address, y);
        break;

    case STA_ABS:
        write(effective_address, acc);
        break;

    case STX_ABS:
        write(effective_address, x);
        break;

    case BCC_REL:
        branch(effective_address, !flags.carry);
        break;

    case STA_IND_Y:
        write(effective_address, acc);
        break;

    case LDX_IMM:
        load_reg(x, b1);
        break;

    case STY_ZPG_X:
        write(effective_address, y);
        break;

    case STA_ZPG_X:
        write(effective_address, acc);
        break;

    case STX_ZPG_Y:
        write(effective_address, x);
        break;

    case TYA_IMPL:
        acc = y;
        flags.set_n_and_z(acc);
        break;

    case STA_ABS_Y:
        write(effective_address, acc);
        break;

    case TXS_IMPL:
        stack_ptr = x;
        break;

    case STA_ABS_X:
        write(effective_address, acc);
        break;

    case LDY_IMM:
        load_reg(y, b1);
        break;

    case LDA_X_IND:
        load_reg(acc, data);
        break;

    case LDY_ZPG:
        load_reg(y, data);
        break;

    case LDA_ZPG:
        load_reg(acc, data);
        break;

    case LDX_ZPG:
        load_reg(x, data);
        break;

    case TAY_IMPL:
        y = acc;
        flags.set_n_and_z(y);
        break;

    case LDA_IMM:
        load_reg(acc, b1);
        break;

    case TAX_IMPL:
        x = acc;
        flags.set_n_and_z(x);
        break;

    case LDY_ABS:
        load_reg(y, data);
        break;

    case LDA_ABS:
        load_reg(acc, data);
        break;

    case LDX_ABS:
        load_reg(x, data);
        break;

    case BCS_REL:
        branch(effective_address, flags.carry);
        break;

    case LDA_IND_Y:
        load_reg(acc, data);
        break;

    case LDY_ZPG_X:
        load_reg(y, data);
        break;

    case LDA_ZPG_X:
        load_reg(acc, data);
        break;

    case LDX_ZPG_Y:
        load_reg(x, data);
        break;

    case CLV_IMPL:
        flags.overflow = false;
        break;

    case LDA_ABS_Y:
        load_reg(acc, data);
        break;

    case TSX_IMPL:
        x = stack_ptr;
        flags.set_n_and_z(x);
        break;

    case LDY_ABS_X:
        load_reg(y, data);
        break;

    case LDA_ABS_X:
        load_reg(acc, data);
        break;

    case LDX_ABS_Y:
        load_reg(x, data);
        break;

    case CPY_IMM:
        compare(y, b1);
        break;

    case CMP_X_IND:
        compare(acc, data);
        break;

    case CPY_ZPG:
        compare(y, data);
        break;

    case CMP_ZPG:
        compare(acc, data);
        break;

    case DEC_ZPG:
        decrement(data);
        write(effective_address, data);
        break;

    case INY_IMPL:
        increment(y);
        break;

    case CMP_IMM:
        compare(acc, b1);
        break;

    case DEX_IMPL:
        decrement(x);
        break;

    case CPY_ABS:
        compare(y, data);
        break;

    case CMP_ABS:
        compare(acc, data);
        break;

    case DEC_ABS:
        decrement(data);
        write(effective_address, data);
        break;

    case BNE_REL:
        branch(effective_address, !flags.zero);
        break;

    case CMP_IND_Y:
        compare(acc, data);
        break;

    case CMP_ZPG_X:
        compare(acc, data);
        break;

    case DEC_ZPG_X:
        decrement(data);
        write(effective_address, data);
        break;

    case CLD_IMPL:
        flags.bcd_arithmetic = false;
        break;

    case CMP_ABS_Y:
        compare(acc, data);
        break;

    case CMP_ABS_X:
        compare(acc, data);
        break;

    case DEC_ABS_X:
        decrement(data);
        write(effective_address, data);
        break;

    case CPX_IMM:
        compare(x, b1);
        break;

    case SBC_X_IND:
        sbc(data);
        break;

    case CPX_ZPG:
        compare(x, data);
        break;

    case SBC_ZPG:
        sbc(data);
        break;

    case INC_ZPG:
        increment(data);
        write(effective_address, data);
        break;

    case INX_IMPL:
        increment(x);
        break;

    case SBC_IMM:
        sbc(b1);
        break;

    case NOP_IMPL:
        break;

    case CPX_ABS:
        compare(x, data);
        break;

    case SBC_ABS:
        sbc(data);
        break;

    case INC_ABS:
        increment(data);
        write(effective_address, data);
        break;

    case BEQ_REL:
        branch(effective_address, flags.zero);
        break;

    case SBC_IND_Y:
        sbc(data);
        break;

    case SBC_ZPG_X:
        sbc(data);
        break;

    case INC_ZPG_X:
        increment(data);
        write(effective_address, data);
        break;

    case SED_IMPL:
        flags.bcd_arithmetic = true;
        break;

    case SBC_ABS_Y:
        sbc(data);
        break;

    case SBC_ABS_X:
        sbc(data);
        break;

    case INC_ABS_X:
        increment(data);
        write(effective_address, data);
        break;

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
        acc = data;
        x = data;
        flags.set_n_and_z(x);
        break;

    case LXA_IMM:
        ora(0xFF);
        and_op(b1);
        x = acc;
        break;

    case SAX_ZPG:
    case SAX_ZPG_Y:
    case SAX_ABS:
    case SAX_X_IND:
        data = acc & x;
        write(effective_address, data);
        break;

    case SBX_IMM:
        compare(acc & x, b1);
        x = (acc & x) - b1;
        break;

    case USBC_IMM:
        sbc(b1);
        break;

    case DCP_ZPG:
    case DCP_ZPG_X:
    case DCP_ABS:
    case DCP_ABS_X:
    case DCP_ABS_Y:
    case DCP_X_IND:
    case DCP_IND_Y:
        decrement(data);
        write(effective_address, data);
        compare(acc, data);
        break;

    case ISB_ZPG:
    case ISB_ZPG_X:
    case ISB_ABS:
    case ISB_ABS_X:
    case ISB_ABS_Y:
    case ISB_X_IND:
    case ISB_IND_Y:
        increment(data);
        write(effective_address, data);
        sbc(data);
        break;

    case SLO_ZPG:
    case SLO_ZPG_X:
    case SLO_ABS:
    case SLO_ABS_X:
    case SLO_ABS_Y:
    case SLO_X_IND:
    case SLO_IND_Y:
        asl(data);
        ora(data);
        write(effective_address, data);
        break;

    case RLA_ZPG:
    case RLA_ZPG_X:
    case RLA_ABS:
    case RLA_ABS_X:
    case RLA_ABS_Y:
    case RLA_X_IND:
    case RLA_IND_Y:
        rol(data);
        and_op(data);
        write(effective_address, data);
        break;

    case SRE_ZPG:
    case SRE_ZPG_X:
    case SRE_ABS:
    case SRE_ABS_X:
    case SRE_ABS_Y:
    case SRE_X_IND:
    case SRE_IND_Y:
        lsr(data);
        eor(data);
        write(effective_address, data);
        break;

    case RRA_ZPG:
    case RRA_ZPG_X:
    case RRA_ABS:
    case RRA_ABS_X:
    case RRA_ABS_Y:
    case RRA_X_IND:
    case RRA_IND_Y:
        ror(data);
        adc(data);
        write(effective_address, data);
        break;

    case ALR_IMM:
        and_op(b1);
        lsr(acc);
        break;

    case ANC_IMM1:
    case ANC_IMM2:
        and_op(b1);
        flags.carry = acc & 0x80;
        break;

    case ARR_IMM:
        arr(b1);
        break;

    case SHY_ABS_X:
        effective_address = ((y & ((effective_address >> 8) + 1)) << 8) | (effective_address & 0xFF);
        write(effective_address, effective_address >> 8);

        break;

    case SHX_ABS_Y:
        effective_address = ((x & ((effective_address >> 8) + 1)) << 8) | (effective_address & 0xFF);
        write(effective_address, effective_address >> 8);
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

    if (opcode != JSR_ABS && opcode != JMP_ABS && opcode != JMP_IND)
    {
        pc += 1 + read_bytes;
    }
    if (flags.brk)
    {
        flags.brk = true;
        irq_signal = false;
        flags.interrupt_inhibit = true;
        irq();
    }

    clock_counter += op_info.min_cycles;

    if (irq_signal & !flags.interrupt_inhibit)
    {
        pc -= 1;
        flags.interrupt_inhibit = true;
        irq_signal = false;
        irq();
    }
    else
    {
        // pc += read_bytes;
    }

    if (clock_counter > 999999999)
    {
        clock_counter = 0;
        last_clock = 0;
        running_counter = 0;
    }
    if (clock_counter - running_counter > 100000)
    {
        running_counter = clock_counter;
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
    if (flags.interrupt_inhibit)
    {
        return;
    }

    push_pc();
    push(flags.get());

    uint8_t low_addr = read(IRQ_VECTOR);
    uint8_t high_addr = read(IRQ_VECTOR + 1);
    pc = make_address(low_addr, high_addr);

    clock_counter += 7;

    logger::log(logger::LogLevel::Debug, "IRQ: PC=0x{:04X} from 0x{:02X} 0x{:02X}", pc, high_addr, low_addr);
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
