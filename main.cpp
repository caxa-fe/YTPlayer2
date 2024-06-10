#include "mainwindow.h"

#include <QApplication>
// Based on
// WebEngine Widgets Video Player Example
// https://doc.qt.io/qt-6/qtwebengine-webenginewidgets-videoplayer-example.html
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.resize(640, 360);
    mainWindow.setWindowTitle("YouTube Player");
    /*
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::black);
    mainWindow.setAutoFillBackground(true);
    mainWindow.setPalette(pal);
    */
    QPalette pal = mainWindow.palette();
    pal.setColor(QPalette::Window, Qt::black);
    mainWindow.setAutoFillBackground(true);
    mainWindow.setPalette(pal);

    mainWindow.show();

    return a.exec();
}
