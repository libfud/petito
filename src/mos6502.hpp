#ifndef MOS6502_HPP
#define MOS6502_HPP

#include <cstdint>

#include "memory.hpp"

namespace mos6502 {

constexpr uint16_t NMI_VECTOR = 0xFFFA;
constexpr uint16_t RESET_VECTOR = 0xFFFC;
constexpr uint16_t IRQ_VECTOR = 0xFFFE;

struct Flags
{
    bool carry;
    bool zero;
    bool interrupt_inhibit;
    bool bcd_arithmetic;
    bool brk;
    bool overflow;
    bool negative;

    uint8_t get();
    uint8_t get_php();
    uint16_t get_carry();

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

    unsigned int clock_counter;
};

class MOS6502
{

public:
    MOS6502();

    void set_memory(Memory* memory);

    /** Driving clock */
    void step();

    /** Reset signal */
    void reset();

    /** Interrupt request signal */
    void irq();

    /** Nonmaskable interupt signal */
    void nmi();

    CpuData save_state();

public:
    Flags flags;
    uint16_t pc;
    uint8_t acc;
    uint8_t x;
    uint8_t y;
    uint8_t stack_ptr;

    unsigned int clock_counter;

    bool irq_signal;

    Memory* memory;

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
