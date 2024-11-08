#ifndef PLAYLISTSERVISE_H
#define PLAYLISTSERVISE_H

#include "BaseService.h"
#include "../Model/PlayList.h"
#include "../Model/Music.h"

namespace Service
{

class PlayListService:public BaseService<Model::PlayList>
{

    QString tableName;

public:

    PlayListService(const QString &tableName = "");

    QList<Model::Music> GetMusicList();
    QList<Model::Music> GetMusicList(const QString &name);

    bool Add(const Model::PlayList &info);

    QList<Model::PlayList> GetPlayListFromUser();
    QList<Model::PlayList> GetPlayListFromUser(int id);

};

}

#endif
