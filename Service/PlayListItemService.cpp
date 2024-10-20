#include "PlayListItemService.h"

PlayListItemService::PlayListItemService(PlayingRecordType type)
{
    if(type == PlayingCurrent)
    {
        this->currentTableName = "CurrentPlayList";
        BaseService<PlayListItemDto>("CurrentPlayList");
    }
    else
    {
        BaseService<PlayListItemDto>("CurrentPlayList");
        this->currentTableName = "CurrentPlayList";
    }
    // qDebug()<<;
}

PlayListItemService::PlayListItemService(const QString &tableName):BaseService<PlayListItemDto>(PlayListItemDto::TableName + tableName)
{
    this->currentTableName = PlayListItemDto::TableName + tableName;
}



QList<MusicDto> PlayListItemService::GetPlayingList(SortOrder order)
{
    QString orderStr;
    if(order == Asc)orderStr = "asc";
    else if(order == Desc)orderStr = "desc";

    QString str = QString("select Music.* from Music, %1 where Music.Id = %1.MusicId order by %1.CreateTime %2;").arg(this->currentTableName).arg(orderStr);
    QSqlQuery query(str);
    QList<MusicDto> musics;
    while (query.next())
    {
        MusicDto music;
        DataBaseService::QueryToObject(&music, query);
        musics.append(music);
    }
    return musics;
}

bool PlayListItemService::Clear()
{
    QString str = QString("delete from %1;").arg(this->currentTableName);
    QSqlQuery query;
    if(query.exec(str))
        return true;
    return false;
}
