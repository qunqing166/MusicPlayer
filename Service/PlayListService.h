#ifndef PLAYLISTSERVISE_H
#define PLAYLISTSERVISE_H

#include "BaseService.h"
#include "../Dtos/PlayListDto.h"
#include "../Dtos/MusicDto.h"

class PlayListService:public BaseService<PlayListDto>
{

    QString tableName;

public:

    PlayListService(const QString &tableName = "");

    QList<MusicDto> GetMusicList();
    QList<MusicDto> GetMusicList(const QString &name);

    bool Add(const PlayListDto &info);
    // PlayListDto GetOne(const QString &listName);

};

#endif
