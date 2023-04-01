#ifndef MAPPER_HPP
#define MAPPER_HPP

#include <cstdint>

namespace nes {

class Mapper {
public:
    virtual ~Mapper() = default;
    virtual uint8_t read(uint16_t address) = 0;
    virtual void write(uint16_t address, uint8_t data) = 0;
    virtual uint8_t ppu_read(uint16_t address) = 0;
    virtual void ppu_write(uint16_t address, uint8_t data) = 0;
};

} // namespace nes

#endif
