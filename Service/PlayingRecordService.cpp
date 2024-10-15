#include "PlayingRecordService.h"

PlayingRecordService::PlayingRecordService(PlayingRecordType type)
{
    if(type == PlayingCurrent)
    {
        this->currentTableName = "CurrentPlayList";
        BaseService<PlayingRecordDto>("CurrentPlayList");
    }
    else
    {
        BaseService<PlayingRecordDto>("CurrentPlayList");
        this->currentTableName = "CurrentPlayList";
    }
    // qDebug()<<;
}

PlayingRecordService::PlayingRecordService(const QString &tableName):BaseService<PlayingRecordDto>(tableName)
{
    this->currentTableName = tableName;
}



QList<MusicDto> PlayingRecordService::GetPlayingList()
{
    QString str = QString("select Music.* from Music, %1 where Music.Id = %1.MusicId;").arg(this->currentTableName);
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
