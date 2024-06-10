#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QWidget>
#include <QWebEngineFullScreenRequest>

namespace Ui {
class RemoteControl;
}

class RemoteControl : public QWidget
{
    Q_OBJECT

public:
    explicit RemoteControl(QWidget *parent = nullptr);
    ~RemoteControl();
    int getPlayerVolume();
    QString getPlayListItem(int);
    QPixmap getViPic(int);

private:
    Ui::RemoteControl *ui;
    void setChannel(int);
    int currentChannel;
    int currentVolume;
    QVector<QPixmap> volPicVec; // Картинки индикатора громкости
    bool isSoundMute;
    QVector<QString> playList;
    QVector<QString> picsList;

private slots:
    void on_btnOne_clicked();
    void on_btnTwo_clicked();
    void on_btnThree_clicked();
    void on_btnFour_clicked();
    void on_btnFive_clicked();
    void on_btnSix_clicked();
    void on_btnSeven_clicked();
    void on_btnEight_clicked();
    void on_btnNine_clicked();
    void on_btnZero_clicked();
    void on_btnStop_clicked();

    void on_btnFullSc_clicked();

    void on_btnPlay_clicked();

    void on_btnVolUp_clicked();

    void on_btnVolDown_clicked();

    void on_btnSndOff_clicked();

    void on_btnChUp_clicked();

    void on_btnChDown_clicked();

signals:
    void sendAction(int);
    void sendFullScreen();
    void sendPlayPause();
    void sendVolume(int);
};

#endif // REMOTECONTROL_H
