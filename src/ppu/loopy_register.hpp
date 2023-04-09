#ifndef LOOPY_REGISTER_HPP
#define LOOPY_REGISTER_HPP

#include <cstdint>

#include "ppu_ctrl.hpp"

namespace nes {

union LoopyRegister
{
    struct LoopyRegisterData
    {
        uint16_t coarse_x : 5;
        uint16_t coarse_y : 5;
        uint16_t nametable_x : 1;
        uint16_t nametable_y : 1;
        uint16_t fine_y : 3;
        uint16_t unused : 1;
    } data;
    uint16_t reg;

    void set(uint16_t value);
    uint16_t get();
    void increment(const PpuCtrl& ctrl);

    void increment_scroll_x();
    void increment_scroll_y();

    void transfer_address_x(const LoopyRegister& tram_addr);
    void transfer_address_y(const LoopyRegister& tram_addr);

    uint16_t nametable_address() const;
    uint16_t attribute_address() const;
};

} // namespace nes

#endif
