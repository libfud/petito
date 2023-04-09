#include "ppu_object.hpp"
#include "ppu_constants.hpp"
#include <fmt/format.h>

namespace nes {

uint8_t& ObjectAttributeEntry::y_pos()
{
    return data.y_pos;
}

uint8_t& ObjectAttributeEntry::id()
{
    return data.id;
}

uint8_t& ObjectAttributeEntry::attributes()
{
    return data.attributes;
}

uint8_t& ObjectAttributeEntry::x_pos()
{
    return data.x_pos;
}

bool ObjectAttributeEntry::flip_h() const
{
    return (data.attributes & 0x40) > 0;
}

bool ObjectAttributeEntry::flip_v() const
{
    return (data.attributes & 0x80) > 0;
}

ObjectAttributeMemory::ObjectAttributeMemory(uint8_t &oam_address)
    :
    address(oam_address),
    internal_data(OAM_ENTRY_COUNT)
{
    for (auto& entry : internal_data)
    {
        std::memset(entry.values.data(), 0, sizeof(entry.values));
    }
}

uint8_t ObjectAttributeMemory::read() const
{
    auto data = internal_data[address / 4].values[address % 4];
    if ((address % 4) == 2)
    {
        data &= 0xE3;
    }
    return data;
}

void ObjectAttributeMemory::write(uint8_t data)
{
    internal_data[address / 4].values[address % 4] = data;
    // TODO: is this necessary?
    address++;
}

ObjectAttributeEntry& ObjectAttributeMemory::entry(uint8_t index)
{
    return internal_data[address];
}

uint8_t& ObjectAttributeMemory::operator[](size_t index)
{
    return internal_data[index / 4].values[index % 4];
}

void BackgroundInfo::update_shifters()
{
    // Shifting background tile pattern row
    shifter_pattern_lo <<= 1;
    shifter_pattern_hi <<= 1;

    // Shifting palette attributes by 1
    shifter_attrib_lo <<= 1;
    shifter_attrib_hi <<= 1;
}

// Prime the "in-effect" background tile shifters ready for outputting next
// 8 pixels in scanline.
void BackgroundInfo::load_shifters()
{
    /*
     * Shifters advance 1 bit along to feed the pixel compositor. The top 8 bits are the
     * current 8 pixels being drawn, and the bottom 8 bits are the next 8 pixels to be
     * drawn. The required bit is always the MSB of the shifter. However, "fine x" scrolling
     * plays a part in this too, so we can choose any one of the top 8 bits. */
    auto shift_pattern = [](auto& pattern, auto rhs){pattern = (pattern & 0xFF00) | rhs;};
    shift_pattern(shifter_pattern_lo, next_tile_lsb);
    shift_pattern(shifter_pattern_hi, next_tile_msb);

    /*
     * Attribute bits change every 8 pixels, but are synchronized with the pattern shifters for
     * convenience. The bottom 2 bits of the attribute word are taken, representing which
     * palette is being used for the current 8 pixels and the next 8 pixels, and "inflate" them
     * to 8 bit words.
     */
    auto shift_attrib = [](auto& attrib, auto next_attrib, auto mask)
    {
        attrib = (attrib & 0xFF00) | ((next_attrib & mask) ? 0xFF : 0x00);
    };
    shift_attrib(shifter_attrib_lo, next_tile_attrib, 0b01);
    shift_attrib(shifter_attrib_hi, next_tile_attrib, 0b10);
}

Pixel::Pixel() : pixel_data{0, 0, 0, nDefaultAlpha} {}


Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : pixel_data{red, green, blue, alpha}
{}

Pixel::Pixel(uint32_t p) : value(p) {}

Sprite::Sprite() : width{0}, height{0}, col_data{} {}

Sprite::Sprite(int32_t w, int32_t h)
    : width{w},
      height{h},
      col_data(static_cast<uint32_t>(width * height), nDefaultPixel)
{}

bool Sprite::set_pixel(int32_t x, int32_t y, Pixel p)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        col_data[y * width + x] = p;
        return true;
    }
    else
    {
        return false;
    }
}

PaletteScreen::PaletteScreen()
    :
    data{std::make_unique<PaletteScreenArray>(PaletteScreenArray{{
            {84, 84,  84}, { 0, 30, 116}, { 8, 16, 144}, {48,  0, 136},
            {68,  0, 100}, {92,  0,  48}, {84,  4,   0}, {60, 24,   0},
            {32, 42,   0}, { 8, 58,   0}, { 0, 64,   0}, { 0, 60,   0},
            { 0, 50,  60}, { 0,  0,   0}, { 0,  0,   0}, { 0,  0,   0},

            {152, 150, 152}, {  8, 76, 196}, { 48,  50, 236}, { 92,  30, 228},
            {136,  20, 176}, {160, 20, 100}, {152,  34,  32}, {120,  60,   0},
            { 84,  90,   0}, { 40, 114,  0}, {  8, 124,   0}, {  0, 118,  40},
            {  0, 102, 120}, {  0,   0,  0}, {  0,   0,   0}, {  0,   0,   0},

            {236, 238, 236}, { 76, 154, 236}, {120, 124, 236}, {176,  98, 236},
            {228,  84, 236}, {236,  88, 180}, {236, 106, 100}, {212, 136,  32},
            {160, 170,   0}, {116, 196,   0}, { 76, 208,  32}, { 56, 204, 108},
            { 56, 180, 204}, { 60,  60,  60}, {  0,   0,   0}, {  0,   0,   0},

            {236, 238, 236}, {168, 204, 236}, {188, 188, 236}, {212, 178, 236},
            {236, 174, 236}, {236, 174, 212}, {236, 180, 176}, {228, 196, 144},
            {204, 210, 120}, {180, 222, 120}, {168, 226, 144}, {152, 226, 180},
            {160, 214, 228}, {160, 162, 160}, {  0,   0,   0}, {  0,   0,   0}
        }}
    )}
{
}

Pixel& PaletteScreen::operator[](size_t index)
{
    return (*data)[index];
}

} // namespace nes
