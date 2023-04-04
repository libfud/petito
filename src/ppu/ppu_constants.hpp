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
static constexpr int PRE_RENDER_SCANLINE = 261;
static constexpr int ODD_SPECIAL_TICK = 339;
static constexpr int PPU_TICKS_PER_LINE = 341;

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

static constexpr size_t OAM_SIZE = 256;
static constexpr uint16_t PPU_REG_HIGH = 0x2000;
static constexpr uint32_t PALETTE_RAM_START = 0x3F00;
static constexpr uint32_t PALETTE_RAM_SIZE = 0x3F20 - PALETTE_RAM_START;

static constexpr size_t PALETTE_SCREEN_SIZE = 0x40;
static constexpr size_t PALETTE_SCREEN_MASK = PALETTE_SCREEN_SIZE - 1;

}
