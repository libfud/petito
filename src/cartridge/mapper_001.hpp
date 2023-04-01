#ifndef MAPPER_001_HPP
#define MAPPER_001_HPP

#include <cstdint>

#include "mapper.hpp"
#include "cartridge.hpp"

namespace nes {

class Mapper001 : public Mapper {
    static constexpr uint8_t NAMETABLE_0 = 0;
    static constexpr uint8_t NAMETABLE_1 = 1;
    static constexpr uint8_t VERTICAL = 2;
    static constexpr uint8_t HORIZONTAL = 3;

    static constexpr uint8_t BANK_SHIFT = 14;
    static constexpr uint8_t PPU_BANK_SHIFT = 12;

    static constexpr uint8_t BANK_8000_FIXED = 0;
    static constexpr uint8_t BANK_C000_FIXED = 1;

    static constexpr uint8_t BANK_SIZE_32K = 0;
    static constexpr uint8_t BANK_SIZE_16K = 1;

    static constexpr uint8_t ONE_8K_BANK = 0;
    static constexpr uint8_t TWO_4K_BANKS = 1 << 4;

public:
    explicit Mapper001(Cartridge& cartridge);
    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t data) override;
    uint8_t ppu_read(uint16_t address) override;
    void ppu_write(uint16_t address, uint8_t data) override;

private:
    Cartridge& cartridge;
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

    void check_modify_load_register(uint16_t address, uint8_t data);
    void update_control_register();

    uint8_t& cpu_map(uint16_t address, bool& is_rom);

    uint8_t& ppu_map(uint16_t address, bool& is_rom);
};

} // namespace nes

#endif
