#ifndef PPU_OBJECT_HPP
#define PPU_OBJECT_HPP

#include <array>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>

#include "ppu_constants.hpp"

namespace nes {

union ObjectAttributeEntry
{
    struct EntryData {
    /** \brief Y position of sprite */
    uint8_t y_pos;
    /** \brief ID of tile from pattern memory */
    uint8_t id;
    /** \brief Flags define how sprite should be rendered */
    uint8_t attributes;
    /** \brief X position of sprite */
    uint8_t x_pos;
    } data;
    std::array<uint8_t, 4> values;

    uint8_t& y_pos();
    uint8_t& id();
    uint8_t& attributes();
    uint8_t& x_pos();

    bool flip_h() const;
    bool flip_v() const;
};

static_assert(std::is_standard_layout<ObjectAttributeEntry>::value);

class ObjectAttributeMemory
{
public:
    explicit ObjectAttributeMemory(uint8_t& oam_address);
    uint8_t read() const;
    void write(uint8_t data);
    ObjectAttributeEntry& entry(uint8_t index);

    uint8_t& operator[](size_t index);
private:
    uint8_t& address;
    std::vector<ObjectAttributeEntry> internal_data;
};

struct BackgroundInfo {
    uint8_t next_tile_id = 0x00;
    uint8_t next_tile_attrib = 0x00;
    uint8_t next_tile_lsb = 0x00;
    uint8_t next_tile_msb = 0x00;
    uint16_t shifter_pattern_lo = 0x00;
    uint16_t shifter_pattern_hi = 0x00;
    uint16_t shifter_attrib_lo = 0x00;
    uint16_t shifter_attrib_hi = 0x00;

    void update_shifters();
    void load_shifters();
};

union Pixel
{
    struct PixelData {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    } pixel_data;
    uint32_t value;

    Pixel();
    Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = nDefaultAlpha);
    Pixel(uint32_t p);
    uint8_t& red() { return pixel_data.red; }
    uint8_t& green() { return pixel_data.green; }
    uint8_t& blue() { return pixel_data.blue; }
    uint8_t& alpha() { return pixel_data.alpha; }
};

class Sprite
{
public:
    Sprite();
    Sprite(int32_t w, int32_t h);
    Sprite(const Sprite&) = default;
    ~Sprite() = default;

public:
    int32_t width = 0;
    int32_t height = 0;

public:
    bool set_pixel(int32_t x, int32_t y, Pixel p);
    std::vector<Pixel> col_data;
};

struct PixelComposition
{
    /** The 2-bit pixel to be rendered */
    uint8_t bg_pixel;
    /** The 3-bit index of the palette the pixel indexes */
    uint8_t bg_palette;
    /** \brief The 2-bit pixel to be rendered */
    uint8_t fg_pixel = 0x00;
    /** \brief The 3-bit index of the palette the pixel indexes */
    uint8_t fg_palette = 0x00;
    /** \brief Indicates sprite foreground priority */
    uint8_t fg_priority = 0x00;
    /** \brief The final pixel */
    uint8_t pixel = 0x00;
    /** \brief The final palette */
    uint8_t palette = 0x00;
};

using PaletteScreenArray = std::array<Pixel, PAL_SCREEN_SIZE>;
struct PaletteScreen {
public:
    PaletteScreen();
    Pixel& operator[](size_t index);
private:
    std::unique_ptr<PaletteScreenArray> data;
};

} // namespace nes

#endif
