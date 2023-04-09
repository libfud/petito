#ifndef PPU_STATUS_HPP
#define PPU_STATUS_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace nes {

union PpuStatus
{
    struct PpuStatusData
    {
        uint8_t unused : 5;
        /* bit 5 */
        uint8_t sprite_overflow : 1;
        /* bit 6 */
        uint8_t sprite_0_hit : 1;
        /* bit 7 */
        uint8_t in_v_blank : 1;
    } data;
    uint8_t reg;

    void deserialize(uint8_t value);
    uint8_t serialize() const;
};

} // namespace nes

#endif
