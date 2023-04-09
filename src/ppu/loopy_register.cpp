#include "loopy_register.hpp"

#include "ppu_constants.hpp"

namespace nes {

void LoopyRegister::set(uint16_t value)
{
    reg = value;
}

uint16_t LoopyRegister::get()
{
    return reg & 0x7FFF;
}

void LoopyRegister::increment(const PpuCtrl& ctrl)
{
    reg += ctrl.get_vram_increment();
}

void LoopyRegister::increment_scroll_x()
{
    /* Note: pixel perfect scrolling horizontally is handled by the data shifters. This
     * operates in the spatial domain of tiles, 8x8 pixel blocks. */

    // A single name table is 32x30 tiles. As we increment horizontally we may cross into a
    // neighboring nametable, or wrap around to a neighboring nametable
    if (data.coarse_x == 31)
    {
        data.coarse_x = 0;
        // Flip target nametable bit
        data.nametable_x = ~data.nametable_x;
    }
    else
    {
        data.coarse_x++;
    }
}

void LoopyRegister::increment_scroll_y()
{
    // If possible, just increment the fine y offset
    if (data.fine_y < 7)
    {
        data.fine_y++;
        return;
    }

    /*
     * The row may need to be incremented, potentially wrapping into neighboring vertical
     * nametables. N.B., the bottom two rows do not contain tile information. The coarse y
     * offset is used to identify which row of the nametable, and the fine y offset is the
     * specific "scanline."
     */

    data.fine_y = 0;

    // Check if vertical nametable targets need swapped
    if (data.coarse_y == 29)
    {
        data.coarse_y = 0;
        // flip the target nametable bit
        data.nametable_y = ~data.nametable_y;
    }
    else if (data.coarse_y == 31)
    {
        // The pointer may be in attribute memory, so wrap around the current nametable
        data.coarse_y = 0;
    }
    else
    {
        data.coarse_y++;
    }
}

void LoopyRegister::transfer_address_x(const LoopyRegister& tram_addr)
{
    data.nametable_x = tram_addr.data.nametable_x;
    data.coarse_x = tram_addr.data.coarse_x;
}

void LoopyRegister::transfer_address_y(const LoopyRegister& tram_addr)
{
    data.fine_y      = tram_addr.data.fine_y;
    data.nametable_y = tram_addr.data.nametable_y;
    data.coarse_y    = tram_addr.data.coarse_y;
}

uint16_t LoopyRegister::nametable_address() const
{
    return NAMETABLE_SPACE_OFFSET | (reg & 0x0FFF);
}

uint16_t LoopyRegister::attribute_address() const
{
    /* All attribute memory begins at 0x03C0 within a nametable.
     * OR with result to select target nametable, and attribute byte
     * offset. OR with 0x2000 to offset into nametable address
     * space on PPU bus.
     */
    constexpr uint16_t addr_base = 0x23C0;
    uint16_t attrib_addr = addr_base | data.nametable_y << 11;
    attrib_addr |= data.nametable_x << 10;
    attrib_addr |= (data.coarse_y >> 2) << 3;
    attrib_addr |= data.coarse_x >> 2;
    return attrib_addr;
}

} // namespace nes
