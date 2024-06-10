#include "remotecontrol.h"
#include "ui_remotecontrol.h"
#include <QWebEngineFullScreenRequest>
#include <QPixmap>
#include <QString>
#include <QFile>
#include <QVector>
RemoteControl::RemoteControl(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RemoteControl)
    , currentChannel(1)
    , currentVolume(3)
    , isSoundMute(false)
{
    ui->setupUi(this);
    ui ->labelCh->setText(QString::number(currentChannel));
// Готовим катинки для Volume Display
    for (int i = 0; i < 9; ++i)
    {
        QString s = ":imgs/pics/vol_" + QString::number(i) + ".svg";
        volPicVec.append(QPixmap(s));
    }
    ui ->volDisplay->setPixmap(volPicVec[currentVolume]);

// Считаем плейлист
    QFile file(":html/playlist/playlist.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //qDebug() << "File open" << "\n";
        QTextStream stream(&file);
        QString line;
        while (!stream.atEnd()){
            line = stream.readLine();
            line.truncate(11);
            playList.append(line);
        }
    }
    else qDebug() << "File not found";
    file.close();

    // Подготовим список картинок
    // Картинки храняться локально. Надо подумать, как это можно улучшить
    for(int i = 0; i < playList.length(); ++i)
    {
        QString line = ":imgs/pics/pic" + QString::number(i) + ".png";
        picsList.append(line);
    }
}


RemoteControl::~RemoteControl()
{
    delete ui;
}
void RemoteControl::setChannel(int ch)
{
    currentChannel = ch;
    ui ->labelCh->setText(QString::number(ch));
    ui ->labelTop->setPixmap(getViPic(ch));
}
int RemoteControl::getPlayerVolume()
{
    int volArr[] = {0,12,25,38,50,62,75,88,100};
    return volArr[currentVolume];
}
QPixmap RemoteControl::getViPic(int ch)
{
    ch =  ch % playList.length();
    return QPixmap(picsList[ch]);
}
QString RemoteControl::getPlayListItem(int x)
{
    return playList[x];
}
// ---- Кнопки ---
void RemoteControl::on_btnFullSc_clicked()
{
    emit sendAction(-2);
}
// ---- Кнопки 0-9 каналов
void RemoteControl::on_btnOne_clicked()
{
    setChannel(1);
}
void RemoteControl::on_btnTwo_clicked()
{
    setChannel(2);
}
void RemoteControl::on_btnThree_clicked()
{
    setChannel(3);
}
void RemoteControl::on_btnFour_clicked()
{
    setChannel(4);
}
void RemoteControl::on_btnFive_clicked()
{
    setChannel(5);
}
void RemoteControl::on_btnSix_clicked()
{
    setChannel(6);
}
void RemoteControl::on_btnSeven_clicked()
{
    setChannel(7);
}
void RemoteControl::on_btnEight_clicked()
{
    setChannel(8);
}
void RemoteControl::on_btnNine_clicked()
{
    setChannel(9);
}
void RemoteControl::on_btnZero_clicked()
{
    setChannel(0);
}
// ----- Кнопки +/- каналы
void RemoteControl::on_btnChUp_clicked()
{
    if (currentChannel < 9)
        ++currentChannel;
    else
        currentChannel = 0;

    setChannel(currentChannel);
}
void RemoteControl::on_btnChDown_clicked()
{
    if (currentChannel > 0)
        --currentChannel;
    else
        currentChannel = 9;

    setChannel(currentChannel);
}
// ----- Кнопки Stop/Play --------
void RemoteControl::on_btnStop_clicked()
{
    setChannel(1);
    ui ->labelTop->setText("Выбирайте фильм");
    emit sendAction(-1);
}

void RemoteControl::on_btnPlay_clicked()
{
    emit sendAction(currentChannel);
}

// ----- Кнопки Громкости --------
void RemoteControl::on_btnVolUp_clicked()
{
    if (currentVolume < 8)
    {
        ++currentVolume;
        ui ->volDisplay->setPixmap(volPicVec[currentVolume]);
    }
    emit sendVolume(currentVolume);
}

void RemoteControl::on_btnVolDown_clicked()
{
    if (currentVolume > 0)
    {
        --currentVolume;
        ui ->volDisplay->setPixmap(volPicVec[currentVolume]);
    }
    emit sendVolume(currentVolume);
}

void RemoteControl::on_btnSndOff_clicked()
{

    isSoundMute = isSoundMute ? false : true;
    if (isSoundMute)
    {
        ui ->volDisplay->setPixmap(volPicVec[0]);
        //emit sendVolume(currentVolume);
        emit sendVolume(-1);    // Sound Mute
    }
    else
    {
        ui ->volDisplay->setPixmap(volPicVec[currentVolume]);
        emit sendVolume(-2);    // Sound UnMute
        emit sendVolume(currentVolume);
    }


}


