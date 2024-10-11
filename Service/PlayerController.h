#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "../DataInfo/MusicInfo.h"

class PlayerController:public QObject
{
    Q_OBJECT

    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;

    bool isCheckMusic = false;

public:
    PlayerController(QObject *parent = nullptr);

private:
    void ObjectInit();

public slots:
    void OpenNewMusic(const MusicInfo &info);
    void ChangePlayStatus(bool is);
};

#endif // PLAYERCONTROLLER_H
