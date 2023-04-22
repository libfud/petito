#include "system_bus.hpp"

namespace mos6502 {

constexpr uint8_t ZERO_PAGE = 0x00;
constexpr uint16_t INFO_PAGE_ADDRESS = 0x0200;
constexpr uint8_t INFO_PAGE = INFO_PAGE_ADDRESS >> 8;
constexpr uint8_t SCRATCH_PAGE = 0x03;

constexpr uint16_t TEST_RAM_SIZE = 0x400;
constexpr uint16_t TEST_ROM_SIZE = 0x400;

constexpr uint16_t RESET_ADDRESS = TEST_RAM_SIZE;
constexpr uint8_t RESET_ADDRESS_LOW = RESET_ADDRESS & 0xFF;
constexpr uint8_t RESET_ADDRESS_HIGH = (RESET_ADDRESS >> 8) & 0xFF;

constexpr uint16_t NMI_ADDRESS = RESET_ADDRESS + 256;
constexpr uint8_t NMI_ADDRESS_LOW = NMI_ADDRESS & 0xFF;
constexpr uint8_t NMI_ADDRESS_HIGH = (NMI_ADDRESS >> 8) & 0xFF;

constexpr uint16_t IRQ_ADDRESS = RESET_ADDRESS + 2 * 256;
constexpr uint8_t IRQ_ADDRESS_LOW = IRQ_ADDRESS & 0xFF;
constexpr uint8_t IRQ_ADDRESS_HIGH = (IRQ_ADDRESS >> 8) & 0xFF;

constexpr uint16_t IDLE_ADDRESS = RESET_ADDRESS + 3 * 256;
constexpr uint8_t IDLE_ADDRESS_LOW = IDLE_ADDRESS & 0xFF;
constexpr uint8_t IDLE_ADDRESS_HIGH = (IDLE_ADDRESS >> 8) & 0xFF;

constexpr std::array<uint8_t, 4> RESET_PATTERN = {0xBE, 0xEF, 0xCA, 0xFE};
constexpr std::array<uint8_t, 3> NMI_PATTERN = {'N', 'M', 'I'};
constexpr std::array<uint8_t, 3> IRQ_PATTERN = {'I', 'R', 'Q'};

constexpr uint8_t NMI_INFO_OFFSET = 0x10;

constexpr uint8_t IRQ_INFO_OFFSET = 0x20;

constexpr std::array<uint8_t, 6> INTERRUPT_VECTORS{
    NMI_ADDRESS_LOW, NMI_ADDRESS_HIGH,
    RESET_ADDRESS_LOW, RESET_ADDRESS_HIGH,
    IRQ_ADDRESS_LOW, IRQ_ADDRESS_HIGH,
};

class TestSystemBus : public SystemBus
{
public:
    TestSystemBus(
        size_t memory_size,
        size_t program_size,
        const std::array<uint8_t, 6>& vectors);
    TestSystemBus(TestSystemBus&) = delete;
    TestSystemBus(TestSystemBus&&) = delete;
    TestSystemBus& operator=(TestSystemBus&) = delete;
    TestSystemBus&& operator=(TestSystemBus&&) = delete;
    virtual ~TestSystemBus() = default;

    InterruptSignals& get_interrupt_signals() override;

    int32_t& get_cpu_clock() override;

    uint8_t read(uint16_t address) override;

    void write(uint16_t address, uint8_t data) override;

    uint8_t const_read(uint16_t address) const override;

    std::vector<uint8_t> memory;
    std::vector<uint8_t> program;
    std::array<uint8_t, 6> vectors;
    InterruptSignals interrupt_signals = {};
    int32_t cpu_clock = 0;
};

} // namespace mos6502
