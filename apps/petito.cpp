#include <QApplication>
#include <QPushButton>

#include "main_window.hpp"

namespace petito {
int run(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow mainWindow{};
    mainWindow.show();

    return app.exec();
}

} // namespace petito

int main(int argc, char **argv)
{
    return petito::run(argc, argv);
}
