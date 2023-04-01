#include "ppu.hpp"
#include "../logger/logger.hpp"

namespace nes {

using logger::LogLevel;
using logger::log;

ObjectAttributeMemory::ObjectAttributeMemory(uint8_t &oam_address)
    :
    address(oam_address),
    internal_data(256)
{
}

uint8_t ObjectAttributeMemory::read() const
{
    return internal_data[address];
}

void ObjectAttributeMemory::write(uint8_t data)
{
    internal_data[address] = data;
    address++;
}

void AddressLatch::reset()
{
    address = 0;
    count = 0;
}

void AddressLatch::write(uint8_t data)
{
    auto shift = 8 * static_cast<uint8_t>(count % 2 == 1);
    address |= (data << shift);
    count++;
}

uint16_t AddressLatch::get_address() const {
    return address;
}

void AddressLatch::increment(uint8_t increment)
{
    address += increment;
}

PPU::PPU(const int& clock, Cartridge& cartridge) :
    ctrl{},
    mask{},
    status{},
    oam_address{},
    scroll_register{},
    addr_register{},
    data_register{},
    oam_dma{},
    scroll_address{},
    vram_address{},
    object_attribute_memory{oam_address},
    palette_table{PALETTE_RAM_SIZE},
    latch{},
    clock_counter{clock},
    latch_clock{},
    cart{cartridge}
{}

void PPU::fill_latch(uint8_t data)
{
    latch = data;
    latch_clock = clock_counter;
    log(LogLevel::Debug, "Latch Set! {} {}", clock_counter, latch_clock);
}

uint16_t PPU::cpu_map_address(uint16_t address)
{
    if (address == OAM_DMA)
    {
        return address;
    }
    auto mapped_address = (address - PPU_REG_HIGH) & PPU_ADDR_MASK;
    return mapped_address;
}

uint8_t PPU::cpu_read(uint16_t address)
{
    auto mapped_address = cpu_map_address(address);
    uint8_t data = 0xFF;
    if ((clock_counter - latch_clock) > PPU_TICKS_PER_SEC)
    {
        log(LogLevel::Debug, "Latch Decay! {} {}", clock_counter, latch_clock);
        latch = 0x00;
    }
    switch (mapped_address)
    {
    case PPU_CTRL:
        data = latch;
        break;
    case PPU_MASK:
        data = latch;
        break;
    case PPU_STATUS:
        data = status.serialize() | (latch & 0x1F);
        status.in_v_blank = false;
        vram_address.reset();
        scroll_address.reset();
        fill_latch(data);
        break;
    case OAM_ADDR:
        data = latch;
        break;
    case OAM_DATA:
        data = object_attribute_memory.read();
        fill_latch(data);
        break;
    case PPU_SCROLL:
        data = latch;
        break;
    case PPU_ADDR:
        data = latch;
        break;
    case PPU_DATA:
        data = ppu_read();
        fill_latch(data);
        break;
    case OAM_DMA:
        data = oam_dma;
        break;
    default:
        log(LogLevel::Critical, "Invalid write to PPU {:04X}", address);
        break;
    }
    return data;
}

void PPU::cpu_write(uint16_t address, uint8_t data)
{
    auto mapped_address = cpu_map_address(address);
    switch (mapped_address)
    {
    case PPU_CTRL:
        ctrl.deserialize(data);
        break;
    case PPU_MASK:
        mask.deserialize(data);
        break;
    case PPU_STATUS:
        status.deserialize(data);
        break;
    case OAM_ADDR:
        oam_address = data;
        break;
    case OAM_DATA:
        object_attribute_memory.write(data);
        break;
    case PPU_SCROLL:
        scroll_register = data;
        scroll_address.write(data);
        break;
    case PPU_ADDR:
        addr_register = data;
        vram_address.write(data);
        break;
    case PPU_DATA:
        data_register = data;
        break;
    case OAM_DMA:
        oam_dma = data;
        break;
    default:
        log(LogLevel::Critical, "Invalid read from PPU {:04X}", address);
        break;
    }
    fill_latch(data);
}

uint8_t PPU::ppu_read()
{
    auto address = vram_address.get_address();
    vram_address.increment(ctrl.vram_increment);
    if (address >= PALETTE_RAM_START)
    {
        auto mapped_address = (address - PALETTE_RAM_START) % PALETTE_RAM_SIZE;
        return palette_table[mapped_address];
    }
    // auto data = raw_data[mapped_address];
    // return data;
    return 0;
}

void PPU::ppu_write(uint8_t data)
{
    auto address = vram_address.get_address();
    if (address >= PALETTE_RAM_START)
    {
        auto mapped_address = (address - PALETTE_RAM_START) % PALETTE_RAM_SIZE;
        palette_table[mapped_address] = data;
    }
    // raw_data[mapped_address] = data;
}

}
