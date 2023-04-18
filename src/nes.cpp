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
    diagnostic_msg{}
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
        auto diag_msg = nes.diagnostics();
        std::transform(
            diag_msg.begin(),
            diag_msg.end(),
            diag_msg.begin(),
            [](unsigned char c){ return std::tolower(c); });
        if (diag_msg.find(diagnostic_msg) != std::string::npos)
        {
            fmt::print("Passed: Step {}, diag={}\n", cycles, diag_msg);
            state = NesState::Passed;
            return false;
        }
        else if (diag_msg.find("failed") != std::string::npos)
        {
            fmt::print("Failed: Step {}, diag={}\n", cycles, diag_msg);
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
            logger::debug("Step {}, diag={}", cycles, diag_msg);
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

std::string NES::diagnostics() const
{
    uint8_t status = cpu.debug_read(0x6000);

    if (status == 0x80)
    {
        std::vector<char> msg_buf(256, 0);
        memcpy(
            msg_buf.data(),
            &system_bus.cart.prg_ram[4],
            sizeof(msg_buf));
        std::string message(msg_buf.data());
        if (message.size() > 0)
        {
            logger::debug(
                "Test in progress {:02X} {:02X} {:02X}\nmessage={}",
                system_bus.cart.prg_ram[1],
                system_bus.cart.prg_ram[2],
                system_bus.cart.prg_ram[3],
                message
            );
        }
        return message;
    }
    return std::string{""};
}

}
