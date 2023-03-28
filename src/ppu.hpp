#ifndef PPU_HPP
#define PPU_HPP

#include <array>
#include <cstdint>
#include <vector>

namespace nes {

class PPU
{
private:
    static constexpr uint16_t PPU_REG_HIGH = 0x2000;

    static constexpr uint8_t PPU_CTRL = 0;
    static constexpr uint8_t PPU_MASK = 1;
    static constexpr uint8_t PPU_STATUS = 2;
    static constexpr uint8_t OAM_ADDR = 3;
    static constexpr uint8_t OAM_DATA = 4;
    static constexpr uint8_t PPU_SCROLL = 5;
    static constexpr uint8_t PPU_ADDR = 6;
    static constexpr uint8_t PPU_DATA = 7;
    static constexpr uint8_t PPU_ADDR_MASK = 0x0007;

    std::array<uint8_t, 8> raw_data;
    std::vector<uint8_t> object_attribute_memory;

    uint8_t oam_dma;

    uint16_t map_address(uint16_t address);

public:
    PPU();

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);

    // main bus comms
    uint8_t cpu_read(uint16_t address);
    void cpu_write(uint16_t address, uint8_t data);

    // ppu bus comms
    uint8_t ppu_read(uint16_t address);
    void ppu_write(uint16_t address, uint8_t data);

};

}

#endif
