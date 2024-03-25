#include <QApplication>
#include "includes/IMusic.h"
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    IMusic window;
    window.show();

    return QApplication::exec();
}