#include "PlayingListManager.h"
#include "PlayListItemService.h"

QList<MusicDto> PlayingListManager::Musics() const
{
    return musics;
}

void PlayingListManager::setMusics(const QList<MusicDto> &value)
{
    musics = value;
    
    PlayListItemService service("_Current");
    service.Clear();
    
    emit MusicListChanged(musics);
}

int PlayingListManager::Index() const
{
    return index;
}

void PlayingListManager::setIndex(int value)
{
    index = value;
    emit MusicIndexChanged(this->index);
}

MusicDto PlayingListManager::Music() const
{
    return currentMusic;
}

void PlayingListManager::setMusic(const MusicDto &value)
{
    currentMusic = value;
    emit CurrentMusicChanged(value);
}

void PlayingListManager::setMusic(const QList<MusicDto> &list, const int &index)
{
    this->musics = list;
    this->index = index;
    this->currentMusic = list.at(index);

    emit CurrentMusicChanged(this->currentMusic);
    emit MusicListChanged(this->musics);
    emit MusicIndexChanged(this->index);
}

QString PlayingListManager::PlayListName() const
{
    return playListName;
}

void PlayingListManager::setPlayListName(const QString &value)
{
    playListName = value;
}

PlayingListManager::PlayingListManager() {}

inline PlayingListManager* PlayingListManager::instance = nullptr;

PlayingListManager *PlayingListManager::Instance()
{
    if(instance == nullptr)
    {
        instance = new PlayingListManager();
    }
    return instance;
}
