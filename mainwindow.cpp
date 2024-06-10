#include "mainwindow.h"
#include "qapplication.h"
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineFullScreenRequest>
#include <QScreen>
#include <QFile>
#include <QVector>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_view(new QWebEngineView(this))
    , nowOnPlay(-1)
{
    setCentralWidget(m_view);
    m_view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    // Загрузка плеера
    m_view->load(QUrl(QStringLiteral("qrc:/html/playlist/player.html")));

    // и окно Remote Control
    rmCon = new RemoteControl();
    QScreen *screen = QApplication::primaryScreen();
    QRect rect = screen->geometry(); // Вычислим желаемые координаты и поставим окно на них
    int x = (rect.width()  - rmCon->width())  / 2 + 320 + 170;
    int y = (rect.height() - rmCon->height()) / 2 + 24;
    rmCon->move(x,y);
    rmCon->setWindowTitle("Remote Control");
    rmCon->show();

    // ('--ignore-certificate-errors-spki-list') игнорирование ошибок SSL,
    // только непонятно куда подключить

    // Fullscreen Request
    connect(m_view->page(),
            &QWebEnginePage::fullScreenRequested,
            this,
            &MainWindow::fullScreenRequested);

    // Команды с пульта Remote Control
    connect( rmCon, &RemoteControl::sendAction, this, &MainWindow::slot);
    connect( rmCon, &RemoteControl::sendVolume, this, &MainWindow::slotVolume);

}

void MainWindow::fullScreenRequested(QWebEngineFullScreenRequest request)
{
    //this->isFullScreen() ? this->showNormal() : this->showFullScreen();
    /*if(this->isFullScreen())
    {
        this->showNormal();
        request.reject();
    } */
    if (request.toggleOn()) {
        if (m_fullScreenWindow)
        {
            //request.accept();
            //m_fullScreenWindow.reset();

            return;
        }

        request.accept();
        m_fullScreenWindow.reset(new FullScreenWindow(m_view));
    } else {
        if (!m_fullScreenWindow)
            return;
        request.accept();
        m_fullScreenWindow.reset();
    }
}

void MainWindow::slot(int x)
{
    if (x == -1) // Стоп
    {
        m_view->load(QUrl(QStringLiteral("qrc:/html/playlist/player.html")));
        // Не получается удалить объект в JavaSript,
        // поэтому просто перегружаем страницу
        nowOnPlay = -1; // -1 состояние СТОП, плеер пуст
    }
    else if(x == -2) // FullScreenMode
    {
        m_view -> page() ->runJavaScript(
            "playFullscreen();"
            );
    }

    else
    {
        if (nowOnPlay == -1)    // состояние СТОП, плеер не загружен
        {
            m_view -> page() ->runJavaScript(
                "prepVideo('"
                + rmCon->getPlayListItem(x)     // Запускаем плеер с нужным видео
                +"');"
                );
            nowOnPlay = x;
        }
        else if (nowOnPlay == x ) // Плеер работает, просто покажем баннер
        {
            m_view -> page() ->runJavaScript(
                "prepVideo('"
                + rmCon->getPlayListItem(x)
                +"');"
                );
        }
        else    // Плеер работает, попытка загрузки другого видео
        {
            m_view->load(QUrl(QStringLiteral("qrc:/html/playlist/player.html")));

            // Тормознёмся на пару секунд, дадим время для загрузки HTML
            QTimer::singleShot(2000, [this, x]{ m_view -> page() ->runJavaScript(
                                              "prepVideo('"
                                              + rmCon->getPlayListItem(x)
                                              +"');"
                                              );});
            nowOnPlay = x;
        }
    }
}


void MainWindow::slotVolume(int x)
{
    if (x < 0)  // Set Mute or UnMute
    {
        if (x == -1)
            m_view -> page() ->runJavaScript(
                "player.mute();"
                );
        if (x == -2)
            m_view -> page() ->runJavaScript(
                "player.unMute();"
                );
    }
    else    // Set Volume
    {
        int vol = (float)x * 12.5;
        m_view -> page() ->runJavaScript(
            "setVolume("+ QString::number(vol) + ");"
            "player.unMute();"
            );
    }

}






