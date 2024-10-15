#ifndef PLAYLISTSERVISE_H
#define PLAYLISTSERVISE_H

#include "BaseService.h"
#include "../Dtos/PlayListDto.h"

class PlayListService:public BaseService<PlayListDto>
{
public:

    PlayListService(){}

    void GetMusicList(const QString &name);
};

#endif
