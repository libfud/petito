#include "cpu_info.hpp"

#include <fmt/core.h>
#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>

namespace petito {

CpuInfo::CpuInfo()
{
    auto cpuInfoLayout = initCpuInfo();

    cpuInfoLayout->setContentsMargins(5, 5, 5, 5);

    this->setLayout(cpuInfoLayout);
}

QLayout* CpuInfo::initCpuInfo()
{
    auto layout = new QGridLayout;

    QFont monoFont("Monospace");
    monoFont.setStyleHint(QFont::TypeWriter);
    auto column = 0;
    auto makeLabel = [&](auto& dataLabel, auto infoText) {
        dataLabel = new QLabel;
        dataLabel->setFont(monoFont);
        auto infoLabel = new QLabel(infoText);
        layout->addWidget(infoLabel, 0, column);
        layout->addWidget(dataLabel, 1, column);
        column++;
    };

    makeLabel(flags, "Flags");
    makeLabel(programCounter, "PC");
    makeLabel(accumulator, "ACC");
    makeLabel(xRegister, "X");
    makeLabel(yRegister, "Y");
    makeLabel(stackPointer, "SP");
    makeLabel(clockCounter, "CYC");

    mos6502::CpuData cpuData{};
    update(cpuData);

    return layout;
}

void CpuInfo::update(const mos6502::CpuData& cpuData)
{
    setFlags(cpuData.flags);

    auto setHex2 = [](auto& label, auto num) {
        auto text = fmt::format("0x{:02X}", num);
        label->setText(QString::fromStdString(text));
    };

    auto setHex4 = [](auto& label, auto num) {
        auto text = fmt::format("0x{:04X}", num);
        label->setText(QString::fromStdString(text));
    };

    setHex4(programCounter, cpuData.pc);
    setHex2(accumulator, cpuData.acc);
    setHex2(xRegister, cpuData.x);
    setHex2(yRegister, cpuData.y);
    setHex2(stackPointer, cpuData.stack_ptr);

    clockCounter->setText(QString::number(cpuData.clock_counter));
}

void CpuInfo::setFlags(const mos6502::Flags& cpuFlags)
{
    auto flagText = fmt::format(
        "{}{}{}{}{}{}{}",
        cpuFlags.carry ? "C" : "0",
        cpuFlags.zero ? "Z" : "0",
        cpuFlags.interrupt_inhibit ? "I" : "0",
        cpuFlags.bcd_arithmetic ? "D" : "0",
        cpuFlags.brk ? "Br" : "0o",
        cpuFlags.overflow ? "V" : "0",
        cpuFlags.negative ? "N" : "0"
    );

    flags->setText(QString::fromStdString(flagText));
}

}
