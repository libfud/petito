#include "ppu.hpp"
#include "../logger/logger.hpp"
#include "../system_bus.hpp"

namespace nes {

using logger::LogLevel;
using logger::log;

auto flipbyte(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
};

PPU::PPU(NesSystemBus& system_bus, VirtualScreen& virtual_screen) :
    system_bus{system_bus},
    virtual_screen{virtual_screen},
    sprite_memory(64 * 4),
    scanline_sprites(8),
    pipeline_state{PpuState::VerticalBlank},
    picture_buffer(
        SCANLINE_VISIBLE_DOTS,
        std::vector<sf::Color>(VISIBLE_SCANLINES, sf::Color::Magenta))
{
    scanline_sprites.reserve(8);
    scanline_sprites.resize(0);
}

void PPU::reset()
{
    long_sprites = false;
    generate_interrupt = false;
    greyscale_mode = false;
    vblank = false;
    sprite_overflow = false;
    show_background = true;
    show_sprites = true;
    even_frame = true;
    first_write = true;

    bg_page = CharacterPage::Low;
    sprite_page = CharacterPage::Low;

    data_address = 0;
    cycle = 0;
    scanline = 0;
    sprite_data_address = 0;
    fine_x_scroll = 0;
    temp_address = 0;

    data_address_increment = 1;
    pipeline_state = PpuState::PreRender;
    scanline_sprites.reserve(8);
    scanline_sprites.resize(0);
}

uint8_t PPU::read_palette(uint8_t palette_address)
{
    auto mapped_address = palette_address;
    if (palette_address >= 0x10 && palette_address % 4 == 0)
    {
        mapped_address = palette_address & 0x0F;
    }
    return palette[mapped_address];
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

void PPU::run(int cpu_cycles)
{
    int steps = cpu_cycles * PPU_CLOCKS_PER_CPU_CLOCK;
    for (auto idx = 0; idx < steps; ++idx)
    {
        step();
        system_bus.ppu_clock++;
    }
}

void PPU::step()
{
    switch (pipeline_state)
    {
    case PpuState::PreRender:
        prerender();
        break;
    case PpuState::Render:
        render();
        break;
    case PpuState::PostRender:
        post_render();
        break;
    case PpuState::VerticalBlank:
        render_vblank();
        break;
    default:
        logger::critical("Invalid ppu pipeline state");
    }

    ++cycle;
}

void PPU::prerender()
{
    if (cycle == 1)
    {
        vblank = false;
        sprite_0_hit = false;
    }
    else if (cycle == SCANLINE_VISIBLE_DOTS + 2 && show_background && show_sprites)
    {
        //Set bits related to horizontal position
        data_address &= ~0x41f; //Unset horizontal bits
        data_address |= temp_address & 0x41f; //Copy
    }
    else if (cycle > 280 && cycle <= 304 && show_background && show_sprites)
    {
        //Set vertical bits
        data_address &= ~0x7be0; //Unset bits related to horizontal
        data_address |= temp_address & 0x7be0; //Copy
    }

    //if rendering is on, every other frame is one cycle shorter
    if (cycle >= SCANLINE_END_CYCLE - (!even_frame && show_background && show_sprites))
    {
        logger::warn("Transition to render");
        pipeline_state = PpuState::Render;
        cycle = 0;
        scanline = 0;
    }

    // add IRQ support for MMC3
    if (cycle == 260 && show_background && show_sprites)
    {
        system_bus.scanline();
    }
}

void PPU::render()
{
    if (cycle > 0 && cycle <= SCANLINE_VISIBLE_DOTS)
    {
        uint8_t bg_color = 0;
        uint8_t sprite_color = 0;
        bool bg_opaque = false;
        bool sprite_opaque = true;
        bool sprite_foreground = false;

        const int x = cycle - 1;
        const int y = scanline;

        if (show_background)
        {
            render_background(bg_color, bg_opaque);
        }

        if (show_sprites && (!hide_edge_sprites || x >= 8))
        {
            render_sprites(sprite_color, sprite_opaque, sprite_foreground, bg_opaque);
        }

        uint8_t palette_address = bg_color;

        if ((!bg_opaque && sprite_opaque) || (bg_opaque && sprite_opaque && sprite_foreground))
        {
            palette_address = sprite_color;
        }
        else if (!bg_opaque && !sprite_opaque)
        {
            palette_address = 0;
        }
        //else bg_color

        picture_buffer[x][y] = sf::Color(COLORS[read_palette(palette_address)]);
    }
    else if (cycle == SCANLINE_VISIBLE_DOTS + 1 && show_background)
    {
        //Shamelessly copied from nesdev wiki
        if ((data_address & 0x7000) != 0x7000)  // if fine Y < 7
        {
            data_address += 0x1000;              // increment fine Y
        }
        else
        {
            data_address &= ~0x7000;             // fine Y = 0
            int y = (data_address & 0x03E0) >> 5;    // let y = coarse Y
            if (y == 29)
            {
                // coarse Y = 0
                y = 0;
                // switch vertical nametable
                data_address ^= 0x0800;
            }
            else if (y == 31)
            {
                // coarse Y = 0, nametable not switched
                y = 0;
            }
            else
            {
                // increment coarse Y
                y += 1;
            }
            data_address = (data_address & ~0x03E0) | (y << 5);
            // put coarse Y back into data_address
        }
    }
    else if (cycle == SCANLINE_VISIBLE_DOTS + 2 && show_background && show_sprites)
    {
        //Copy bits related to horizontal position
        data_address &= ~0x41f;
        data_address |= temp_address & 0x41f;
    }

    // if (cycle > 257 && cycle < 320) {
    //     sprite_data_address = 0;
    // }

    // add IRQ support for MMC3
    if (cycle==260 && show_background && show_sprites)
    {
        system_bus.scanline();
    }

    if (cycle >= SCANLINE_END_CYCLE)
    {
        //Find and index sprites that are on the next Scanline
        //This isn't where/when this indexing, actually copying in 2C02 is done
        //but (I think) it shouldn't hurt any games if this is done here

        scanline_sprites.resize(0);

        int range = 8;
        if (long_sprites)
        {
            range = 16;
        }

        std::size_t j = 0;
        for (std::size_t i = sprite_data_address / 4; i < 64; ++i)
        {
            auto diff = (scanline - sprite_memory[i * 4]);
            if (0 <= diff && diff < range)
            {
                if (j >= 8)
                {
                    sprite_overflow = true;
                    break;
                }
                scanline_sprites.push_back(i);
                ++j;
            }
        }

        ++scanline;
        cycle = 0;
    }

    if (scanline >= VISIBLE_SCANLINES)
    {
        logger::warn("Transition to post render");
        pipeline_state = PpuState::PostRender;
    }
}

void PPU::render_background(uint8_t& bg_color, bool& bg_opaque)
{
    const int x = cycle - 1;

    auto x_fine = (fine_x_scroll + x) % 8;
    if (!hide_edge_background || x >= 8)
    {
        //fetch tile
        auto addr = 0x2000 | (data_address & 0x0FFF); //mask off fine y
        //auto addr = 0x2000 + x / 8 + (y / 8) * (ScanlineVisibleDots / 8);
        uint8_t tile = system_bus.read(addr);

        //fetch pattern
        //Each pattern occupies 16 bytes, so multiply by 16
        addr = (tile * 16) + ((data_address >> 12/*y % 8*/) & 0x7); //Add fine y
        //set whether the pattern is in the high or low page
        addr |= static_cast<int>(bg_page) << 12;
        //Get the corresponding bit determined by (8 - x_fine) from the right
        bg_color = (system_bus.read(addr) >> (7 ^ x_fine)) & 1; //bit 0 of palette entry
        bg_color |= ((system_bus.read(addr + 8) >> (7 ^ x_fine)) & 1) << 1; //bit 1

        bg_opaque = bg_color; //flag used to calculate final pixel with the sprite pixel

        //fetch attribute and calculate higher two bits of palette
        addr = 0x23C0
            | (data_address & 0x0C00)
            | ((data_address >> 4) & 0x38)
            | ((data_address >> 2) & 0x07);
        auto attribute = system_bus.read(addr);
        int shift = ((data_address >> 4) & 4) | (data_address & 2);
        //Extract and set the upper two bits for the color
        bg_color |= ((attribute >> shift) & 0x3) << 2;
    }
    //Increment/wrap coarse X
    if (x_fine == 7)
    {
        if ((data_address & 0x001F) == 31) // if coarse X == 31
        {
            data_address &= ~0x001F;          // coarse X = 0
            data_address ^= 0x0400;           // switch horizontal nametable
        }
        else
        {
            data_address += 1;                // increment coarse X
        }
    }
}

void PPU::render_sprites(
    uint8_t& sprite_color,
    bool& sprite_opaque,
    bool& sprite_foreground,
    const bool& bg_opaque)
{
    const int x = cycle - 1;
    const int y = scanline;

    for (auto i : scanline_sprites)
    {
        uint8_t spr_x = sprite_memory[i * 4 + 3];

        if (0 > x - spr_x || x - spr_x >= 8)
        {
            continue;
        }

        uint8_t spr_y = sprite_memory[i * 4 + 0] + 1;
        uint8_t tile = sprite_memory[i * 4 + 1];
        uint8_t attribute = sprite_memory[i * 4 + 2];

        int length = (long_sprites) ? 16 : 8;

        int x_shift = (x - spr_x) % 8;
        int y_offset = (y - spr_y) % length;

        if ((attribute & 0x40) == 0) //If NOT flipping horizontally
        {
            x_shift ^= 7;
        }
        if ((attribute & 0x80) != 0) //IF flipping vertically
        {
            y_offset ^= (length - 1);
        }

        uint16_t addr = 0;

        if (!long_sprites)
        {
            addr = tile * 16 + y_offset;
            if (sprite_page == CharacterPage::High) addr += 0x1000;
        }
        else //8x16 sprites
        {
            //bit-3 is one if it is the bottom tile of the sprite,
            //multiply by two to get the next pattern
            y_offset = (y_offset & 7) | ((y_offset & 8) << 1);
            addr = (tile >> 1) * 32 + y_offset;
            addr |= (tile & 1) << 12; //Bank 0x1000 if bit-0 is high
        }

        sprite_color |= (system_bus.read(addr) >> (x_shift)) & 1; //bit 0 of palette entry
        sprite_color |= ((system_bus.read(addr + 8) >> (x_shift)) & 1) << 1; //bit 1

        sprite_opaque = sprite_color;
        if (!sprite_opaque)
        {
            sprite_color = 0;
            continue;
        }

        sprite_color |= 0x10; //Select sprite palette
        sprite_color |= (attribute & 0x3) << 2; //bits 2-3

        sprite_foreground = !(attribute & 0x20);

        //Sprite-0 hit detection
        if (!sprite_0_hit && show_background && i == 0 && sprite_opaque && bg_opaque)
        {
            sprite_0_hit = true;
        }

        break; //Exit the loop now since we've found the highest priority sprite
    }
}

void PPU::post_render()
{
    if (cycle >= SCANLINE_END_CYCLE)
    {
        ++scanline;
        cycle = 0;
        pipeline_state = PpuState::VerticalBlank;
        logger::warn("Transition to vblank");
        for (std::size_t x = 0; x < picture_buffer.size(); ++x)
        {
            for (std::size_t y = 0; y < picture_buffer[0].size(); ++y)
            {
                virtual_screen.setPixel(x, y, picture_buffer[x][y]);
            }
        }
    }
}

void PPU::render_vblank()
{
    // logger::warn("Render vblank");
    if (cycle == 1 && scanline == VISIBLE_SCANLINES + 1)
    {
        // logger::warn("Render vblank cycle 1, scanline = {}, cycle = {}", scanline, cycle);
        vblank = true;
        if (generate_interrupt)
        {
            // vblankCallback();
            nmi();
        }
    }

    if (cycle >= SCANLINE_END_CYCLE)
    {
        ++scanline;
        cycle = 0;
        // logger::warn(
        //     "Render vblank, reset cycle, increment scanline = {}, cycle = {}",
        //     scanline,
        //     cycle);
    }

    if (scanline >= FRAME_END_SCANLINE)
    {
        logger::warn("Transition to prerender");
        pipeline_state = PpuState::PreRender;
        scanline = 0;
        even_frame = !even_frame;
    }
}

uint8_t PPU::read_oam(uint8_t addr)
{
    return sprite_memory[addr];
}

void PPU::write_oam(uint8_t addr, uint8_t value)
{
    sprite_memory[addr] = value;
}

void PPU::dma()
{
#if 0
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
#endif
}

#if 0
uint16_t PPU::cpu_map_address(uint16_t address)
{
    if (address == OAM_DMA)
    {
        return address;
    }
    auto mapped_address = (address - PPU_REG_HIGH) & PPU_ADDR_MASK;
    return mapped_address;
}
#endif

uint8_t PPU::cpu_read(uint16_t unmapped_address)
{
    /*
    auto clock_diff = system_bus.ppu_clock - latch_clock;
    if (clock_diff > (PPU_TICKS_PER_SEC / 2))
    {
        address_latch = 0x00;
        // ppu_data_buffer = 0x00;
    }
    */
    // uint8_t data = address_latch;
    // uint8_t data = ppu_data_buffer;
    uint16_t address = unmapped_address;
    if (unmapped_address >= 0x2000 && unmapped_address <= 0x3FFF)
    {
        address = unmapped_address & 0x2003;
    }
    uint8_t data = 0;
    switch (address)
    {
    case PPU_CTRL:
        break;
    case PPU_MASK:
        break;
    case PPU_STATUS:
        data = sprite_overflow << 5 | sprite_0_hit << 6 << vblank << 7;
        vblank = false;
        first_write = true;
        break;
    case OAM_ADDR:
        break;
    case OAM_DATA:
        if (first_write)
        {
            temp_address &= ~0xff00; //Unset the upper byte
            temp_address |= (address & 0x3f) << 8;
            first_write = false;
        }
        else
        {
            temp_address &= ~0xff; //Unset the lower byte;
            temp_address |= address;
            data_address = temp_address;
            first_write = true;
        }
        break;
    case PPU_SCROLL:
        break;
    case PPU_ADDR:
        break;
    case PPU_DATA:
        system_bus.read(data_address);
        break;
    case OAM_DMA:
        data = sprite_memory[address];
        break;
    default:
        log(LogLevel::Critical, "Invalid write to PPU {:04X}", address);
        break;
    }
    return data;
}

void PPU::cpu_write(uint16_t unmapped_address, uint8_t data)
{
    uint16_t address = unmapped_address;
    if (unmapped_address >= 0x2000 && unmapped_address <= 0x3FFF)
    {
        address = unmapped_address & 0x2003;
    }
    switch (address)
    {
    case PPU_CTRL:
        generate_interrupt = data & 0x80;
        long_sprites = data & 0x20;
        bg_page = static_cast<CharacterPage>(!!(data & 0x10));
        sprite_page = static_cast<CharacterPage>(!!(data & 0x08));
        break;
    case PPU_MASK:
        greyscale_mode = data & 0x01;
        hide_edge_background = !(data & 0x02);
        hide_edge_sprites = !(data & 0x04);
        show_background = data & 0x08;
        show_sprites = data & 0x10;
        break;
    case PPU_STATUS:
        break;
    case OAM_ADDR:
        // oam_address = data;
        break;
    case OAM_DATA:
        // object_attribute_memory.write(data);
        break;
    case PPU_SCROLL:
        break;
    case PPU_ADDR:
        break;
    case PPU_DATA:
        break;
    case OAM_DMA:
        dma();
        break;
    default:
        logger::critical("Invalid read from PPU {:04X}", address);
        break;
    }
}

} // namespace nes
