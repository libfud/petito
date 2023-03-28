#include "logger/logger.hpp"
#include "option_parser/option_parser.hpp"
#include "mos6502.hpp"
#include "nes.hpp"
#include "cartridge.hpp"

#include "mos6502_config.hpp"

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
    logger::set_level(logger::LogLevel::Debug);
    option_parser::OptionParser opts(argc, argv, "mos6502", "MOS6502 emulator");

    auto flags_added = opts.add_flag_set({
        {"v", "version", "Param version", version},
        {"h", "help", "Print usage", opts.create_help_callback(version)}
    });

    if (flags_added.is_ok())
    {
        flags_added = opts.add_argument<std::string>("r", "rom", "ROM file to load");
    }

    if (flags_added.is_err())
    {
        auto err = flags_added.get_err().format();
        fmt::print(stderr, "Failed to add flags {}\n", err);
        logger::log(logger::LogLevel::Critical, "Failed to add flags: {}", err);
        std::exit(1);
    }

    auto parsed_res = opts.parse();

    if (parsed_res.is_err())
    {
        auto err = parsed_res.get_err().format();
        fmt::print(stderr, "Failed to parse arguments: {}\n", err);
        logger::log(logger::LogLevel::Critical, "Failed to parse arguments: {}", err);
        std::exit(1);
    }

    if (opts.handle_flag("help"))
    {
        std::exit(0);
    }

    opts.handle_flag("version");

    if (auto rom_name = opts.flag_value<std::string>("rom"))
    {
        logger::set_level(logger::LogLevel::Trace);
        auto cart = load_rom(*rom_name);
        if (!cart)
        {
            logger::log(logger::LogLevel::Error, "Failed to load {}", *rom_name);
            std::exit(1);
        }
        nes::NES nes(std::move(*cart));
        logger::set_level(logger::LogLevel::Debug);
        nes.run();
    }

    return 0;
}
