#include <algorithm>
#include <exception>
#include <fstream>
#include <iterator>
#include <filesystem>

#include "nes.hpp"
#include "logger/logger.hpp"

namespace nes {

NES::NES(Cartridge&& cart, int32_t cpu_clock_rate) :
    cpu{system_bus, cpu_clock_rate},
    cart{std::move(cart)},
    apu{},
    ppu{system_bus, virtual_screen},
    system_bus{this->cart, ppu, apu},
    virtual_screen{},
    screen_scale{3.0f},
    diagnostic_msg{},
    debug_msg(static_cast<const char*>(static_cast<void*>(&system_bus.cart.prg_ram[4])), 128)
{
    system_bus.init();
}

NES::~NES() {}

void NES::set_diagnostics(std::string diag_msg)
{
    diagnostic_msg = diag_msg;
}

void NES::reset()
{
    cpu.reset();
    ppu.reset();
}

void NES::run(bool perform_reset)
{
    /*
    window.create(
        sf::VideoMode(NTSC_WIDTH * screen_scale, NTSC_HEIGHT * screen_scale),
        "SimpleNES",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setVerticalSyncEnabled(true);
    */
    virtual_screen.create(NTSC_WIDTH, NTSC_HEIGHT, screen_scale, sf::Color::White);

    if (perform_reset)
    {
        reset();
    }
    uint8_t idx = 0;
    while (true)
    {
        step();
        idx++;
        if (idx % 8 == 0)
        {
            diagnostics();
        }
    }
}

void NES::run_until(const std::function<bool(const NES& nes)>& predicate)
{
    reset();
    while (predicate(*this))
    {
        step();
    }
}

void NES::run_diag()
{
    enum class NesState {
        Running,
        Passed,
        Failed
    };
    NesState state = NesState::Running;
    int64_t cycles = 0;
    auto terminator = [&](const NES& nes){
        auto has_debug_msg = nes.diagnostics();
        if (!has_debug_msg)
        {
            return true;
        }
        if (debug_msg.find(diagnostic_msg) != std::string::npos)
        {
            fmt::print("Passed: Step {}, diag={}\n", cycles, debug_msg);
            state = NesState::Passed;
            return false;
        }
        else if (debug_msg.find("failed") != std::string::npos)
        {
            fmt::print("Failed: Step {}, diag={}\n", cycles, debug_msg);
            state = NesState::Failed;
            return false;
        }
        else
        {
            state = NesState::Running;
        }

        cycles++;
        if (cycles % 100000 == 0)
        {
            logger::debug("Step {}, diag={}", cycles, debug_msg);
        }
        if (cycles > 10000000000 || cycles < 0)
        {
            return state == NesState::Running;
        }

        return true;
    };
    logger::debug("Running until msg is \"failed\" or \"{}\"", diagnostic_msg);
    run_until(terminator);
}

void NES::step()
{
    auto cycles = cpu.step();
    static_cast<void>(cycles);
    // ppu.run(cycles);
}

auto NES::diagnostics() const -> bool
{
    constexpr auto DEBUG_STATUS_ADDRESS = 0x6000;
    uint8_t status = cpu.debug_read(DEBUG_STATUS_ADDRESS);

    bool has_debug_msg = false;
    if (status == 0x80)
    {
        if (debug_msg.size() > 0)
        {
            has_debug_msg = true;
            logger::debug(
                "Test in progress {:02X} {:02X} {:02X}\nmessage=\n{}",
                system_bus.cart.prg_ram[1],
                system_bus.cart.prg_ram[2],
                system_bus.cart.prg_ram[3],
                debug_msg
            );
        }
    }
    return has_debug_msg;
}

}
