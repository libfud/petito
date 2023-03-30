#ifndef PETITO_CPU_INFO_H
#define PETITO_CPU_INFO_H

#include <QLabel>
#include <QLayout>

#include "mos6502.hpp"

namespace petito {
class CpuInfo : public QWidget
{
public:
    CpuInfo();

private:
    void createActions();
    void createMenus();

    /* Slots */
    void update(const mos6502::CpuData& cpuData);

    /* Display information */
    QLabel* flags;
    QLabel* programCounter;
    QLabel* accumulator;
    QLabel* xRegister;
    QLabel* yRegister;
    QLabel* stackPointer;
    QLabel* clockCounter;

    /* Helper Functions */
    QLayout* initCpuInfo();
    void setFlags(const mos6502::Flags& cpuFlags);
};

} // namespace petito


#endif
