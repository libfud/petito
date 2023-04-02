#include "ppu.hpp"
#include "../logger/logger.hpp"
#include <SDL.h>

namespace nes {

using logger::LogLevel;
using logger::log;

ObjectAttributeMemory::ObjectAttributeMemory(uint8_t &oam_address)
    :
    address(oam_address),
    internal_data(256)
{
}

uint8_t ObjectAttributeMemory::read() const
{
    return internal_data[address];
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

PPU::PPU(const int& clock, mos6502::InterruptSignals& interrupt_signals, Cartridge& cartridge) :
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
    object_attribute_memory{oam_address},
    palette_table{PALETTE_RAM_SIZE},
    latch{},
    clock_counter{clock},
    latch_clock{},
    cart{cartridge},
    line_index{0},
    cycle_index{0},
    odd_frame{false},
    signals{interrupt_signals}
{}

void PPU::fill_latch(uint8_t data)
{
    latch = data;
    latch_clock = clock_counter;
    log(LogLevel::Debug, "Latch Set! {} {}", clock_counter, latch_clock);
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
    if ((clock_counter - latch_clock) > PPU_TICKS_PER_SEC)
    {
        log(LogLevel::Debug, "Latch Decay! {} {}", clock_counter, latch_clock);
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
        fill_latch(data);
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
        fill_latch(data);
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
        break;
    case OAM_DMA:
        oam_dma = data;
        break;
    default:
        log(LogLevel::Critical, "Invalid read from PPU {:04X}", address);
        break;
    }
    fill_latch(data);
}

uint8_t PPU::ppu_read()
{
    auto address = vram_address.get_address();
    vram_address.increment(ctrl.vram_increment);
    if (address >= PALETTE_RAM_START)
    {
        auto mapped_address = (address - PALETTE_RAM_START) % PALETTE_RAM_SIZE;
        return palette_table[mapped_address];
    }
    auto data = cart.ppu_read(address);
    return data;
}

void PPU::ppu_write(uint8_t data)
{
    auto address = vram_address.get_address();
    if (address >= PALETTE_RAM_START)
    {
        auto mapped_address = (address - PALETTE_RAM_START) % PALETTE_RAM_SIZE;
        palette_table[mapped_address] = data;
    }
    else
    {
        cart.ppu_write(address, data);
    }
}

void PPU::nmi()
{
    signals.nmi = true;
    ctrl.generate_nmi = false;
}

void PPU::run(int cpu_cycles)
{
    int steps = cpu_cycles * PPU_CLOCKS_PER_CPU_CLOCK;
    while (steps > 0)
    {
        step();
        steps--;
    }
}

void PPU::step()
{
    if (line_index == POST_RENDER_LINE_0 + 1 && cycle_index == 1)
    {
        status.in_v_blank = true;
    }
    else if (line_index < POST_RENDER_LINE_0)
    {
        status.in_v_blank = false;
    }

    if (ctrl.generate_nmi && status.in_v_blank)
    {
        nmi();
    }

    if (odd_frame && line_index == PRE_RENDER_SCANLINE && cycle_index == ODD_SPECIAL_TICK)
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
        auto third_width = NTSC_WIDTH / 3;
        for (auto row = 0; row < NTSC_HEIGHT; ++row)
        {
            for (auto col = 0; col < NTSC_WIDTH; ++col)
            {
                auto index = row * NTSC_WIDTH + col;
                uint32_t& pixel = rendered_image[index];
                if (col < third_width)
                {
                    pixel = 0x00FF0000;
                }
                else if (col < (2 * third_width))
                {
                    pixel = 0x0000FF00;
                }
                else
                {
                    pixel = 0x000000FF;
                }
            }
        }
    }
    // SDL_LockSurface(RenderedImage);
    auto pixel_ptr = static_cast<uint32_t*>(RenderedImage->pixels);
    std::memcpy(pixel_ptr, rendered_image.data(), sizeof(uint32_t) * rendered_image.size());
    // SDL_UnlockSurface(RenderedImage);
    SDL_BlitSurface(RenderedImage, nullptr, ScreenSurface, nullptr);
    SDL_UpdateWindowSurface(Window);
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            std::exit(0);
        }
    }
}

}
