#ifndef PPU_REGISTER_HPP
#define PPU_REGISTER_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace nes {

class PpuRegister
{
public:
    virtual void deserialize(uint8_t data) = 0;
    virtual uint8_t serialize() const = 0;
};

} // namespace nes

#endif
