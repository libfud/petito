#include "test_system_bus.hpp"
#include "mos6502.hpp"

#include <cassert>
#include <format>

namespace mos6502 {

size_t add_reset_procedure(std::vector<uint8_t>& program, uint16_t reset_address)
{
    std::vector<uint8_t> reset_procedure{
        // set X to 0xFF and A to 0
        LDX_IMM, 0xFF,
        LDA_IMM, 0x00,
        // zero out 0x00 to 0xFF, 0x200-0x2FF and 0x300-0x3FF
        STA_ABS_X, 0x00, ZERO_PAGE,
        STA_ABS_X, 0x00, INFO_PAGE,
        STA_ABS_X, 0x00, SCRATCH_PAGE,
        // decrement X
        DEX_IMPL,
        // repeat until X reaches zero
        BNE_REL, static_cast<uint8_t>(-(3 * 3 + 1 + 2)),
        // I'm too tired to think of an elegant solution so enjoy brute force
        STA_ABS_X, 0x00, ZERO_PAGE,
        STA_ABS_X, 0x00, INFO_PAGE,
        STA_ABS_X, 0x00, SCRATCH_PAGE,
        LDA_IMM, RESET_PATTERN[0],
        LDY_IMM, RESET_PATTERN[1],
        STA_ABS, 0x00, INFO_PAGE,
        STY_ABS, 0x01, INFO_PAGE,
        LDA_IMM, RESET_PATTERN[2],
        LDY_IMM, RESET_PATTERN[3],
        STA_ABS, 0x02, INFO_PAGE,
        STY_ABS, 0x03, INFO_PAGE,
        // go to idle procedure
        JMP_ABS, IDLE_ADDRESS_LOW, IDLE_ADDRESS_HIGH,
    };
    std::memcpy(&program[reset_address], reset_procedure.data(), reset_procedure.size());
    return reset_procedure.size();
}

size_t add_nmi_procedure(std::vector<uint8_t>& program, uint16_t nmi_address)
{
    constexpr auto acc_offset = 4;
    constexpr auto x_offset = 5;
    constexpr auto y_offset = 6;
    constexpr auto flags_offset = 7;
    constexpr auto sp_offset = 8;
    std::vector<uint8_t> nmi_procedure{
        // push Acc and flags to stack
        PHP_IMPL, PHA_IMPL,
        // increment NMI counter, write NMI to memory
        INC_ABS, NMI_INFO_OFFSET + 0, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('N'),
        STA_ABS, NMI_INFO_OFFSET + 1, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('M'),
        STA_ABS, NMI_INFO_OFFSET + 2, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('I'),
        STA_ABS, NMI_INFO_OFFSET + 3, INFO_PAGE,
        // write X to memory
        TXA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + x_offset, INFO_PAGE,
        // push X (in Acc) onto stack, transfer SP to X, write SP to memory
        PHA_IMPL, TSX_IMPL, TXA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + sp_offset, INFO_PAGE,
        // pop X from stack, restore X
        PLA_IMPL, TAX_IMPL,
        // write Y to memory
        TYA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + y_offset, INFO_PAGE,
        // restore A, write A to memory
        PLA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + acc_offset, INFO_PAGE,
        // copy flags to acc, write flags to memory
        PLA_IMPL,
        STA_ABS, NMI_INFO_OFFSET + flags_offset, INFO_PAGE,
        // restore flags
        PHA_IMPL, PLP_IMPL,
        // restore A
        LDA_ABS, NMI_INFO_OFFSET + acc_offset, INFO_PAGE,
        RTI_IMPL
    };
    std::memcpy(&program[nmi_address], nmi_procedure.data(), nmi_procedure.size());
    return nmi_procedure.size();
}

size_t add_irq_procedure(std::vector<uint8_t>& program, uint16_t irq_address)
{
    std::vector<uint8_t> irq_procedure{
        // push Acc and flags to stack
        PHP_IMPL, PHA_IMPL,
        // increment IRQ counter, write IRQ to memory
        INC_ABS, IRQ_INFO_OFFSET + 0, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('I'),
        STA_ABS, IRQ_INFO_OFFSET + 1, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('R'),
        STA_ABS, IRQ_INFO_OFFSET + 2, INFO_PAGE,
        LDA_IMM, static_cast<uint8_t>('Q'),
        STA_ABS, IRQ_INFO_OFFSET + 3, INFO_PAGE,
        // pop Acc and flags from stack
        PLA_IMPL, PLP_IMPL,
        // go to idle procedure
        RTI_IMPL
    };
    std::memcpy(&program[irq_address], irq_procedure.data(), irq_procedure.size());
    return irq_procedure.size();
}

size_t add_idle_procedure(std::vector<uint8_t>& program, uint16_t idle_address)
{
    std::vector<uint8_t> idle_procedure{
        // clear Interrupt inhibit
        CLI_IMPL,
        NOP_IMPL, NOP_IMPL, NOP_IMPL, NOP_IMPL, NOP_IMPL, NOP_IMPL, NOP_IMPL,
        // go back to start of idle procedure
        JMP_ABS, IDLE_ADDRESS_LOW, IDLE_ADDRESS_HIGH,
    };
    std::memcpy(&program[idle_address], idle_procedure.data(), idle_procedure.size());
    return idle_procedure.size();
}

TestSystemBus::TestSystemBus(
        size_t memory_size,
        size_t program_size,
        const std::array<uint8_t, 6>& vectors) :
    memory(memory_size),
    program(program_size),
    vectors{vectors}
{
    memory.reserve(memory_size);
    memory.resize(memory_size);
    program.reserve(program_size);
    program.resize(program_size);

    const auto check_proc_size = [](
        uint16_t base_address,
        uint16_t max_address,
        uint16_t proc_size,
        auto&& name)
    {
        if ((base_address + proc_size) > max_address)
        {
            throw std::runtime_error(
                fmt::format(
                    "{} procedure too large! Expected less than {}, got {}",
                    name,
                    max_address - base_address,
                    proc_size
                ));
        }
    };

    const auto nmi_address = vectors[1] << 8 | vectors[0];
    const auto reset_address = vectors[3] << 8 | vectors[2];
    const auto irq_address = vectors[5] << 8 | vectors[4];

    assert(reset_address >= memory_size);
    const auto reset_byte_address = reset_address - memory_size;
    const auto reset_proc_size = add_reset_procedure(program, reset_byte_address);
    check_proc_size(reset_address, nmi_address, reset_proc_size, "RESET");

    const auto nmi_base_address = nmi_address - reset_address;
    const auto nmi_proc_size = add_nmi_procedure(program, nmi_base_address);
    check_proc_size(nmi_address, irq_address, nmi_proc_size, "NMI");

    const auto irq_base_address = irq_address - reset_address;
    const auto irq_proc_size = add_irq_procedure(program, irq_base_address);
    check_proc_size(irq_address, IDLE_ADDRESS, irq_proc_size, "IRQ");

    const auto idle_base_address = IDLE_ADDRESS - reset_address;
    add_idle_procedure(program, idle_base_address);
}

InterruptSignals& TestSystemBus::get_interrupt_signals() {
    return interrupt_signals;
}

int32_t& TestSystemBus::get_cpu_clock() { return cpu_clock; };

uint8_t TestSystemBus::read(uint16_t address)
{
    if (address < memory.size())
    {
        return memory[address];
    }

    if (address < (memory.size() + program.size()))
    {
        uint16_t mapped_address = address - memory.size();
        return program[mapped_address];
    }

    if (address >= NMI_VECTOR)
    {
        uint16_t mapped_address = address - NMI_VECTOR;
        return vectors[mapped_address];
    }

    throw std::runtime_error(fmt::format("Invalid address read 0x{:04X}", address));
}

void TestSystemBus::write(uint16_t address, uint8_t data) {
    if (address < memory.size())
    {
        memory[address] = data;
    }
    else
    {
        throw std::runtime_error(
            fmt::format(
                "Invalid address write 0x{:04X}, 0x{:02X}",
                address,
                data));
    }
}

uint8_t TestSystemBus::const_read(uint16_t address) const {
    return address % 256;
}

} // namespace mos6502
