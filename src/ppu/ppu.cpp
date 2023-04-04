#include "ppu.hpp"
#include "../logger/logger.hpp"
#include "../system_bus.hpp"
#include <SDL.h>

namespace nes {

using logger::LogLevel;
using logger::log;

ObjectAttributeMemory::ObjectAttributeMemory(uint8_t &oam_address)
    :
    address(oam_address),
    internal_data(256, 0)
{
}

uint8_t ObjectAttributeMemory::read() const
{
    auto data = internal_data[address];
    if ((address % 4) == 2)
    {
        data &= 0xE3;
    }
    return data;
}

void ObjectAttributeMemory::write(uint8_t data)
{
    internal_data[address] = data;
    address++;
}

void AddressLatch::reset()
{
    address = 0;
    count = 0;
}

void AddressLatch::write(uint8_t data)
{
    auto shift = 8 * static_cast<uint8_t>(count % 2 == 1);
    address |= (data << shift);
    count++;
}

uint16_t AddressLatch::get_address() const {
    return address;
}

void AddressLatch::increment(uint8_t increment)
{
    address += increment;
}

PPU::PPU(NesSystemBus& system_bus) :
    ctrl{},
    mask{},
    status{},
    oam_address{},
    scroll_register{},
    addr_register{},
    data_register{},
    oam_dma{},
    scroll_address{},
    vram_address{},
    ppu_data_buffer{0},
    object_attribute_memory{oam_address},
    palette_table{PALETTE_RAM_SIZE, 0},
    latch{},
    latch_clock{},
    system_bus{system_bus},
    line_index{0},
    cycle_index{0},
    odd_frame{false},
    nmi_occurred{false},
    pal_screen(PALETTE_SCREEN_SIZE, 0)
{
    auto make_pixel = [](auto r, auto g, auto b)
    {
        return r << 16 | g << 8 | b;
    };
    pal_screen[0x00] = make_pixel(84, 84, 84);
	pal_screen[0x01] = make_pixel(0, 30, 116);
	pal_screen[0x02] = make_pixel(8, 16, 144);
	pal_screen[0x03] = make_pixel(48, 0, 136);
	pal_screen[0x04] = make_pixel(68, 0, 100);
	pal_screen[0x05] = make_pixel(92, 0, 48);
	pal_screen[0x06] = make_pixel(84, 4, 0);
	pal_screen[0x07] = make_pixel(60, 24, 0);
	pal_screen[0x08] = make_pixel(32, 42, 0);
	pal_screen[0x09] = make_pixel(8, 58, 0);
	pal_screen[0x0A] = make_pixel(0, 64, 0);
	pal_screen[0x0B] = make_pixel(0, 60, 0);
	pal_screen[0x0C] = make_pixel(0, 50, 60);
	pal_screen[0x0D] = make_pixel(0, 0, 0);
	pal_screen[0x0E] = make_pixel(0, 0, 0);
	pal_screen[0x0F] = make_pixel(0, 0, 0);

	pal_screen[0x10] = make_pixel(152, 150, 152);
	pal_screen[0x11] = make_pixel(8, 76, 196);
	pal_screen[0x12] = make_pixel(48, 50, 236);
	pal_screen[0x13] = make_pixel(92, 30, 228);
	pal_screen[0x14] = make_pixel(136, 20, 176);
	pal_screen[0x15] = make_pixel(160, 20, 100);
	pal_screen[0x16] = make_pixel(152, 34, 32);
	pal_screen[0x17] = make_pixel(120, 60, 0);
	pal_screen[0x18] = make_pixel(84, 90, 0);
	pal_screen[0x19] = make_pixel(40, 114, 0);
	pal_screen[0x1A] = make_pixel(8, 124, 0);
	pal_screen[0x1B] = make_pixel(0, 118, 40);
	pal_screen[0x1C] = make_pixel(0, 102, 120);
	pal_screen[0x1D] = make_pixel(0, 0, 0);
	pal_screen[0x1E] = make_pixel(0, 0, 0);
	pal_screen[0x1F] = make_pixel(0, 0, 0);

	pal_screen[0x20] = make_pixel(236, 238, 236);
	pal_screen[0x21] = make_pixel(76, 154, 236);
	pal_screen[0x22] = make_pixel(120, 124, 236);
	pal_screen[0x23] = make_pixel(176, 98, 236);
	pal_screen[0x24] = make_pixel(228, 84, 236);
	pal_screen[0x25] = make_pixel(236, 88, 180);
	pal_screen[0x26] = make_pixel(236, 106, 100);
	pal_screen[0x27] = make_pixel(212, 136, 32);
	pal_screen[0x28] = make_pixel(160, 170, 0);
	pal_screen[0x29] = make_pixel(116, 196, 0);
	pal_screen[0x2A] = make_pixel(76, 208, 32);
	pal_screen[0x2B] = make_pixel(56, 204, 108);
	pal_screen[0x2C] = make_pixel(56, 180, 204);
	pal_screen[0x2D] = make_pixel(60, 60, 60);
	pal_screen[0x2E] = make_pixel(0, 0, 0);
	pal_screen[0x2F] = make_pixel(0, 0, 0);

	pal_screen[0x30] = make_pixel(236, 238, 236);
	pal_screen[0x31] = make_pixel(168, 204, 236);
	pal_screen[0x32] = make_pixel(188, 188, 236);
	pal_screen[0x33] = make_pixel(212, 178, 236);
	pal_screen[0x34] = make_pixel(236, 174, 236);
	pal_screen[0x35] = make_pixel(236, 174, 212);
	pal_screen[0x36] = make_pixel(236, 180, 176);
	pal_screen[0x37] = make_pixel(228, 196, 144);
	pal_screen[0x38] = make_pixel(204, 210, 120);
	pal_screen[0x39] = make_pixel(180, 222, 120);
	pal_screen[0x3A] = make_pixel(168, 226, 144);
	pal_screen[0x3B] = make_pixel(152, 226, 180);
	pal_screen[0x3C] = make_pixel(160, 214, 228);
	pal_screen[0x3D] = make_pixel(160, 162, 160);
	pal_screen[0x3E] = make_pixel(0, 0, 0);
	pal_screen[0x3F] = make_pixel(0, 0, 0);
}

void PPU::fill_latch(uint8_t data)
{
    latch = data;
    latch_clock = system_bus.ppu_clock;
}

uint16_t PPU::cpu_map_address(uint16_t address)
{
    if (address == OAM_DMA)
    {
        return address;
    }
    auto mapped_address = (address - PPU_REG_HIGH) & PPU_ADDR_MASK;
    return mapped_address;
}

uint8_t PPU::cpu_read(uint16_t address)
{
    auto mapped_address = cpu_map_address(address);
    uint8_t data = 0xFF;
    auto clock_diff = system_bus.ppu_clock - latch_clock;
    if (clock_diff > (PPU_TICKS_PER_SEC / 2))
    {
        latch = 0x00;
    }

    switch (mapped_address)
    {
    case PPU_CTRL:
        data = latch;
        break;
    case PPU_MASK:
        data = latch;
        break;
    case PPU_STATUS:
        data = status.serialize() | (latch & 0x1F);
        status.in_v_blank = false;
        vram_address.reset();
        scroll_address.reset();
        break;
    case OAM_ADDR:
        data = latch;
        break;
    case OAM_DATA:
        data = object_attribute_memory.read();
        fill_latch(data);
        break;
    case PPU_SCROLL:
        data = latch;
        break;
    case PPU_ADDR:
        data = latch;
        break;
    case PPU_DATA:
        data = ppu_read();
        break;
    case OAM_DMA:
        data = oam_dma;
        break;
    default:
        log(LogLevel::Critical, "Invalid write to PPU {:04X}", address);
        break;
    }
    return data;
}

void PPU::cpu_write(uint16_t address, uint8_t data)
{
    auto mapped_address = cpu_map_address(address);
    switch (mapped_address)
    {
    case PPU_CTRL:
        ctrl.deserialize(data);
        break;
    case PPU_MASK:
        mask.deserialize(data);
        break;
    case PPU_STATUS:
        break;
    case OAM_ADDR:
        oam_address = data;
        break;
    case OAM_DATA:
        object_attribute_memory.write(data);
        break;
    case PPU_SCROLL:
        scroll_register = data;
        scroll_address.write(data);
        break;
    case PPU_ADDR:
        addr_register = data;
        vram_address.write(data);
        break;
    case PPU_DATA:
        data_register = data;
        ppu_write(data);
        break;
    case OAM_DMA:
        logger::warn("OAM DMA!");
        oam_dma = data;
        break;
    default:
        logger::critical("Invalid read from PPU {:04X}", address);
        break;
    }
    fill_latch(data);
}

uint8_t PPU::ppu_read()
{
    auto address = vram_address.get_address();
    vram_address.increment(ctrl.vram_increment);
    uint8_t data = latch;
    if (address >= PALETTE_RAM_START)
    {
        auto mapped_address = (address - PALETTE_RAM_START) % PALETTE_RAM_SIZE;
        auto new_data = palette_table[mapped_address];
        fill_latch(new_data);
        return new_data;
    }
    else
    {
        auto new_data = system_bus.ppu_read(address);
        fill_latch(new_data);
    }

    return data;
}

void PPU::ppu_write(uint8_t data)
{
    auto address = vram_address.get_address();
    vram_address.increment(ctrl.vram_increment);
    if (address >= PALETTE_RAM_START)
    {
        auto mapped_address = (address - PALETTE_RAM_START) % PALETTE_RAM_SIZE;
        palette_table[mapped_address] = data;
    }
    else
    {
        system_bus.ppu_write(address, data);
    }
}

int64_t cpu_clock_nmi = 0;
void PPU::nmi()
{
    auto cpu_clock_2 = system_bus.cpu_clock;
    auto clock_diff = cpu_clock_2 - cpu_clock_nmi;
    logger::warn("NMI {} {} {}", cpu_clock_nmi, cpu_clock_2, clock_diff);
    cpu_clock_nmi = cpu_clock_2;
    logger::warn("NMI!");
    system_bus.signals.nmi = true;
    ctrl.generate_nmi = false;
}

void PPU::dma()
{
    logger::warn("DMA!");
    uint16_t base_address = oam_dma << 8;
    run(1);
    for (auto idx = 0; idx < 256; ++idx)
    {
        auto address = base_address + idx;
        object_attribute_memory.write(system_bus.read(address));
        run(2);
    }
    // system_bus.cpu_clock += 513;
    // system_bus.ppu_clock += 513 * 3;
}

void PPU::run(int cpu_cycles)
{
    int steps = cpu_cycles * PPU_CLOCKS_PER_CPU_CLOCK;
    for (int idx = 0; idx < steps; ++idx)
    {
        step();
        system_bus.ppu_clock++;
    }
}

int64_t cpu_clock_1 = 0;
void PPU::step()
{
    auto is_rendering = mask.show_sprites && mask.show_background;
    if (line_index == VBLANK_LINE_0 && cycle_index == 1)
    {
        auto cpu_clock_2 = system_bus.cpu_clock;
        auto clock_diff = cpu_clock_2 - cpu_clock_1;
        // logger::warn("IN VBLANK {} {} {}", cpu_clock_1, cpu_clock_2, clock_diff);
        cpu_clock_1 = system_bus.cpu_clock;
        status.in_v_blank = true;
        nmi_occurred = true;

        if (ctrl.generate_nmi && nmi_occurred)
        {
            nmi();
        }
    }
    else if (line_index == PRE_RENDER_SCANLINE && cycle_index == 1)
    {
        auto cpu_clock_2 = system_bus.cpu_clock;
        auto clock_diff = cpu_clock_2 - cpu_clock_1;
        // logger::warn("Out of VBLANK {} {} {}", cpu_clock_1, cpu_clock_2, clock_diff);
        status.in_v_blank = false;
        nmi_occurred = false;
        status.sprite_overflow = false;
        status.sprite_0_hit = false;
    }

    // auto render = true;
    auto special_dot = line_index == PRE_RENDER_SCANLINE && cycle_index == ODD_SPECIAL_TICK;
    if (odd_frame && is_rendering && special_dot)
    {
        // line_index = 0;
        // cycle_index = 0;
        // odd_frame = !odd_frame;
        // return;
        cycle_index++;
    }

    cycle_index++;
    if (cycle_index >= PPU_TICKS_PER_LINE)
    {
        cycle_index = 0;
        line_index++;
    }

    if (line_index >= SCANLINES_PER_FRAME)
    {
        line_index = 0;
        odd_frame = !odd_frame;
    }
}

bool is_initialized = false;
SDL_Window* Window = nullptr;
SDL_Surface* ScreenSurface = nullptr;
SDL_Surface* RenderedImage = nullptr;

bool init();

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logger::critical("Could not initialize vidoe: {}", SDL_GetError());
        return false;
    }

    Window = SDL_CreateWindow(
        "Petito NES",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        NTSC_WIDTH,
        NTSC_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (Window == nullptr)
    {
        logger::critical("Could not initialize Window: {}", SDL_GetError());
        return false;
    }

    ScreenSurface = SDL_GetWindowSurface(Window);

    is_initialized = true;
    return true;
}

