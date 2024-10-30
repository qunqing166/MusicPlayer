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

QList<MusicDto> PlayListItemService::GetPlayingList(QString orderCriteria, SortOrder orderType)
{
    QString orderStr;
    if(orderType == Asc)orderStr = "asc";
    else if(orderType == Desc)orderStr = "desc";

    QString str = QString("select Music.* from Music, %1 where Music.Id = %1.MusicId order by %1.%2 %3;")
                      .arg(this->currentTableName).arg(orderCriteria).arg(orderStr);
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

bool PlayListItemService::UpdateNewList(const QList<MusicDto> &list)
{
    //删除原来的记录
    this->Clear();
    //添加新的记录
    foreach (auto music, list) {
        PlayListItemDto item;
        item.setMusicId(music.Id());
        this->Add(item);
    }
    return true;
}
