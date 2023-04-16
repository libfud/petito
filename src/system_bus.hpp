#ifndef NES_SYSTEM_BUS_HPP
#define NES_SYSTEM_BUS_HPP

#include "interrupt_signals.hpp"
#include "cartridge/cartridge.hpp"
#include "ppu/ppu.hpp"
#include "apu.hpp"

namespace mos6502 {

class SystemBus {
public:
    virtual InterruptSignals& get_interrupt_signals() = 0;

    virtual int32_t& get_cpu_clock() = 0;

    virtual uint8_t read(uint16_t address) = 0;

    virtual uint8_t const_read(uint16_t address) const = 0;

    virtual void write(uint16_t address, uint8_t data) = 0;
};

} // namespace mos6502

namespace nes {

using mos6502::InterruptSignals;;

class NesSystemBus : public mos6502::SystemBus {
public:
    NesSystemBus(Cartridge& cart, PPU& ppu, APU& apu);

    Cartridge& cart;
    PPU& ppu;
    APU& apu;
    InterruptSignals signals;
    int32_t clock_rate;
    int32_t master_clock;
    int32_t cpu_clock;
    int32_t ppu_clock;

    InterruptSignals& get_interrupt_signals() override;

    int32_t& get_cpu_clock() override;

    uint8_t read(uint16_t address) override;

    uint8_t const_read(uint16_t address) const override;

    void write(uint16_t address, uint8_t data) override;

    uint8_t ppu_read(uint16_t address);

    void ppu_write(uint16_t address, uint8_t data);

    void init();

    void scanline();

private:
    std::vector<uint8_t> internal_ram;
};

} // namespace nes

#endif
