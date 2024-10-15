#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
// #include "../DataInfo/MusicInfo.h"
#include "../Dtos/MusicDto.h"

class PlayerController:public QObject
{
    Q_OBJECT

    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;

    bool isCheckMusic = false;

    QList<MusicDto> playingList;

    int currentPlayingIndex = 0;

public:
    PlayerController(QObject *parent = nullptr);

    void SetPlayingList(const QList<MusicDto> &value);

private:
    void ObjectInit();

public slots:
    void OpenNewMusic(const MusicDto &info);
    void ChangePlayStatus(bool is);
    QMediaPlayer *MediaPlayer() const;

signals:
    void UpdatePlayBarStatus(const MusicDto &music);
};

#endif // PLAYERCONTROLLER_H
