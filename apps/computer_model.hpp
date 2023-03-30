#ifndef COMPUTER_MODEL_HPP
#define COMPUTER_MODEL_HPP

#include <QDialog>
#include <QSpinBox>

namespace petito {

class ComputerModelCreator : QDialog
{
public:
    ComputerModelCreator(QWidget* parent = nullptr);

private:
    QSpinBox* RamSize;
    QSpinBox* RomSize;
};

} // namespace petito

#endif
