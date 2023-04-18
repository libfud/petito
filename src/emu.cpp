#include "logger/logger.hpp"
#include "option_parser/option_parser.hpp"
#include "nes.hpp"
#include "cartridge/cartridge.hpp"

#include "mos6502_config.hpp"
#include "emu.hpp"

using logger::LogLevel;

using option_parser::OptionParser;

std::optional<nes::Cartridge> load_rom(const std::string& filename)
{
    logger::debug("Using rom {}\n", filename);
    nes::Cartridge cart{};
    if (cart.load(filename))
    {
        return cart;
    }
    return {};
}

void version() { fmt::print(stdout, "{} {}\n", PROJECT_NAME, PROJECT_VER); }

bool create_flags(OptionParser& opts)
{
    auto flags_added = opts.add_flag_set({
        {"v", "version", "Param version", version},
        {"h", "help", "Print usage", opts.create_help_callback(version)},
    });

    if (flags_added.is_ok())
    {
        flags_added = opts.add_argument<std::string>("r", "rom", "ROM file to load");
    }

    if (flags_added.is_ok())
    {
        flags_added = opts.add_argument<std::string>("l", "log-level", "Log level");
    }

    if (flags_added.is_ok())
    {
        flags_added = opts.add_argument<std::string>("d", "diagnostic", "Diagnostic mode");
    }

    if (flags_added.is_err())
    {
        auto err = flags_added.get_err().format();
        fmt::print(stderr, "Failed to add flags {}\n", err);
        logger::log(LogLevel::Critical, "Failed to add flags: {}", err);
        return false;
    }

    auto parsed_res = opts.parse();
    if (parsed_res.is_err())
    {
        auto err = parsed_res.get_err().format();
        fmt::print(stderr, "Failed to parse arguments: {}\n", err);
        logger::log(LogLevel::Critical, "Failed to parse arguments: {}", err);
        return false;
    }

    return true;
}

int main(int argc, char** argv)
{
    logger::set_pattern("%v");
    logger::set_level(LogLevel::Error);

    OptionParser opts(argc, argv, "mos6502", "MOS6502 emulator");
    if (!create_flags(opts))
    {
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
            logger::error("Failed to load {}", *rom_name);
            std::exit(1);
        }
        nes::NES nes(std::move(*cart));
        if (opts.has_flag("diagnostic"))
        {
            logger::debug("Using diagnostics");
            auto diag_msg = opts.flag_value<std::string>("diagnostic").value();
            nes.set_diagnostics(diag_msg);
            nes.run_diag();
        }
        else
        {
            nes.run();
        }
    }

    return 0;
}
