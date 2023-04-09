#ifndef PPU_HPP
#define PPU_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>
#include <SDL2/SDL.h>

#include "ppu_ctrl.hpp"
#include "ppu_mask.hpp"
#include "ppu_status.hpp"
#include "ppu_constants.hpp"
#include "loopy_register.hpp"
#include "ppu_object.hpp"

namespace nes {

class NesSystemBus;

static constexpr uint8_t PPU_CTRL = 0;
static constexpr uint8_t PPU_MASK = 1;
static constexpr uint8_t PPU_STATUS = 2;
static constexpr uint8_t OAM_ADDR = 3;
static constexpr uint8_t OAM_DATA = 4;
static constexpr uint8_t PPU_SCROLL = 5;
static constexpr uint8_t PPU_ADDR = 6;
static constexpr uint8_t PPU_DATA = 7;
static constexpr uint8_t PPU_ADDR_MASK = 0x0007;
static constexpr uint16_t OAM_DMA = 0x4014;

class AddressLatch
{
public:
    void reset();
    void write(uint8_t data);
    uint16_t get_address() const;
    void increment(const PpuCtrl& ctrl);
private:
    uint16_t address;
    uint8_t count;
};

enum class PpuState {
    PreRender,
    Render,
    PostRender,
    VerticalBlank
};

class PPU
{
public:
    explicit PPU(NesSystemBus& system_bus);

    uint8_t cpu_read(uint16_t address);

    void cpu_write(uint16_t address, uint8_t data);

    uint8_t ppu_read(uint16_t address);

    void ppu_write(uint16_t address, uint8_t data);

    void reset();

    void run(int cpu_cycles);

    void old_step();

    void step();

    void render();

    const Sprite& get_sprite_screen() const;

protected:
    NesSystemBus& system_bus;

    PpuCtrl control = {};

    PpuMask mask = {};

    PpuStatus status = {};

    uint8_t oam_address = {};

    uint8_t addr_register = 0;

    uint8_t oam_dma = 0;

    uint8_t fine_x = 0;

    bool latch_set = false;

    ObjectAttributeMemory object_attribute_memory;

    std::array<uint8_t, PALETTE_RAM_SIZE> palette_table = {};

    PaletteScreen palette_screen = {};

    std::unique_ptr<Sprite> sprite_screen;

    std::array<ObjectAttributeEntry, 8> sprite_scanline = {};

    std::array<uint8_t, 8> sprite_shifter_pattern_lo = {};

    std::array<uint8_t, 8> sprite_shifter_pattern_hi = {};

    int latch_clock = 0;

    int16_t scanline_index = 0;

    int16_t cycle = 0;

    BackgroundInfo bg_info = {};

    LoopyRegister tram_addr = {};

    LoopyRegister vram_addr = {};

    uint8_t address_latch = 0;

    uint8_t ppu_data_buffer = 0;

    uint8_t sprite_count = 0;

    bool odd_frame = false;

    bool nmi_occurred = false;

    bool frame_complete = false;

    bool sprite_0_hit_possible = false;

    bool sprite_0_being_rendered = false;

    bool is_pre_render_scanline() const;

    uint8_t ppu_data_read();

    void ppu_data_write(uint8_t data);

    void fill_latch(uint8_t data);

    uint16_t cpu_map_address(uint16_t address);

    void nmi();

    void dma();

    void render_background();

    void start_new_frame();

    void work_visible_frame();

    void update_shifters();

    void set_next_tile_addr_byte(uint8_t& next_tile_byte, uint8_t plane_offset);

    void fetch_next_bg_tile_attrib();

    void render_foreground();

    void evaluate_visible_sprites();

    void prepare_visible_sprites();

    void compose_background(PixelComposition& pixel_composition);

    void compose_foreground(PixelComposition& pixel_composition);

    void composite_pixels(PixelComposition& pixel_composition);

    Pixel& get_color_from_palette_ram(const PixelComposition& pixel_composition);

    bool is_initialized = false;
    SDL_Window* Window = nullptr;
    SDL_Surface* ScreenSurface = nullptr;
    SDL_Surface* RenderedImage = nullptr;

    bool init_sdl();
};

}

#endif
