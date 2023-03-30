#include "main_window.hpp"

#include "logger/logger.hpp"
#include <fmt/core.h>
#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QSizePolicy>
#include <QStatusBar>
#include <QVBoxLayout>

namespace petito {

using logger::LogLevel;

MainWindow::MainWindow()
{
    QWidget* widget = new QWidget;
    setCentralWidget(widget);

    QVBoxLayout* layout = new QVBoxLayout;

    programEditor = new QTextEdit;
    cpuInfo = new CpuInfo;

    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(cpuInfo);
    layout->addWidget(programEditor);

    widget->setLayout(layout);

    createActions();
    createMenus();

    QString message = tr("Status bar info");
    statusBar()->showMessage(message);

    setWindowTitle("Petito");
    setMinimumSize(400, 400);
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
    logger::log(LogLevel::Info, "Load!");
}

void MainWindow::reset()
{
    logger::log(LogLevel::Info, "Reset!");
}

void MainWindow::unload()
{
    logger::log(LogLevel::Info, "Unload!");
}

void MainWindow::exit()
{
    logger::log(LogLevel::Info, "Quit!");
    QCoreApplication::quit();
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Petito", "A MOS6502 Machine Creator");
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

}
