#include "ppu.hpp"

namespace nes {

PPU::PPU() :
    raw_data{0},
    object_attribute_memory(256)
{}

uint16_t PPU::map_address(uint16_t address)
{
    auto mapped_address = (address - PPU_REG_HIGH) & PPU_ADDR_MASK;
    return mapped_address;
}

uint8_t PPU::read(uint16_t address)
{
    // auto mapped_address = map_address(address);
    // auto data = raw_data[mapped_address];
    // return data;
    return 0xFF;
}

void PPU::write(uint16_t address, uint8_t data)
{
    auto mapped_address = map_address(address);
    raw_data[mapped_address] = data;
}

uint8_t PPU::cpu_read(uint16_t address)
{
    auto mapped_address = map_address(address);
    auto data = raw_data[mapped_address];
    return data;
}

void PPU::cpu_write(uint16_t address, uint8_t data)
{
    auto mapped_address = map_address(address);
    raw_data[mapped_address] = data;
}
uint8_t PPU::ppu_read(uint16_t address)
{
    auto mapped_address = map_address(address);
    auto data = raw_data[mapped_address];
    return data;
}

void PPU::ppu_write(uint16_t address, uint8_t data)
{
    auto mapped_address = map_address(address);
    raw_data[mapped_address] = data;
}
}
