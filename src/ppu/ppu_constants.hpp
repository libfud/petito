#include <cstdint>
#include <cstddef>

namespace nes {

static constexpr int PPU_CLOCKS_PER_CPU_CLOCK = 3;
static constexpr int PPU_TICKS_PER_SEC = 5369319;

static constexpr int SCANLINES_PER_FRAME = 262;
static constexpr int VISIBLE_SCANLINE_0 = 0;
static constexpr int VISIBLE_SCANLINE_F = 239;
static constexpr int POST_RENDER_LINE_0 = 240;
static constexpr int POST_RENDER_LINE_F = 260;
static constexpr int PRE_RENDER_SCANLINE = 261;
static constexpr int ODD_SPECIAL_TICK = 339;
static constexpr int PPU_TICKS_PER_LINE = 341;

static constexpr size_t NTSC_WIDTH = 256;
static constexpr size_t NTSC_HEIGHT = 240;

static constexpr size_t OAM_SIZE = 256;
static constexpr uint16_t PPU_REG_HIGH = 0x2000;
static constexpr uint32_t PALETTE_RAM_START = 0x3F00;
static constexpr uint32_t PALETTE_RAM_SIZE = 0x3F20 - PALETTE_RAM_START;

}
