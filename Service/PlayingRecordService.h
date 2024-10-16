#ifndef PLAYINGRECORDSERVICE_H
#define PLAYINGRECORDSERVICE_H

// #include "Response.h"
#include <QSqlDatabase>
#include "BaseService.h"
#include "../Dtos/PlayingRecordDto.h"
// #include "DataBaseService.h"
#include "../Dtos/MusicDto.h"
// #include "../DataInfo/MusicInfo.h"

enum PlayingRecordType
{
    PlayingCurrent,
    PlayingRecord
};

//用于查询当前播放列表和播放记录
class PlayingRecordService:public BaseService<PlayingRecordDto>
{

    QString currentTableName;

public:
    PlayingRecordService(PlayingRecordType type = PlayingCurrent);
    PlayingRecordService(const QString &tableName);

    QList<MusicDto> GetPlayingList();
    bool Clear();

private:

};

#endif // PLAYINGRECORDSERVICE_H
