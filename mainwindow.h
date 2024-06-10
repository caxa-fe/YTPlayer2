#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fullscreenwindow.h"
#include "qtimer.h"
#include "remotecontrol.h"
#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEngineFullScreenRequest>
#include <QVector>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    //~MainWindow();
QWebEngineView *m_view;
public slots:
    void slot(int); // Кнопки Play, Stop, FullScreen
    void slotVolume(int); // Кнопки громкости на пульте

private slots:
    void fullScreenRequested(QWebEngineFullScreenRequest request);
    //void slotPageReady(int);
private:
    //QWebEngineView *m_view;
    QScopedPointer<FullScreenWindow> m_fullScreenWindow;
    RemoteControl *rmCon;
    int nowOnPlay;

};
#endif // MAINWINDOW_H
