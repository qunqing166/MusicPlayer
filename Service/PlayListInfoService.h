#ifndef PLAYLISTINFOSERVICE_H
#define PLAYLISTINFOSERVICE_H

// #include "IBaseService.h"
#include "../DataInfo/PlayListInfo.h"
#include "DataBaseService.h"

enum QueryParameterPlayList
{
    PlayListName,
    Creator
};

class PlayListInfoService//:public IBaseService<PlayListInfo>
{

    DataBaseService<PlayListInfo> *dbService;

public:
    PlayListInfoService();
    ~PlayListInfoService();

    Response<QList<PlayListInfo>> GetAll();
    Response<QList<PlayListInfo>> GetAll(QString str, QueryParameterPlayList type);
    Response<PlayListInfo> GetOne(int id);
    Response<PlayListInfo> Update(PlayListInfo model);
    Response<QString> Delete(int id);
    Response<PlayListInfo> Add(PlayListInfo model);
};

#endif // PLAYLISTINFOSERVICE_H
