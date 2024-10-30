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

bool PlayListService::Add(const PlayListDto &info)
{
    QSqlQuery query;

    QString str1 = QString("select count(*) as count_value from PlayList where ListName = '%1'").arg(info.ListName());

    query.exec(str1);
    query.next();
    // qDebug()<<"num: "<<query.value("count_value");

    if(query.value("count_value").toInt() != 0)
        return false;

    BaseService<PlayListDto>::Add(info);

    QString str = QString("CREATE TABLE PlayList_%1 ("
                          "Id  INTEGER PRIMARY KEY NOT NULL,"
                          "CreateTime TEXT    NOT NULL,"
                          "UpdateTime TEXT    NOT NULL,"
                          "MusicId    INTEGER NOT NULL"
                          ");").arg(info.ListName());
    // QSqlQuery query;
    return query.exec(str);
    // qDebug()<<query.lastError().text();
}


// PlayListDto PlayListService::GetOne(const QString &listName)
// {
//     QString str = QString("select * from %1 where ListName = %2;").arg(tableName).arg(listName);
//     QSqlQuery query(str);
//     query.next();
//     // return query;
//     PlayListDto playList;
//     DataBaseService::QueryToObject(&playList, query);
//     return playList;
// }
