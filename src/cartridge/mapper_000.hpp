#ifndef MAPPER_000_HPP
#define MAPPER_000_HPP

#include <cstdint>

#include "mapper.hpp"
#include "cartridge.hpp"

namespace nes {

class Mapper000 : public Mapper {
public:
    explicit Mapper000(Cartridge& cartridge);
    uint8_t read(uint16_t address) override;
    void write(uint16_t address, uint8_t data) override;
    uint8_t ppu_read(uint16_t address) override;
    void ppu_write(uint16_t address, uint8_t data) override;
private:
    Cartridge& cartridge;

    uint8_t& map(uint16_t address);

    uint8_t& ppu_map(uint16_t address);
};

} // namespace nes

#endif
