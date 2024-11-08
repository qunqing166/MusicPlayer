#include "PlayListItemService.h"

using namespace Model;
using namespace Service;

PlayListItemService::PlayListItemService(PlayingRecordType type)
{
    if(type == PlayingCurrent)
    {
        this->currentTableName = "CurrentPlayList";
        BaseService<PlayListItem>("CurrentPlayList");
    }
    else
    {
        BaseService<PlayListItem>("CurrentPlayList");
        this->currentTableName = "CurrentPlayList";
    }
    // qDebug()<<;
}

PlayListItemService::PlayListItemService(const QString &tableName):BaseService<PlayListItem>(PlayListItem::TableName + tableName)
{
    this->currentTableName = PlayListItem::TableName + tableName;
}

QList<Music> PlayListItemService::GetPlayingList(QString orderCriteria, SortOrder orderType)
{
    QString orderStr;
    if(orderType == Asc)orderStr = "asc";
    else if(orderType == Desc)orderStr = "desc";

    QString str = QString("select Music.* from Music, %1 where Music.Id = %1.MusicId order by %1.%2 %3;")
                      .arg(this->currentTableName).arg(orderCriteria).arg(orderStr);
    QSqlQuery query(str);
    QList<Music> musics;
    while (query.next())
    {
        Music music;
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

bool PlayListItemService::UpdateNewList(const QList<Music> &list)
{
    //删除原来的记录
    this->Clear();
    //添加新的记录
    foreach (auto music, list) {
        PlayListItem item;
        item.setMusicId(music.Id());
        this->Add(item);
    }
    return true;
}
