#ifndef PETITO_MAIN_WINDOW_H
#define PETITO_MAIN_WINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QTextEdit>
#include <QLayout>

#include "mos6502.hpp"

namespace petito {
class MainWindow : public QMainWindow
{
public:
    MainWindow();
private:
    void createActions();
    void createMenus();

    /* Slots */
    QMenu* fileMenu;
    void load();
    void reset();
    void unload();
    void exit();
    QAction* loadAct;
    QAction* resetAct;
    QAction* unloadAct;
    QAction* exitAct;

    /* Help menu items */
    QMenu* helpMenu;
    void about();
    void aboutQt();
    QAction* aboutAct;
    QAction* aboutQtAct;

    QLabel* flags;
    QLabel* programCounter;
    QLabel* accumulator;
    QLabel* xRegister;
    QLabel* yRegister;
    QLabel* stackPointer;
    QLabel* clockCounter;

    QLayout* initCpuInfo();
    void setCpuInfo(const mos6502::CpuData& cpuData);
    void setFlags(const mos6502::Flags& cpuFlags);

    QTextEdit* programEditor;
};

} // namespace petito


#endif
