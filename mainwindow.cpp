#include "mainwindow.h"
#include <QOpenGLWidget>
#include "openglwidget.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    widget = new OpenGLWidget(this);

    setCentralWidget(widget);
    setWindowState(windowState() | Qt::WindowFullScreen);
    QTimer::singleShot(1000, this, SLOT(show()));
}

MainWindow::~MainWindow()
{
    delete widget;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    widget->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    widget->keyReleaseEvent(event);
}
