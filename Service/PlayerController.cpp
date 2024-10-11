#include "PlayerController.h"

PlayerController::PlayerController(QObject *parent):QObject(parent)
{
    ObjectInit();
}

void PlayerController::ObjectInit()
{
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
}

void PlayerController::OpenNewMusic(const MusicInfo &info)
{
    isCheckMusic = true;
    mediaPlayer->setSource(QUrl::fromLocalFile(info.musicPath));
    mediaPlayer->play();
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
