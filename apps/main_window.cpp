#include "main_window.hpp"

#include "logger/logger.hpp"
#include <fmt/core.h>
#include <QApplication>
#include <QFont>
#include <QMenuBar>
#include <QSizePolicy>
#include <QStatusBar>
#include <QVBoxLayout>

namespace petito {

MainWindow::MainWindow()
{
    QWidget* widget = new QWidget;
    setCentralWidget(widget);

    auto cpuInfoLayout = initCpuInfo();

    QVBoxLayout* layout = new QVBoxLayout;

    programEditor = new QTextEdit;

    layout->setContentsMargins(5, 5, 5, 5);
    layout->addLayout(cpuInfoLayout);
    layout->addWidget(programEditor);

    widget->setLayout(layout);

    createActions();
    createMenus();

    QString message = tr("Status bar info");
    statusBar()->showMessage(message);

    setWindowTitle("Petito");
    setMinimumSize(400, 400);
}

QLayout* MainWindow::initCpuInfo()
{
    QFont monoFont("Monospace");
    monoFont.setStyleHint(QFont::TypeWriter);
    auto makeLabel = [&]() {
        auto label = new QLabel;
        label->setFont(monoFont);
        return label;
    };

    flags = makeLabel();
    programCounter = makeLabel();
    accumulator = makeLabel();
    xRegister = makeLabel();
    yRegister = makeLabel();
    stackPointer = makeLabel();
    clockCounter = makeLabel();

    mos6502::CpuData cpuData{};
    setCpuInfo(cpuData);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(flags);
    layout->addWidget(programCounter);
    layout->addWidget(accumulator);
    layout->addWidget(xRegister);
    layout->addWidget(yRegister);
    layout->addWidget(stackPointer);
    layout->addWidget(clockCounter);
    return layout;
}

void MainWindow::createActions()
{
    auto makeAct = [&](auto& act, auto name, std::optional<const char*> shortcut, auto func) {
        act = new QAction(tr(name), this);
        if (shortcut) {
            act->setShortcut(QKeySequence(tr(shortcut.value())));
        }
        connect(act, &QAction::triggered, this, func);
    };

    makeAct(loadAct, "&Load", "Ctrl+l", &MainWindow::load);
    makeAct(resetAct, "&Reset", "Ctrl+r", &MainWindow::reset);
    makeAct(unloadAct, "&Unload", "Ctrl+u", &MainWindow::unload);
    makeAct(exitAct, "&Exit", "Ctrl+q", &MainWindow::exit);
    makeAct(aboutAct, "About", std::nullopt, &MainWindow::about);
    makeAct(aboutQtAct, "About Qt", std::nullopt, &MainWindow::aboutQt);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(loadAct);
    fileMenu->addAction(resetAct);
    fileMenu->addAction(unloadAct);
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::load()
{
    using logger::LogLevel;
    logger::log(LogLevel::Info, "Load!");
}

void MainWindow::reset()
{
    using logger::LogLevel;
    logger::log(LogLevel::Info, "Reset!");
}

void MainWindow::unload()
{
    using logger::LogLevel;
    logger::log(LogLevel::Info, "Unload!");
}

void MainWindow::exit()
{
    using logger::LogLevel;
    logger::log(LogLevel::Info, "Quit!");
    QCoreApplication::quit();
}

void MainWindow::about()
{
    using logger::LogLevel;
    logger::log(LogLevel::Info, "About!");
}

void MainWindow::aboutQt()
{
    using logger::LogLevel;
    logger::log(LogLevel::Info, "About Qt!");
}

void MainWindow::setCpuInfo(const mos6502::CpuData& cpuData)
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

void MainWindow::setFlags(const mos6502::Flags& cpuFlags)
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
