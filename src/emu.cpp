#include "logger/logger.hpp"
#include "option_parser/option_parser.hpp"
#include "nes.hpp"
#include "cartridge/cartridge.hpp"

#include "mos6502_config.hpp"

using logger::LogLevel;

std::optional<nes::Cartridge> load_rom(const std::string& filename)
{
    fmt::print("using rom {}\n", filename);
    nes::Cartridge cart{};
    if (cart.load(filename))
    {
        return cart;
    }
    return {};
}

void version()
{
    fmt::print(stdout, "{} {}\n", PROJECT_NAME, PROJECT_VER);
}

int main(int argc, char** argv)
{
    // logger::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    logger::set_pattern("[%H:%M:%S] [%^-%L-%$] %v");
    logger::set_level(LogLevel::Error);
    option_parser::OptionParser opts(argc, argv, "mos6502", "MOS6502 emulator");

    auto flags_added = opts.add_flag_set({
        {"v", "version", "Param version", version},
        {"h", "help", "Print usage", opts.create_help_callback(version)}
    });

    if (flags_added.is_ok())
    {
        flags_added = opts.add_argument<std::string>("r", "rom", "ROM file to load");
    }

    if (flags_added.is_ok())
    {
        flags_added = opts.add_argument<uint16_t>("i", "init-addr", "Initial address");
    }

    if (flags_added.is_ok())
    {
        flags_added = opts.add_argument<std::string>("l", "log-level", "Log level");
    }

    if (flags_added.is_err())
    {
        auto err = flags_added.get_err().format();
        fmt::print(stderr, "Failed to add flags {}\n", err);
        logger::log(LogLevel::Critical, "Failed to add flags: {}", err);
        std::exit(1);
    }

    auto parsed_res = opts.parse();

    if (parsed_res.is_err())
    {
        auto err = parsed_res.get_err().format();
        fmt::print(stderr, "Failed to parse arguments: {}\n", err);
        logger::log(LogLevel::Critical, "Failed to parse arguments: {}", err);
        std::exit(1);
    }

    if (opts.handle_flag("help"))
    {
        std::exit(0);
    }

    opts.handle_flag("version");

    if (auto log_level_str = opts.flag_value<std::string>("log-level"))
    {
        auto log_level = logger::logLevelFromStr(*log_level_str);
        if (log_level) {
            logger::set_level(*log_level);
        }
    }

    if (auto rom_name = opts.flag_value<std::string>("rom"))
    {
        auto cart = load_rom(*rom_name);
        if (!cart)
        {
            logger::log(LogLevel::Error, "Failed to load {}", *rom_name);
            std::exit(1);
        }
        nes::NES nes(std::move(*cart));

        if (auto init_addr = opts.flag_value<uint16_t>("init-addr"))
        {
            nes.cpu.reset();
            nes.cpu.pc = *init_addr;
            nes.cpu.heavy_diagnostics = true;
            logger::log(LogLevel::Debug, "Using init address {:04X}", nes.cpu.pc);
            while (true)
            {
                nes.cpu.step();
            }
        }
        else
        {
            nes.run();
        }
    }

    return 0;
}
