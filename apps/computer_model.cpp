#include "computer_model.hpp"

#include "mos6502.hpp"

namespace petito {

ComputerModelCreator::ComputerModelCreator(QWidget *parent) {
    RamSize = new QSpinBox;
    RamSize->setMinimum(mos6502::MIN_RAM_SIZE);
    RamSize->setMaximum(mos6502::MIN_RAM_SIZE);
}

} // namespace petito
