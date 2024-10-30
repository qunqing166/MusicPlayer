#include "PlayerController.h"
#include "PlayListItemService.h"
#include "MusicService.h"

QList<MusicDto> PlayerController::CurrentMusicList() const
{
    return currentMusicList;
}

void PlayerController::setCurrentMusicList(const QList<MusicDto> &value, int index)
{

    currentMusicList = value;
    currentMusicIndex = index;
    isListNameChanged = false;
    //更新数据库
    PlayListItemService service("_Current");
    service.UpdateNewList(currentMusicList);

    MusicDto music = currentMusicList.at(currentMusicIndex);
    //播放
    PlayMusic(music);

    AddToRecord(music);
    //通知sidebar的index更改
    emit CurrentMusicIndexChanged(currentMusicIndex);
    // emit CurrentMusicListChanged(currentMusicList, currentMusicIndex);
}

int PlayerController::CurrentMusicIndex() const
{
    return currentMusicIndex;
}

void PlayerController::setCurrentMusicIndex(int value)
{
    currentMusicIndex = value;

    PlayMusic(currentMusicList.at(currentMusicIndex));
}

QString PlayerController::CurrentPlaylistName() const
{
    return currentPlaylistName;
}

void PlayerController::setCurrentPlaylistName(const QString &value)
{
    if(this->currentPlaylistName == value)
    {
        return;
    }
    currentPlaylistName = value;
    isListNameChanged = true;
}

PlayerController::PlayerController(QObject *parent):QObject(parent)
{
    ObjectInit();
}

inline PlayerController* PlayerController::instance = nullptr;

PlayerController *PlayerController::Instance()
{
    if(instance == nullptr)
    {
        instance = new PlayerController();
    }
    return instance;
}

void PlayerController::AddToPlayList(const MusicDto &music)
{
    currentMusicList.insert(currentMusicIndex + 1, music);

    emit CurrentMusicListChanged(currentMusicList, currentMusicIndex);
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

void PlayerController::PlayMusic(const MusicDto &music)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(music.MusicPath()));
    mediaPlayer->play();

    emit CurrentMusicChanged(music);
}

void PlayerController::AddToRecord(const MusicDto &music)
{
    PlayListItemService service("_Record");

    if(service.IsExist(QString("MusicId = %1").arg(music.Id())))
    {
        auto m = service.GetOneByParameter(QString("MusicId = %1").arg(music.Id()));
        service.Update(m);
    }
    else
    {
        PlayListItemDto item;
        item.setMusicId(music.Id());
        service.Add(item);
    }
}

void PlayerController::OpenNewMusic(const MusicDto &info)
{
    // currentPlayingIndex = index;
    isCheckMusic = true;
    mediaPlayer->setSource(QUrl::fromLocalFile(info.MusicPath()));
    mediaPlayer->play();
    emit UpdatePlayBarStatus(info);
}

void PlayerController::setPlayStatus(bool is)
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

void PlayerController::ReadStartUp(int index)
{
    PlayListItemService service("_Current");
    currentMusicList = service.GetPlayingList();
    currentPlayingIndex = index;
    if(currentMusicIndex < 0 || currentMusicIndex > currentMusicList.count())
        return;
    mediaPlayer->setSource(QUrl::fromLocalFile(currentMusicList.at(currentMusicIndex).MusicPath()));
}

QMediaPlayer *PlayerController::getMediaPlayer() const
{
    return mediaPlayer;
}

QMediaPlayer *PlayerController::MediaPlayer() const
{
    return mediaPlayer;
}

void PlayerController::LoadMusic(const MusicDto &music)
{
    mediaPlayer->setSource(QUrl::fromLocalFile(music.MusicPath()));
}

void PlayerController::OnProgressBarValueChanged(int value)
{
    mediaPlayer->setPosition(value * 1000);
}
