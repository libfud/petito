#ifndef PPU_HPP
#define PPU_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "ppu_ctrl.hpp"
#include "ppu_mask.hpp"
#include "ppu_status.hpp"
#include "../cartridge/cartridge.hpp"
#include "../interrupt_signals.hpp"
#include "ppu_constants.hpp"

namespace nes {

static constexpr uint8_t PPU_CTRL = 0;
static constexpr uint8_t PPU_MASK = 1;
static constexpr uint8_t PPU_STATUS = 2;
static constexpr uint8_t OAM_ADDR = 3;
static constexpr uint8_t OAM_DATA = 4;
static constexpr uint8_t PPU_SCROLL = 5;
static constexpr uint8_t PPU_ADDR = 6;
static constexpr uint8_t PPU_DATA = 7;
static constexpr uint8_t PPU_ADDR_MASK = 0x0007;
static constexpr uint16_t OAM_DMA = 0x4014;

class ObjectAttributeMemory
{
public:
    explicit ObjectAttributeMemory(uint8_t& oam_address);
    uint8_t read() const;
    void write(uint8_t data);
private:
    uint8_t& address;
    std::vector<uint8_t> internal_data;
};

class AddressLatch
{
public:
    void reset();
    void write(uint8_t data);
    uint16_t get_address() const;
    void increment(uint8_t increment);
private:
    uint16_t address;
    uint8_t count;
};

class PPU
{
public:
    PPU(const int& clock, mos6502::InterruptSignals& interrupt_signals, Cartridge& cartridge);

    // main bus comms
    uint8_t cpu_read(uint16_t address);
    void cpu_write(uint16_t address, uint8_t data);

    // ppu bus comms
    uint8_t ppu_read();
    void ppu_write(uint8_t data);

    void run(int cpu_cycles);

    void step();

    void render();

protected:
    PpuCtrl ctrl;
    PpuMask mask;
    PpuStatus status;
    uint8_t oam_address;
    uint8_t scroll_register;
    uint8_t addr_register;
    uint8_t data_register;

    uint8_t oam_dma;

    AddressLatch scroll_address;

    AddressLatch vram_address;

    ObjectAttributeMemory object_attribute_memory;
    std::vector<uint8_t> palette_table;
    std::vector<uint32_t> rendered_image;

    uint8_t latch;
    const int& clock_counter;
    int latch_clock;
    uint16_t line_index;
    uint16_t cycle_index;
    bool odd_frame;

    Cartridge& cart;

    mos6502::InterruptSignals& signals;

    void fill_latch(uint8_t data);

    uint16_t cpu_map_address(uint16_t address);

    void nmi();
};

}

#endif
