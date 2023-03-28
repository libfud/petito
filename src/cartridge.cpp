#include <algorithm>
#include <exception>
#include <fstream>
#include <iterator>
#include <filesystem>

#include "cartridge.hpp"
#include "logger/logger.hpp"

namespace nes {

namespace fs = std::filesystem;

bool Cartridge::load(const std::string& rom_name)
{
    if (!fs::exists(rom_name))
    {
        logger::log(logger::LogLevel::Error, "No file with name {}.", rom_name);
        return false;
    }
    fs::path rom_path = rom_name;
    size_t rom_size = fs::file_size(rom_path);
    size_t min_size = NesHeader::HEADER_SIZE;
    size_t position = 0;
    if (rom_size < min_size)
    {
        logger::log(
            logger::LogLevel::Error,
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
        logger::log(logger::LogLevel::Error,
                    "Failed to read header.");
        return false;
    }

    size_t prg_rom_size = header.prg_rom_size();
    size_t prg_ram_size = header.prg_ram_size();
    size_t chr_rom_size = header.chr_rom_size();
    size_t chr_ram_size = header.chr_ram_size();

    logger::log(logger::LogLevel::Debug, "prg rom size {}", prg_rom_size);
    logger::log(logger::LogLevel::Debug, "prg ram size {}", prg_ram_size);
    logger::log(logger::LogLevel::Debug, "chr rom size {}", chr_rom_size);
    logger::log(logger::LogLevel::Debug, "chr ram size {}", chr_ram_size);

    min_size += prg_rom_size;
    min_size += chr_rom_size;
    if (header.uses_trainer())
    {
        logger::log(logger::LogLevel::Debug, "Using trainer for ROM");
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

    logger::log(logger::LogLevel::Debug,
                "Reading 0x{:04X} bytes into prg_rom, starting at 0x{:04X}.",
                prg_rom_size,
                position);
    std::copy_n(buffer.begin() + position, prg_rom_size, std::back_inserter(prg_rom));
    position += prg_rom_size;

    logger::log(logger::LogLevel::Debug,
                "Reading 0x{:04X} bytes into chr_rom, starting at 0x{:04X}.",
                chr_rom_size,
                position);
    std::copy_n(buffer.begin() + position, chr_rom_size, std::back_inserter(chr_rom));

    mapper_number = header.mapper();
    logger::log(logger::LogLevel::Debug, "Using mapper number {}", mapper_number);
    switch (header.mapper())
    {
    case 0:
    case 1:
        break;
    default:
        logger::log(logger::LogLevel::Error, "Mapper number {} unimplemented.", mapper_number);
        return false;
    }

    logger::log(logger::LogLevel::Debug, "Loaded  PRG  ROM, RESET=0x{:02X} 0x{:02X}.",
                prg_rom[prg_rom.size() - 5],
                prg_rom[prg_rom.size() - 4]);
    logger::log(logger::LogLevel::Debug, "Compare full ROM, RESET=0x{:02X} 0x{:02X}.",
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
        logger::log(logger::LogLevel::Error, "Mapper number {} unimplemented.", mapper_number);
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

void Cartridge::ppu_write(uint16_t address, uint8_t data)
{
    return mapper->write(address, data);
}

Mapper000::Mapper000(Cartridge &cart) : cartridge(cart) {}

uint8_t* Mapper000::map(uint16_t address)
{
    if (address >= 0x6000 && address < 0x8000)
    {
        auto mapped_address = address - 0x6000;
        logger::log(logger::LogLevel::Trace,
                    "mapper000 ram mapped address=0x{:04X} to 0x{:04X}",
                    address,
                    mapped_address);
        return &cartridge.prg_ram[mapped_address];
    }
    else
    {
        // auto page_size = NesHeader::PRG_ROM_PAGE_SIZE;
        auto mapped_address = (address - 0x8000) % cartridge.prg_rom.size();
        logger::log(logger::LogLevel::Trace,
                    "mapper000 rom mapped address=0x{:04X} to 0x{:04X}",
                    address,
                    mapped_address);
        return &cartridge.prg_rom[mapped_address];
    }
}

uint8_t Mapper000::read(uint16_t address)
{
    uint8_t* data_ptr = map(address);
    return *data_ptr;
}

void Mapper000::write(uint16_t address, uint8_t data)
{
    logger::log(
        logger::LogLevel::Trace, "mapper000 write to address=0x{:04X}, data 0x{:02x}",
        address,
        data);

    if (address >= 0x8000 || address < 0x6000)
    {
        logger::log(
            logger::LogLevel::Error, "mapper000 write denied to address=0x{:04X}, data 0x{:02x}",
            address,
            data);
        return;
    }
    uint8_t* data_ptr = map(address);
    *data_ptr = data;
}

Mapper001::Mapper001(Cartridge& cart) :
    cartridge(cart),
    shift_register(0),
    load_register(0),
    chr_bank_0(0),
    chr_bank_1(0),
    prg_bank(0),
    prg_ram_enable(0),
    write_counter(0),
    mirroring(NAMETABLE_0),
    prg_swap_bank(BANK_C000_FIXED),
    prg_bank_size(0),
    chr_bank_size(0)
{

}

uint8_t Mapper001::read(uint16_t address)
{
    logger::log(
        logger::LogLevel::Trace, "mapper001 read to address=0x{:04X}",
        address);

    if (address >= 0x6000 && address < 0x8000)
    {
        auto mapped_address = address - 0x6000;
        auto data = cartridge.prg_ram[mapped_address];
        logger::log(
            logger::LogLevel::Trace, "mapper001 read RAM, address=0x{:04X}, mapped=0x{:04X}, data 0x{:02x}",
            address,
            mapped_address,
            data);

        return data;
    }
    else //  if (address >= 0x8000)
    {
        uint32_t bank = (prg_bank & prg_bank_size) << BANK_SHIFT;
        auto mapped_address = (bank | address) - 0x8000;

        auto page_size = NesHeader::PRG_ROM_PAGE_SIZE;

        if (mapped_address >= page_size && cartridge.prg_rom.size() == page_size)
        {
            mapped_address -= page_size;
        }
        auto data = cartridge.prg_rom[mapped_address];
        logger::log(
            logger::LogLevel::Trace, "mapper001 read ROM, address=0x{:04X}, mapped=0x{:04X}, data 0x{:02x}",
            address,
            mapped_address,
            data);
        return data;
    }
}

void Mapper001::write(uint16_t address, uint8_t data)
{
    logger::log(
        logger::LogLevel::Trace, "mapper001 write to address=0x{:04X}, data 0x{:02x}",
        address,
        data);

    uint8_t data_bit = 0;
    bool reset_bit = false;

    if (address >= 0x8000)
    {
        data_bit = data & 0x01;
        reset_bit = data & 0x80;
    }

    if (reset_bit)
    {
        logger::log(logger::LogLevel::Trace, "mapper001 write reset");

        write_counter = 0;
        shift_register = 0;

        mirroring = NAMETABLE_0;
        prg_swap_bank = BANK_C000_FIXED;
        prg_bank_size = BANK_SIZE_16K;
        chr_bank_size = ONE_8K_BANK;
    }
    else
    {
        shift_register |= data_bit << (4 - write_counter);
        write_counter++;
    }

    if (write_counter == 5)
    {
        write_counter = 0;
        if (address >= 0x8000 && address < 0xA000)
        {
            mirroring = shift_register & 0x03;
            prg_swap_bank = shift_register & 0x04 >> 2;
            prg_bank_size = shift_register & 0x08 >> 3;
            chr_bank_size = shift_register & 0x10;
            uint32_t bank = (prg_bank & prg_bank_size) << BANK_SHIFT;

            logger::log(
                logger::LogLevel::Trace,
                "mapper001 state: M={:02X} SWAP_BANK={:02X}, PRG_BANK_SIZE={}, PRG_BANK={:04X}, CHR_BANK_SIZE={}",
                mirroring,
                prg_swap_bank,
                prg_bank_size,
                bank,
                chr_bank_size);

        }
        else if (address >= 0xA000 && address < 0xC000)
        {
            chr_bank_0 = shift_register & 0x1F;
        }
        else if (address >= 0xC000 && address < 0xE000)
        {
            chr_bank_1 = shift_register & 0x1F;
        }
        else
        {
            uint32_t bank = (prg_bank & prg_bank_size) << BANK_SHIFT;

            prg_bank = shift_register & 0x0F;
            prg_ram_enable = (shift_register & 0x10) == 0;
            logger::log(
                logger::LogLevel::Trace,
                "mapper001 state: PRG_BANK={:02X}, BANK={:04X}, PRG_RAM_ENABLE={}",
                prg_bank,
                bank,
                prg_ram_enable);
        }
    }

    if (address >= 0x6000 && address < 0x8000 && prg_ram_enable)
    {
        cartridge.prg_ram[address - 0x6000] = data;
    }
}

}
