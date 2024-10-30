#ifndef PLAYLISTITEMSERVICE_H
#define PLAYLISTITEMSERVICE_H

// #include "Response.h"
#include <QSqlDatabase>
#include "BaseService.h"
#include "../Dtos/PlayListItemDto.h"
// #include "DataBaseService.h"
#include "../Dtos/MusicDto.h"
// #include "../DataInfo/MusicInfo.h"

enum PlayingRecordType
{
    PlayingCurrent,
    PlayingRecord
};

enum SortOrder
{
    Desc,
    Asc
};

//用于查询当前播放列表和播放记录
class PlayListItemService:public BaseService<PlayListItemDto>
{

    QString currentTableName;

public:
    PlayListItemService(PlayingRecordType type = PlayingCurrent);
    PlayListItemService(const QString &tableName);

    QList<MusicDto> GetPlayingList(QString orderCriteria = "CreateTime", SortOrder oder = Desc);
    bool Clear();
    bool UpdateNewList(const QList<MusicDto> &list);

private:

};

#endif // PLAYLISTITEMSERVICE_H
