#include "ppu.hpp"
#include "../logger/logger.hpp"
#include "../system_bus.hpp"

namespace nes {

using logger::LogLevel;
using logger::log;

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

void AddressLatch::increment(const PpuCtrl& control)
{
    address += control.get_vram_increment();
}

PPU::PPU(NesSystemBus& system_bus) :
    system_bus{system_bus},
    object_attribute_memory{oam_address},
    sprite_screen{std::make_unique<Sprite>(Sprite(256, 240))}
{
}

void PPU::fill_latch(uint8_t data)
{
    address_latch = data;
    // ppu_data_buffer = data;
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
    auto clock_diff = system_bus.ppu_clock - latch_clock;
    if (clock_diff > (PPU_TICKS_PER_SEC / 2))
    {
        address_latch = 0x00;
        // ppu_data_buffer = 0x00;
    }
    uint8_t data = address_latch;
    // uint8_t data = ppu_data_buffer;

    switch (mapped_address)
    {
    case PPU_CTRL:
        break;
    case PPU_MASK:
        break;
    case PPU_STATUS:
        data = status.serialize() | (ppu_data_buffer & 0x1F);
        status.data.in_v_blank = 0;
        latch_set = false;
        break;
    case OAM_ADDR:
        break;
    case OAM_DATA:
        data = object_attribute_memory.read();
        fill_latch(data);
        break;
    case PPU_SCROLL:
        break;
    case PPU_ADDR:
        break;
    case PPU_DATA:
        data = ppu_read(vram_addr.get());
        // data = ppu_data_buffer;
        // ppu_data_buffer = ppu_read(vram_addr.get());
        // if (vram_addr.get() >= 0x3F00)
        // {
        //     data = ppu_data_buffer;
        // }
        // vram_addr.increment(control);
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
        control.deserialize(data);
        tram_addr.data.nametable_x = control.data.nametable_x;
        tram_addr.data.nametable_y = control.data.nametable_y;
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
        if (latch_set)
        {
            fine_x = data & 0x07;
            tram_addr.data.coarse_x = data >> 3;
            latch_set = true;
        }
        else
        {
            tram_addr.data.fine_y = data & 0x07;
            tram_addr.data.coarse_y = data >> 3;
            latch_set = false;
        }
        break;
    case PPU_ADDR:
        if (latch_set)
        {
            auto tram_reg = tram_addr.get();
            auto new_tram_high = static_cast<uint16_t>((data & 0x3F)) << 8;
            auto new_tram_low = tram_reg & 0xFF;
            tram_addr.set(new_tram_high | new_tram_low);
            latch_set = true;
        }
        else
        {
            auto tram_reg = tram_addr.get();
            tram_addr.set((tram_reg & 0xFF00) | data);
            vram_addr = tram_addr;
            latch_set = false;
        }
        break;
    case PPU_DATA:
        ppu_data_write(data);
        ppu_data_buffer = data;
        break;
    case OAM_DMA:
        logger::warn("OAM DMA!");
        oam_dma = data;
        dma();
        break;
    default:
        logger::critical("Invalid read from PPU {:04X}", address);
        break;
    }
    fill_latch(data);
}

uint8_t PPU::ppu_read(uint16_t address)
{
    uint8_t data = address_latch;
    uint16_t anded_address = address & 0x3FFF;
    if (address >= PALETTE_RAM_START)
    {
        auto mapped_address = (anded_address - PALETTE_RAM_START) % PALETTE_RAM_SIZE;
        logger::debug(
            "PALETTE RAM START! 0x{:04X} 0x{:04X} 0x{:04X}",
            address, anded_address, mapped_address);
        auto new_data = palette_table[mapped_address];
        fill_latch(new_data);
        return new_data;
    }
    else
    {
        logger::debug(
            "SYSTEM BUS READ! 0x{:04X} 0x{:04X}",
            address, anded_address);
        auto new_data = system_bus.ppu_read(anded_address);
        fill_latch(new_data);
    }

    return data;
}

uint8_t PPU::ppu_data_read()
{
    auto address = vram_addr.get();
    vram_addr.increment(control);
    return ppu_read(address);
}

void PPU::ppu_write(uint16_t address, uint8_t data)
{
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

void PPU::ppu_data_write(uint8_t data)
{
    auto address = vram_addr.get();
    vram_addr.increment(control);
    ppu_write(address, data);
}

void PPU::reset()
{
    fine_x = 0x00;
    address_latch = 0x00;
    ppu_data_buffer = 0x00;
    scanline_index = 0;
    cycle = 0;
    bg_info = {};
    status.reg = 0;
    mask.reg = 0;
    control.reg = 0;
    vram_addr.reg = 0x0000;
    tram_addr.reg = 0x0000;
    odd_frame = false;
}

// int64_t cpu_clock_nmi = 0;
void PPU::nmi()
{
    // auto cpu_clock_2 = system_bus.cpu_clock;
    // auto clock_diff = cpu_clock_2 - cpu_clock_nmi;
    // logger::warn("NMI {} {} {}", cpu_clock_nmi, cpu_clock_2, clock_diff);
    // cpu_clock_nmi = cpu_clock_2;
    logger::warn("NMI!");
    system_bus.signals.nmi = true;
    // control.data.generate_nmi = false;
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
    system_bus.cpu_clock += 513;
    // system_bus.ppu_clock += 513 * 3;
}

void PPU::run(int cpu_cycles)
{
    int steps = cpu_cycles * PPU_CLOCKS_PER_CPU_CLOCK;
    for (auto idx = 0; idx < steps; ++idx)
    {
        step();
        system_bus.ppu_clock++;
    }
}

bool PPU::is_pre_render_scanline() const
{
    return scanline_index == PRE_RENDER_SCANLINE;
}

void PPU::step()
{
    if (scanline_index >= PRE_RENDER_SCANLINE && scanline_index < POST_RENDER_LINE_0)
    {
        render_background();

        render_foreground();
    }

    if (scanline_index == POST_RENDER_LINE_0)
    {
        // do nothing
    }

    // If end of frame, set vertical blank flag
    if (scanline_index >= VBLANK_LINE_0 && scanline_index <= POST_RENDER_LINE_F)
    {
        if (scanline_index == VBLANK_LINE_0 && cycle == 1)
        {
            status.data.in_v_blank = 1;
            if (control.data.generate_nmi)
            {
                nmi();
            }
        }
    }

    PixelComposition pixel_composition;
    compose_background(pixel_composition);
    compose_foreground(pixel_composition);
    composite_pixels(pixel_composition);

    sprite_screen->set_pixel(
        cycle - 1,
        scanline_index,
        get_color_from_palette_ram(pixel_composition));

    cycle++;
    if (mask.is_rendering())
    {
        if (cycle == 260 && scanline_index < POST_RENDER_LINE_0)
        {
            system_bus.scanline();
        }
    }

    if (cycle >= PPU_TICKS_PER_LINE)
    {
        cycle = 0;
        scanline_index++;
        if (scanline_index > POST_RENDER_LINE_F)
        {
            scanline_index = PRE_RENDER_SCANLINE;
            odd_frame = !odd_frame;
        }
    }
}

void PPU::render_background()
{
    auto is_cycle_zero = scanline_index == 0 && cycle == 0;
    if (is_cycle_zero && odd_frame && mask.is_rendering())
    {
        cycle = 1;
    }

    if (is_pre_render_scanline() && cycle == 1)
    {
        start_new_frame();
    }

    auto is_fetch_tile_cycle = cycle >= CYCLE_TILE_0 && cycle <= CYCLE_TILE_F;
    auto is_fetch_n_tile_cycle = cycle >= CYCLE_N_TILE_0 && cycle <= CYCLE_N_TILE_F;
    if (is_fetch_tile_cycle || is_fetch_n_tile_cycle)
    {
        work_visible_frame();
    }

    if (cycle == CYCLE_END_OF_SCANLINE && mask.is_rendering())
    {
        vram_addr.increment_scroll_y();
    }

    if (cycle == CYCLE_END_OF_SCANLINE)
    {
        render();
    }

    if (cycle == CYCLE_TILE_F)
    {
        bg_info.load_shifters();
        if (mask.is_rendering())
        {
            vram_addr.transfer_address_x(tram_addr);
        }
    }

    // Superfluous reads of tile id at end of scanline
    if (cycle == CYCLE_UNUSED_NT_FETCH_0 || cycle == CYCLE_UNUSED_NT_FETCH_1)
    {
        bg_info.next_tile_id = ppu_read(vram_addr.nametable_address());
    }

    auto is_cycle_pre_render_v_update =
        cycle >= CYCLE_PRE_RENDER_V_UPDATE_0 &&
        cycle <= CYCLE_PRE_RENDER_V_UPDATE_F;
    if (is_pre_render_scanline() && is_cycle_pre_render_v_update)
    {
        if (mask.is_rendering())
        {
            vram_addr.transfer_address_y(tram_addr);
        }
    }
}

void PPU::start_new_frame()
{
    status.data.in_v_blank = 0;

    status.data.sprite_overflow = 0;

    status.data.sprite_0_hit = 0;

    sprite_shifter_pattern_lo = {0};
    sprite_shifter_pattern_hi = {0};
}

void PPU::work_visible_frame()
{
    update_shifters();

    switch ((cycle - 1) % 8)
    {
    case 0:
        bg_info.load_shifters();

        bg_info.next_tile_id = ppu_read(NAMETABLE_SPACE_OFFSET | (vram_addr.reg & NAMETABLE_MASK));
        break;

    case 2:
        fetch_next_bg_tile_attrib();
        break;

    case 4:
        set_next_tile_addr_byte(bg_info.next_tile_lsb, 0);
        break;

    case 6:
        set_next_tile_addr_byte(bg_info.next_tile_msb, 8);
        break;

    case 7:
        if (mask.is_rendering())
        {
            vram_addr.increment_scroll_x();
        }
        break;
    }
}

void PPU::update_shifters()
{
    if (mask.data.show_background)
    {
        bg_info.update_shifters();
    }

    if (mask.data.show_sprites && cycle >= 1 && cycle <= CYCLE_TILE_F)
    {
        for (auto idx = 0; idx < sprite_count; idx++)
        {
            if (sprite_scanline[idx].x_pos() > 0)
            {
                sprite_scanline[idx].x_pos()--;
            }
            else
            {
                sprite_shifter_pattern_lo[idx] <<= 1;
                sprite_shifter_pattern_hi[idx] <<= 1;
            }
        }
    }
}

void PPU::fetch_next_bg_tile_attrib()
{
    uint16_t attrib_addr = vram_addr.attribute_address();
    logger::debug("PPU READ, FETCH NEXT BG TILE ATTRIB {:04X}", attrib_addr);
    bg_info.next_tile_attrib = ppu_read(attrib_addr);

    if (vram_addr.data.coarse_y & 0x02)
    {
        bg_info.next_tile_attrib >>= 4;
    }
    if (vram_addr.data.coarse_x & 0x02)
    {
        bg_info.next_tile_attrib >>= 2;
    }
    bg_info.next_tile_attrib &= 0x03;
}

void PPU::set_next_tile_addr_byte(uint8_t& next_tile_byte, uint8_t plane_offset)
{
    uint16_t tile_addr_byte = control.data.background_pattern_table << 12;
    tile_addr_byte += static_cast<uint16_t>(bg_info.next_tile_id) << 4;
    tile_addr_byte += vram_addr.data.fine_y + plane_offset;
    next_tile_byte = ppu_read(tile_addr_byte);
}

void PPU::render_foreground()
{
    if (cycle == CYCLE_TILE_F && scanline_index >= 0)
    {
        // We've reached the end of a visible scanline. It is now time to determine which
        // sprites are visible on the next scanline, and preload this info into buffers that we
        // can work with while the scanline scans the row.

        // Firstly, clear out the sprite memory. This memory is used to store the sprites to be
        // rendered. It is not the OAM.
        std::memset(sprite_scanline.data(), 0xFF, sizeof(sprite_scanline));

        // The NES supports a maximum number of sprites per scanline. Nominally this is 8 or
        // fewer sprites. This is why in some games you see sprites flicker or disappear when
        // the scene gets busy.
        sprite_count = 0;

        // Secondly, clear out any residual information in sprite pattern shifters
        sprite_shifter_pattern_lo = {0};
        sprite_shifter_pattern_hi = {0};

        evaluate_visible_sprites();
    }
    if (cycle == 340)
    {
        prepare_visible_sprites();
    }
}

void PPU::evaluate_visible_sprites()
{
    uint8_t oam_entry_idx = 0;

    sprite_0_hit_possible = false;

    while (oam_entry_idx < OAM_ENTRY_COUNT && sprite_count <= SPRITE_MAX_COUNT)
    {
        auto& oam_entry = object_attribute_memory.entry(oam_entry_idx);
        // N.B. conversion to signed
        int16_t diff = static_cast<int16_t>(scanline_index - static_cast<int16_t>(oam_entry.y_pos()));

        auto sprite_size = control.data.sprite_size ? 16 : 8;
        auto diff_in_range = diff >= 0 && diff < sprite_size;
        if (diff_in_range && sprite_count < 8)
        {
            if (sprite_count < 8)
            {
                auto zero_idx = oam_entry_idx == 0;
                sprite_0_hit_possible = zero_idx || sprite_0_hit_possible;

                std::memcpy(&sprite_scanline[sprite_count], &oam_entry, sizeof(oam_entry));
            }
            sprite_count++;
        }
        oam_entry_idx++;
    }

    status.data.sprite_overflow = sprite_count >= 8;
}

auto flipbyte(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
};

void PPU::prepare_visible_sprites()
{
    for (uint8_t idx = 0; idx < sprite_count; idx++)
    {
        uint8_t sprite_pattern_bits_lo{};
        uint8_t sprite_pattern_bits_hi{};
        uint16_t sprite_pattern_addr_lo{};
        uint16_t sprite_pattern_addr_hi{};

        auto unflipped = sprite_scanline[idx].attributes() & 0x80;
        auto size_8x8 = !control.data.sprite_size;
        if (size_8x8)
        {
            auto row_x = scanline_index - sprite_scanline[idx].y_pos();
            auto row = !unflipped ? row_x : 7 - row_x;
            sprite_pattern_addr_lo = control.data.sprite_pattern_table << 12;
            sprite_pattern_addr_lo |= sprite_scanline[idx].id() << 4;
            sprite_pattern_addr_lo |= row;
        }
        else
        {
            auto cell = (scanline_index - sprite_scanline[idx].y_pos() < 8) ? 0 : 1;
            auto row = (scanline_index - sprite_scanline[idx].y_pos()) & 0x07;
            auto flipped_8x16 = unflipped;
            if (flipped_8x16)
            {
                row = (7 - (scanline_index - sprite_scanline[idx].y_pos())) & 0x07;
                cell = scanline_index - sprite_scanline[idx].y_pos() < 8 ? 1 : 0;
            }
            sprite_pattern_addr_lo = (sprite_scanline[idx].id() & 0x01) << 12;
            sprite_pattern_addr_lo |= ((sprite_scanline[idx].id() & 0xFE) + cell) << 4;
            sprite_pattern_addr_lo |= row;
        }

        sprite_pattern_addr_hi = sprite_pattern_addr_lo + 8;

        sprite_pattern_bits_lo = ppu_read(sprite_pattern_addr_lo);
        sprite_pattern_bits_hi = ppu_read(sprite_pattern_addr_hi);

        if (sprite_scanline[idx].flip_h())
        {
            sprite_pattern_bits_lo = flipbyte(sprite_pattern_bits_lo);
            sprite_pattern_bits_hi = flipbyte(sprite_pattern_bits_hi);
        }

        sprite_shifter_pattern_lo[idx] = sprite_pattern_bits_lo;
        sprite_shifter_pattern_hi[idx] = sprite_pattern_bits_hi;
    }
}

void PPU::compose_background(PixelComposition& pixel_composition)
{
    pixel_composition.bg_pixel = 0x00;
    pixel_composition.bg_palette = 0x00;

    if (mask.data.show_background)
    {
        if (mask.data.show_bg_left || (cycle >= 9))
        {
            uint16_t bit_mux = 0x8000 >> fine_x;

            uint8_t p0_pixel = (bg_info.shifter_pattern_lo & bit_mux) > 0;
            uint8_t p1_pixel = (bg_info.shifter_pattern_hi & bit_mux) > 0;

            pixel_composition.bg_pixel = (p1_pixel << 1) | p0_pixel;

            uint8_t bg_pal0 = (bg_info.shifter_attrib_lo & bit_mux) > 0;
            uint8_t bg_pal1 = (bg_info.shifter_attrib_hi & bit_mux) > 0;
            pixel_composition.bg_palette = (bg_pal1 << 1) | bg_pal0;
        }
    }
}

void PPU::compose_foreground(PixelComposition& pixel_composition)
{
    if (!mask.data.show_sprites)
    {
        return;
    }

    if (!(mask.data.show_sprites_left || (cycle >= 9)))
    {
        return;
    }

    sprite_0_being_rendered = false;

    for (uint8_t idx = 0; idx < sprite_count; idx++)
    {
        if (sprite_scanline[idx].x_pos() != 0)
        {
            continue;
        }

        uint8_t fg_pixel_lo = (sprite_shifter_pattern_lo[idx] & 0x80) > 0;
        uint8_t fg_pixel_hi = (sprite_shifter_pattern_hi[idx] & 0x80) > 0;
        pixel_composition.fg_pixel = (fg_pixel_hi << 1) | fg_pixel_lo;

        pixel_composition.fg_palette = (sprite_scanline[idx].attributes() & 0x03) + 0x04;
        pixel_composition.fg_priority = (sprite_scanline[idx].attributes() & 0x20) == 0;

        if (pixel_composition.fg_pixel != 0)
        {
            sprite_0_being_rendered = sprite_0_being_rendered || (idx == 0);
            break;
        }
    }
}

void PPU::composite_pixels(PixelComposition& pixel_composition)
{
    const auto& bg_pix_gt_zero = pixel_composition.bg_pixel > 0;
    const auto& fg_pix_gt_zero = pixel_composition.fg_pixel > 0;
    const auto& fg_pixel = pixel_composition.fg_pixel;
    const auto& bg_pixel = pixel_composition.bg_pixel;
    const auto& fg_pal = pixel_composition.fg_palette;
    const auto& bg_pal = pixel_composition.bg_palette;

    pixel_composition.pixel = bg_pix_gt_zero * bg_pixel + fg_pix_gt_zero * fg_pixel;
    pixel_composition.palette = bg_pix_gt_zero * bg_pal + fg_pix_gt_zero * fg_pal;

    auto maybe_collision = bg_pix_gt_zero && fg_pix_gt_zero;
    if (!maybe_collision)
    {
        return;
    }

    auto fg_pri = pixel_composition.fg_priority;
    pixel_composition.pixel = fg_pri * fg_pixel + !fg_pri * bg_pixel;
    pixel_composition.palette = fg_pri * fg_pal + !fg_pri * bg_pal;

    auto maybe_zero_hit = sprite_0_hit_possible && sprite_0_being_rendered;
    if (maybe_zero_hit && mask.is_rendering())
    {
        // The left edge of the screen has specific switches to control
        // its appearance. This is used to smooth inconsistencies when
        // scrolling (since sprites x coord must be >= 0)
        auto show_left = mask.data.show_bg_left || mask.data.show_sprites_left;
        auto is_hit_x = !show_left && cycle >= 9 && cycle < 258;
        if (is_hit_x || (cycle >= 1 && cycle < 258))
        {
            status.data.sprite_0_hit = 1;
        }
    }
}

bool PPU::init_sdl()
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

const Sprite& PPU::get_sprite_screen() const {
    return *sprite_screen;
}

void PPU::render()
{
    if (!is_initialized)
    {
        init_sdl();
        auto depth = 32;
        RenderedImage = SDL_CreateRGBSurface(
            0,
            NTSC_WIDTH,
            NTSC_HEIGHT,
            depth,
            0xFF000000,
            0x00FF0000,
            0x0000FF00,
            0x000000FF);
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
    }

    // SDL_LockSurface(RenderedImage);
    auto pixel_ptr = static_cast<uint32_t*>(RenderedImage->pixels);
    std::memcpy(
        pixel_ptr,
        sprite_screen->col_data.data(),
        sizeof(uint32_t) * sprite_screen->width * sprite_screen->height);
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

Pixel& PPU::get_color_from_palette_ram(const PixelComposition& pixel_composition)
{
    // This is a convenience function that takes a specified palette and pixel
    // index and returns the appropriate screen color.
    // "0x3F00"       - Offset into PPU addressable range where palettes are stored
    // "palette << 2" - Each palette is 4 bytes in size
    // "pixel"        - Each pixel index is either 0, 1, 2 or 3
    // "& 0x3F"       - Stops us reading beyond the bounds of the palScreen array
    auto read_address = 0x3F00 + (pixel_composition.palette << 2) + pixel_composition.pixel;
    return palette_screen[ppu_read(read_address) & 0x3F];
}

} // namespace nes
