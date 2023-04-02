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

namespace nes {

static constexpr int PPU_CLOCKS_PER_CPU_CLOCK = 3;
static constexpr int PPU_TICKS_PER_SEC = 5369319;

static constexpr size_t NTSC_WIDTH = 256;
static constexpr size_t NTSC_HEIGHT = 240;

static constexpr size_t OAM_SIZE = 256;
static constexpr uint16_t PPU_REG_HIGH = 0x2000;
static constexpr uint32_t PALETTE_RAM_START = 0x3F00;
static constexpr uint32_t PALETTE_RAM_SIZE = 0x3F20 - PALETTE_RAM_START;

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

    Cartridge& cart;

    mos6502::InterruptSignals& signals;

    void fill_latch(uint8_t data);

    uint16_t cpu_map_address(uint16_t address);

    void nmi();

public:
    void step();

    void render();
};

}

#endif
