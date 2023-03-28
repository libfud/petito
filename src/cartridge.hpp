#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "header.hpp"

namespace nes {

class Mapper {
public:
    virtual ~Mapper() = default;
    virtual uint8_t read(uint16_t address) = 0;
    virtual void write(uint16_t address, uint8_t data) = 0;
};

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

private:
    static constexpr size_t TRAINER_SIZE = 512;
    static constexpr size_t ROM_START = 0x4020;

    uint8_t mapper000_read(uint16_t address);
    void mapper000_write(uint16_t address, uint8_t data);

    uint8_t* mapper001_map(uint16_t address);
    uint8_t mapper001_read(uint16_t address);
    void mapper001_write(uint16_t address, uint8_t data);

    NesHeader header;
    uint8_t mapper_number;
    std::unique_ptr<Mapper> mapper;

    std::vector<uint8_t> trainer;

public:

    std::vector<uint8_t> prg_rom;
    std::vector<uint8_t> prg_ram;
    std::vector<uint8_t> chr_rom;
    std::vector<uint8_t> chr_ram;
};

class Mapper000 : public Mapper {
public:
    explicit Mapper000(Cartridge& cartridge);
    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t data) override;
private:
    Cartridge& cartridge;
    uint8_t* map(uint16_t address);
};

class Mapper001 : public Mapper {
    static constexpr uint8_t NAMETABLE_0 = 0;
    static constexpr uint8_t NAMETABLE_1 = 1;
    static constexpr uint8_t VERTICAL = 2;
    static constexpr uint8_t HORIZONTAL = 3;

    static constexpr uint8_t BANK_SHIFT = 14;

    static constexpr uint8_t BANK_8000_FIXED = 0;
    static constexpr uint8_t BANK_C000_FIXED = 1;

    static constexpr uint8_t BANK_SIZE_32K = 0;
    static constexpr uint8_t BANK_SIZE_16K = 1;

    static constexpr uint8_t ONE_8K_BANK = 0;
    static constexpr uint8_t TWO_4K_BANKS = 1 << 4;

    static constexpr uint16_t SIZE_4K = 0x1000;
    static constexpr uint16_t SIZE_8K = 0x2000;
    static constexpr uint16_t SIZE_16K = 0x4000;
    static constexpr uint16_t SIZE_32K = 0x8000;

public:
    explicit Mapper001(Cartridge& cartridge);
    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t data) override;

private:
    Cartridge& cartridge;
    uint8_t shift_register;
    uint8_t load_register;
    uint8_t chr_bank_0;
    uint8_t chr_bank_1;
    uint8_t prg_bank;
    bool prg_ram_enable;

    uint8_t write_counter;

    uint8_t mirroring;
    uint8_t prg_swap_bank;
    uint8_t prg_bank_size;
    uint8_t chr_bank_size;
};

}

#endif
