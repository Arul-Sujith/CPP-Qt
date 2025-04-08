#include "MainWindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QFont defaultFont("Consolas", 12);
    app.setFont(defaultFont);

    MainWindow window;
    window.show();
    return app.exec();
}
