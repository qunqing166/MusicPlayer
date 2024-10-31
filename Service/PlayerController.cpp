#include "PlayerController.h"
#include "PlayListItemService.h"
#include <QDir>
#include <QFile>
#include "../Dtos/UserDto.h"

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

MusicDto PlayerController::CurrentMusic() const
{
    if(currentMusicIndex < 0 || currentMusicIndex > currentMusicList.count())
        return MusicDto();
    return currentMusicList.at(currentMusicIndex);
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

long long PlayerController::Position() const
{
    return position;
}

PlayMode PlayerController::getPlayMode() const
{
    return playMode;
}

void PlayerController::setPlayMode(const PlayMode &value)
{
    playMode = value;
}

PlayerController::PlayerController(QObject *parent):QObject(parent)
{
    ObjectInit();

    ReadStartUp();

    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [&](QMediaPlayer::MediaStatus status){
        if(status == QMediaPlayer::EndOfMedia)
        {
            if(playMode == OneLoop)
            {
                mediaPlayer->play();
            }
            else
            {
                ToNextMusic();
            }
        }
    });

    connect(this, &PlayerController::CurrentMusicChanged, this, &PlayerController::AddToRecord);
}

PlayerController::~PlayerController()
{
    QJsonObject jsonObj;
    jsonObj.insert("current_music_index", this->currentMusicIndex);
    jsonObj.insert("current_music_position", this->mediaPlayer->position());
    jsonObj.insert("play_mode", this->playMode);
    jsonObj.insert("play_volume", this->audioOutput->volume());
    jsonObj.insert("user_id", UserDto::MyUserInfo()->Id());


    QByteArray jsonStr = QJsonDocument(jsonObj).toJson();
    QFile file(QDir::currentPath() + "/start_up.json");
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        file.write(jsonStr);
        file.close();
    }
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
    auto crtMusic = currentMusicList.at(currentMusicIndex);

    for(int i = 0; i < currentMusicList.count(); i++)
    {
        if(currentMusicList.at(i).Id() == music.Id())
        {
            currentMusicList.removeAt(i);
        }
    }

    for(int i = 0; i < currentMusicList.count(); i++)
    {
        if(currentMusicList.at(i).Id() == crtMusic.Id())
        {
            currentMusicList.insert(i + 1, music);
            currentMusicIndex = i;
        }
    }

    PlayListItemService service("_Current");
    service.UpdateNewList(currentMusicList);

    // emit CurrentMusicListChanged(currentMusicList, currentMusicIndex);
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

void PlayerController::ReadStartUp()
{
    QByteArray jsonStr;
    QFile file(QDir::currentPath() + "/start_up.json");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        jsonStr = file.readAll();
        file.close();
    }

    QJsonObject jsonObj = QJsonDocument::fromJson(jsonStr).object();

    currentMusicIndex = jsonObj.value("current_music_index").toInt();
    position = jsonObj.value("current_music_position").toInteger();
    playMode = (PlayMode)jsonObj.value("play_mode").toInt();
    audioOutput->setVolume(jsonObj.value("play_volume").toDouble());
    UserDto::GetUserInfo(jsonObj.value("user_id").toInt());

    PlayListItemService service("_Current");
    currentMusicList = service.GetPlayingList();
    if(currentMusicIndex < 0 || currentMusicIndex > currentMusicList.count())
        return;
    mediaPlayer->setSource(QUrl::fromLocalFile(currentMusicList.at(currentMusicIndex).MusicPath()));
}

QMediaPlayer *PlayerController::getMediaPlayer() const
{
    return mediaPlayer;
}

QAudioOutput *PlayerController::getAudioOutput() const
{
    return audioOutput;
}

void PlayerController::ToNextMusic()
{
    currentMusicIndex = (currentMusicIndex + 1) % currentMusicList.count();
    PlayMusic(currentMusicList.at(currentMusicIndex));
}

void PlayerController::ToLastMusic()
{
    currentMusicIndex = (currentMusicIndex + currentMusicList.count() - 1) % currentMusicList.count();
    PlayMusic(currentMusicList.at(currentMusicIndex));
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
