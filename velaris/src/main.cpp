#include <QApplication>
#include <QGuiApplication>
#include <QScreen>

#include "velaris/ui/MainWindow.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    velaris::ui::MainWindow window;
    if (QScreen* screen = QGuiApplication::primaryScreen()) {
        window.setGeometry(screen->availableGeometry());
    }
    window.show();

    return app.exec();
}
