#pragma once

#include "BaseService.h"
#include "../Dtos/MusicDto.h"

class MusicService:public BaseService<MusicDto>
{

public:
    MusicService();

    QList<MusicDto> GetAllByTableName(const QString &tableName);

};
