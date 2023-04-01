#ifndef PPU_STATUS_HPP
#define PPU_STATUS_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "ppu_register.hpp"

namespace nes {

struct PpuStatus : public PpuRegister
{
    /* bit 5 */
    bool sprite_overflow;
    /* bit 6 */
    bool sprite_0_hit;
    /* bit 7 */
    bool in_v_blank;

    void deserialize(uint8_t data) override;
    uint8_t serialize() const override;
};

} // namespace nes

#endif
