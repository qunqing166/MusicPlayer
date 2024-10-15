#include "PlayerController.h"

PlayerController::PlayerController(QObject *parent):QObject(parent)
{
    ObjectInit();
}

void PlayerController::SetPlayingList(const QList<MusicDto> &value)
{
    this->playingList = value;
}

void PlayerController::ObjectInit()
{
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
}

void PlayerController::OpenNewMusic(const MusicDto &info)
{
    // currentPlayingIndex = index;
    isCheckMusic = true;
    mediaPlayer->setSource(QUrl::fromLocalFile(info.MusicPath()));
    mediaPlayer->play();
    emit UpdatePlayBarStatus(info);
}

void PlayerController::ChangePlayStatus(bool is)
{
    if(is)
    {
        mediaPlayer->play();
    }
    else
    {
        mediaPlayer->pause();
    }
}

QMediaPlayer *PlayerController::MediaPlayer() const
{
    return mediaPlayer;
}