void PPU::render()
{
    if (!is_initialized)
    {
        init();
        auto depth = 32;
        RenderedImage = SDL_CreateRGBSurface(
            0,
            NTSC_WIDTH,
            NTSC_HEIGHT,
            depth,
            0x00FF0000,
            0x0000FF00,
            0x000000FF,
            0);
        if (RenderedImage == nullptr)
        {
            logger::critical("Could not get create surface {}", SDL_GetError());
            return;
        }
        auto fmt = RenderedImage->format;
        if (fmt->BitsPerPixel != depth)
        {
            logger::critical("Could not get correct format");
            return;
        }
        rendered_image.resize(NTSC_WIDTH * NTSC_HEIGHT);
        for (auto& val : rendered_image)
        {
            val = 0;
        }
    }

    // (* 240 256) 61440
    for (auto row = 0; row < NTSC_HEIGHT; ++row)
    {
        for (auto col = 0; col < NTSC_WIDTH; ++col)
        {
            auto index = row * NTSC_WIDTH + col;
            uint32_t& pixel = rendered_image[index];
            pixel = system_bus.ppu_read(0x0000 + index % 0x1000);
            pixel |= system_bus.ppu_read(0x1000 + index % 0x1000 + 1) << 8;
            pixel |= system_bus.ppu_read(0x0000 + index % 0x1000 + 2) << 16;
            pixel |= system_bus.ppu_read(0x1000 + index % 0x1000 + 3) << 24;
        }
    }

    // SDL_LockSurface(RenderedImage);
    auto pixel_ptr = static_cast<uint32_t*>(RenderedImage->pixels);
    std::memcpy(pixel_ptr, rendered_image.data(), sizeof(uint32_t) * rendered_image.size());
    // SDL_UnlockSurface(RenderedImage);
    SDL_BlitSurface(RenderedImage, nullptr, ScreenSurface, nullptr);
    SDL_UpdateWindowSurface(Window);
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            std::exit(0);
        }
    }
}

} // namespace nes
