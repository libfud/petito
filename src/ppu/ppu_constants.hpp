#ifndef PPU_CONSTANTS_HPP
#define PPU_CONSTANTS_HPP

#include <cstdint>
#include <cstddef>

namespace nes {

static constexpr int PPU_CLOCKS_PER_CPU_CLOCK = 3;
static constexpr int PPU_TICKS_PER_SEC = 5369319;

static constexpr int SCANLINES_PER_FRAME = 262;
static constexpr int VISIBLE_SCANLINE_0 = 0;
static constexpr int VISIBLE_SCANLINE_F = 239;
static constexpr int POST_RENDER_LINE_0 = 240;
static constexpr int VBLANK_LINE_0 = 241;
static constexpr int POST_RENDER_LINE_F = 260;
static constexpr int PRE_RENDER_SCANLINE = -1;
static constexpr int ODD_SPECIAL_TICK = 339;
static constexpr int PPU_TICKS_PER_LINE = 341;

static constexpr int VISIBLE_SCANLINES = 240;
static constexpr int FRAME_END_SCANLINE = 261;

static constexpr int SCANLINE_END_CYCLE = 340;

static constexpr int CYCLE_TILE_0 = 2;
static constexpr int CYCLE_TILE_F = 257;

static constexpr int CYCLE_N_TILE_0 = 321;
static constexpr int CYCLE_N_TILE_F = 337;

static constexpr int CYCLE_END_OF_SCANLINE = 256;
static constexpr int SCANLINE_VISIBLE_DOTS = 256;

static constexpr int CYCLE_UNUSED_NT_FETCH_0 = 338;
static constexpr int CYCLE_UNUSED_NT_FETCH_1 = 340;

static constexpr int CYCLE_PRE_RENDER_V_UPDATE_0 = 280;
static constexpr int CYCLE_PRE_RENDER_V_UPDATE_F = 304;

static constexpr uint8_t SPRITE_MAX_COUNT = 8;
//                5369319
// (* 262 341 60) 5360520
// (- 5369319 (* 262 341 60.0985))
/*
static_assert(
    PPU_TICKS_PER_LINE * SCANLINES_PER_FRAME == PPU_TICKS_PER_SEC / 60.098,
    "PPU_TICKS_PER_SECOND MUST EQUAL DOTS TIMES LINES"
);
*/

static constexpr size_t NTSC_WIDTH = 256;
static constexpr size_t NTSC_HEIGHT = 240;
static constexpr size_t NTSC_SIZE = NTSC_WIDTH * NTSC_HEIGHT;

static constexpr size_t OAM_SIZE = 256;
static constexpr size_t OAM_ENTRY_COUNT = 64;
static constexpr size_t TBL_NAME_SIZE = 1024;
static constexpr size_t TBL_PATTERN_SIZE = 4096;
static constexpr size_t PAL_SCREEN_SIZE = 64;

static constexpr uint16_t PPU_REG_HIGH = 0x2000;
static constexpr uint32_t PALETTE_RAM_START = 0x3F00;
static constexpr uint32_t PALETTE_RAM_SIZE = 0x3F20 - PALETTE_RAM_START;

static constexpr size_t PALETTE_SCREEN_SIZE = 0x40;
static constexpr size_t PALETTE_SCREEN_MASK = PALETTE_SCREEN_SIZE - 1;

constexpr uint8_t  nDefaultAlpha = 0xFF;
constexpr uint32_t nDefaultPixel = static_cast<uint32_t>(nDefaultAlpha) << 24;
constexpr uint16_t NAMETABLE_SPACE_OFFSET = 0x2000;
constexpr uint16_t NAMETABLE_MASK = 0x0FFF;

} // namespace nes

#endif
