#pragma once

#include "BaseService.h"
#include "../Model/Music.h"

namespace Service
{

class MusicService:public BaseService<Model::Music>
{

public:
    MusicService();

    QList<Model::Music> GetAllByTableName(const QString &tableName);

};

}
