#include <algorithm>
#include <exception>
#include <fstream>
#include <iterator>
#include <filesystem>

#include "cartridge.hpp"
#include "mapper_000.hpp"
#include "mapper_001.hpp"
#include "../logger/logger.hpp"

namespace nes {

namespace fs = std::filesystem;

bool Cartridge::load(const std::string& rom_name)
{
    if (!fs::exists(rom_name))
    {
        logger::error("No file with name {}.", rom_name);
        return false;
    }
    fs::path rom_path = rom_name;
    size_t rom_size = fs::file_size(rom_path);
    size_t min_size = NesHeader::HEADER_SIZE;
    size_t position = 0;
    if (rom_size < min_size)
    {
        logger::error(
            "Rom size={:08X} less than min_size (header) {:08X}",
            rom_size,
            min_size);
        return false;
    }

    std::ifstream rom_fstream(rom_path, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(rom_fstream), {});
    std::array<uint8_t, NesHeader::HEADER_SIZE> header_bytes{0};
    std::copy_n(buffer.begin(), sizeof(header_bytes), header_bytes.begin());

    if (auto opt_header = NesHeader::from_bytes(header_bytes))
    {
        header = *opt_header;
        position += sizeof(header_bytes);
    }
    else
    {
        logger::error("Failed to read header.");
        return false;
    }

    size_t prg_rom_size = header.prg_rom_size();
    size_t prg_ram_size = header.prg_ram_size();
    size_t chr_rom_size = header.chr_rom_size();
    size_t chr_ram_size = header.chr_ram_size();

    logger::debug("prg rom size {}", prg_rom_size);
    logger::debug("prg ram size {}", prg_ram_size);
    logger::debug("chr rom size {}", chr_rom_size);
    logger::debug("chr ram size {}", chr_ram_size);

    min_size += prg_rom_size;
    min_size += chr_rom_size;
    if (header.uses_trainer())
    {
        logger::debug("Using trainer for ROM");
        min_size += TRAINER_SIZE;
    }

    if (rom_size < min_size)
    {
        return false;
    }

    if (header.uses_trainer())
    {
        trainer.resize(TRAINER_SIZE);
        std::copy(buffer.begin() + position, buffer.begin() + TRAINER_SIZE, trainer.begin());
        position += TRAINER_SIZE;
    }

    prg_rom.clear();
    prg_rom.reserve(prg_rom_size);
    chr_rom.clear();
    chr_rom.reserve(chr_rom_size);

    prg_ram.resize(prg_ram_size);
    chr_ram.resize(chr_ram_size);

    logger::debug(
        "Reading 0x{:04X} bytes into prg_rom, starting at 0x{:04X}.",
        prg_rom_size,
        position);
    std::copy_n(buffer.begin() + position, prg_rom_size, std::back_inserter(prg_rom));
    position += prg_rom_size;

    logger::debug(
        "Reading 0x{:04X} bytes into chr_rom, starting at 0x{:04X}.",
        chr_rom_size,
        position);
    std::copy_n(buffer.begin() + position, chr_rom_size, std::back_inserter(chr_rom));

    mapper_number = header.mapper();
    logger::debug("Using mapper number {}", mapper_number);
    switch (header.mapper())
    {
    case 0:
    case 1:
        break;
    default:
        logger::error("Mapper number {} unimplemented.", mapper_number);
        return false;
    }

    ppu_ram.clear();
    ppu_ram.reserve(PPU_RAM_SIZE);
    ppu_ram.resize(PPU_RAM_SIZE);

    logger::debug(
        "Loaded  PRG  ROM, RESET=0x{:02X} 0x{:02X}.",
        prg_rom[prg_rom.size() - 5],
        prg_rom[prg_rom.size() - 4]);
    logger::debug(
        "Compare full ROM, RESET=0x{:02X} 0x{:02X}.",
        buffer[prg_rom.size() + 0x10 - 5],
        buffer[prg_rom.size() + 0x10 - 4]);

    return true;
}

void Cartridge::init_mapper()
{
    switch (header.mapper())
    {
    case 0:
        mapper = std::unique_ptr<Mapper>(new Mapper000(*this));
        break;
    case 1:
        mapper = std::unique_ptr<Mapper>(new Mapper001(*this));
        break;
    default:
        logger::error("Mapper number {} unimplemented.", mapper_number);
        throw std::runtime_error("Unimplemented mapper");
    }
}

uint8_t Cartridge::read(uint16_t address) { return mapper->read(address); }

uint8_t Cartridge::cpu_read(uint16_t address) { return mapper->read(address); }

void Cartridge::write(uint16_t address, uint8_t data)
{
    return mapper->write(address, data);
}

void Cartridge::cpu_write(uint16_t address, uint8_t data)
{
    return mapper->write(address, data);
}

uint8_t Cartridge::ppu_read(uint16_t address)
{
    return mapper->ppu_read(address);
}

void Cartridge::ppu_write(uint16_t address, uint8_t data)
{
    return mapper->ppu_write(address, data);
}

} // namespace nes
