#ifndef PPU_HPP
#define PPU_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

#include "virtual_screen.hpp"
#include "ppu_constants.hpp"

namespace nes {

class NesSystemBus;

static constexpr uint16_t PPU_CTRL = PPU_REG_HIGH + 0;
static constexpr uint16_t PPU_MASK = PPU_REG_HIGH + 1;
static constexpr uint16_t PPU_STATUS = PPU_REG_HIGH + 2;
static constexpr uint16_t OAM_ADDR = PPU_REG_HIGH + 3;
static constexpr uint16_t OAM_DATA = PPU_REG_HIGH + 4;
static constexpr uint16_t PPU_SCROLL = PPU_REG_HIGH + 5;
static constexpr uint16_t PPU_ADDR = PPU_REG_HIGH + 6;
static constexpr uint16_t PPU_DATA = PPU_REG_HIGH + 7;
static constexpr uint16_t PPU_ADDR_MASK = 0x0007;
static constexpr uint16_t OAM_DMA = 0x4014;

enum class PpuState {
    PreRender,
    Render,
    PostRender,
    VerticalBlank
};

enum class CharacterPage
{
    Low,
    High
};

class PPU
{
public:
    PPU(NesSystemBus& system_bus, VirtualScreen & virtual_screen);

    void reset();

    uint8_t read_palette(uint8_t palette_address);

    void run(int cpu_cycles);

    void step();

    void prerender();

    void render();

    void render_background(uint8_t& bg_color, bool& bg_opaque);

    void render_sprites(
        uint8_t& sprite_color,
        bool& sprite_opaque,
        bool& sprite_foreground,
        const bool& bg_opaque);

    void post_render();

    void render_vblank();

    void dma();

    void nmi();

    uint8_t cpu_read(uint16_t address);

    void cpu_write(uint16_t address, uint8_t data);

    void control(uint8_t ctrl);

    void set_mask(uint8_t mask);

    void set_oam_address(uint8_t addr);

    void set_data_address(uint8_t addr);

    void set_scroll(uint8_t scroll);

    void set_data(uint8_t data);

    uint8_t get_status();

    uint8_t get_data();

    uint8_t get_oam_data();

    void setOAMData(uint8_t value);

private:

    uint8_t read_oam(uint8_t addr);

    void write_oam(uint8_t addr, uint8_t value);

    uint8_t read(uint16_t address);

protected:
    NesSystemBus& system_bus;

    VirtualScreen& virtual_screen;

    std::array<uint8_t, 32> palette = std::array<uint8_t, 32>{};

    std::vector<uint8_t> sprite_memory;

    std::vector<uint8_t> scanline_sprites;

    PpuState pipeline_state = PpuState::PreRender;

    int cycle = 0;

    int scanline = 0;

    bool even_frame = true;

    bool vblank = false;

    bool sprite_0_hit = false;

    bool sprite_overflow = false;

    uint16_t data_address = 0;

    uint16_t temp_address = 0;

    uint8_t fine_x_scroll = 0;

    bool first_write = true;

    uint8_t data_buffer = 0;

    uint8_t sprite_data_address = 0;

    bool long_sprites = false;

    bool generate_interrupt = false;

    bool greyscale_mode = false;

    bool show_sprites = true;

    bool show_background = true;

    bool hide_edge_sprites = false;

    bool hide_edge_background = false;

    CharacterPage bg_page = CharacterPage::Low;

    CharacterPage sprite_page = CharacterPage::Low;

    uint16_t data_address_increment = 1;

    std::vector<std::vector<sf::Color>> picture_buffer;
};

}

#endif
