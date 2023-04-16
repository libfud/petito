#ifndef EMU_HPP
#define EMU_HPP

#include "cartridge/cartridge.hpp"
#include "option_parser/option_parser.hpp"

std::optional<nes::Cartridge> load_rom(const std::string& filename);

void version();

bool create_flags(option_parser::OptionParser& opts);

#endif
