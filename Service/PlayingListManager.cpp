#include "PlayingListManager.h"
#include "PlayListItemService.h"

using namespace Model;
using namespace Service;

QList<Music> PlayingListManager::Musics() const
{
    return musics;
}

void PlayingListManager::setMusics(const QList<Music> &value)
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

Music PlayingListManager::getMusic() const
{
    return currentMusic;
}

void PlayingListManager::setMusic(const Music &value)
{
    currentMusic = value;
    emit CurrentMusicChanged(value);
}

void PlayingListManager::setMusic(const QList<Music> &list, const int &index)
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
