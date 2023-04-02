#ifndef INTERRUPT_SIGNALS_HPP
#define INTERRUPT_SIGNALS_HPP

namespace mos6502 {

struct InterruptSignals
{
    bool nmi;
    bool irq;
    bool reset;
};

} // namespace mos6502

#endif
