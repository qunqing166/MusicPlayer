#include "PlayListService.h"

// void PlayListService::GetMusicList(const QString &name)
// {
//     QString str = QString("select * from Music")
//     QSqlQuery query;
// }

PlayListService::PlayListService(const QString &tableName)
{
    this->tableName = tableName;
}

QList<MusicDto> PlayListService::GetMusicList()
{
    QString str = QString("select Music.* from Music, %1 where Music.Id = %1.MusicId;").arg(this->tableName);
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

QList<MusicDto> PlayListService::GetMusicList(const QString &name)
{
    QString str = QString("select Music.* from Music, %1 where Music.Id = %1.MusicId;").arg(name);
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
