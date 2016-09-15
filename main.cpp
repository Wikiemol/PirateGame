#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);
    QApplication a(argc, argv);
    MainWindow w;

    return a.exec();
}
