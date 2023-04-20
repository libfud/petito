#ifndef MOS6502_HPP
#define MOS6502_HPP

#include <cstdint>

#include "opcode_table.hpp"

namespace mos6502 {

class SystemBus;

constexpr uint16_t MIN_RAM_SIZE = 256;

constexpr uint16_t NMI_VECTOR = 0xFFFA;
constexpr uint16_t RESET_VECTOR = 0xFFFC;
constexpr uint16_t IRQ_VECTOR = 0xFFFE;

constexpr uint8_t BRK_MASK = 0x20;
constexpr uint8_t PHP_MASK = 0x30;

struct Flags
{
    bool carry;
    bool zero;
    bool interrupt_inhibit;
    bool bcd_arithmetic;
    bool brk;
    // bool unused = true;
    bool overflow;
    bool negative;

    uint8_t get() const;
    uint8_t get_php() const;

    void set(uint8_t data);
    void set_n_and_z(uint8_t data);
};

struct CpuData
{
    Flags flags;
    uint16_t pc;
    uint8_t acc;
    uint8_t x;
    uint8_t y;
    uint8_t stack_ptr;
    uint8_t opcode;
    OpDecode op_decode;

    int clock_counter;
};

class MOS6502
{

public:
    MOS6502(SystemBus& system_bus, int32_t cpu_clock_rate);

    // void set_system_bus(SystemBus* system_bus);

    OpDecode decode(uint8_t opcode);

    void step_diagnostics(uint8_t opcode, const OpDecode& op_decode) const;

    uint32_t run(uint16_t steps);

    /** Driving clock */
    uint8_t step();

    /** Reset signal */
    void reset();

    /** Interrupt request signal */
    void irq();

    /** Nonmaskable interupt signal */
    void nmi();

    CpuData save_state() const;

    uint8_t debug_read(uint16_t address) const;

    void set_diagnostics(bool enable);

private:
    Flags flags;
    uint16_t pc;
    uint8_t acc;
    uint8_t x;
    uint8_t y;
    uint8_t stack_ptr;

    int32_t clock_rate;
    int clock_counter;

    uint8_t opcode = BRK_IMPL;
    OpDecode op_decode = {};

    SystemBus& system_bus;

    bool diagnostics;
    uint64_t irq_counter;
    uint64_t nmi_counter;

    void push(uint8_t data);

    void push_pc();

    uint8_t pull();

    void pull_pc();

    uint8_t read(uint16_t address);

    void write(uint16_t address, uint8_t data);

    void load_reg(uint8_t& reg, uint8_t data);

    uint16_t make_address(uint8_t addr_low, uint8_t addr_high) const;

    uint16_t absolute(uint8_t addr_low, uint8_t addr_high) const;

    /* Non-const because of pc modifier. */
    uint16_t absolute_idx(uint8_t addr_low, uint8_t addr_high, uint8_t idx);

    uint8_t zero_page_x(uint8_t addr_low) const;

    uint8_t zero_page_y(uint8_t addr_low) const;

    /* Non-const because of read. */
    uint16_t indirect(uint8_t addr_low, uint8_t addr_high);

    uint16_t x_indirect(uint8_t offset);

    uint16_t indirect_y(uint8_t offset);

    uint16_t rel_addr(uint8_t offset);

    void branch(uint16_t relative_address, bool flag);

    void compare(uint8_t reg, uint8_t value);

    void adc(uint8_t value);

    void sbc(uint8_t value);

    void arr(uint8_t value);

    void decrement(uint8_t& value);

    void increment(uint8_t& value);

    void and_op(uint8_t value);

    void asl(uint8_t& value);

    void bit_test(uint8_t value);

    void eor(uint8_t value);

    void lsr(uint8_t& value);

    void ora(uint8_t value);

    void rol(uint8_t& value);

    void ror(uint8_t& value);
};

}

#endif
