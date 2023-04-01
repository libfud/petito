#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "header.hpp"
#include "mapper.hpp"

namespace nes {

static constexpr uint16_t SIZE_4K = 0x1000;
static constexpr uint16_t SIZE_8K = 0x2000;
static constexpr uint16_t SIZE_16K = 0x4000;
static constexpr uint16_t SIZE_32K = 0x8000;
static constexpr uint16_t PPU_RAM_SIZE = 0x800;

class Cartridge
{
public:
    bool load(const std::string& rom_name);

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);

    uint8_t cpu_read(uint16_t address);
    void cpu_write(uint16_t address, uint8_t data);

    uint8_t ppu_read(uint16_t address);
    void ppu_write(uint16_t address, uint8_t data);

    void init_mapper();

protected:
    static constexpr size_t TRAINER_SIZE = 512;
    static constexpr size_t ROM_START = 0x4020;

    NesHeader header;
    uint8_t mapper_number;
    std::unique_ptr<Mapper> mapper;

    std::vector<uint8_t> trainer;

public:

    std::vector<uint8_t> prg_rom;
    std::vector<uint8_t> prg_ram;
    std::vector<uint8_t> chr_rom;
    std::vector<uint8_t> chr_ram;

    std::vector<uint8_t> ppu_ram;
};

}

#endif
