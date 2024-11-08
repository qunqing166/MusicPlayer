#include "PlayListService.h"
#include "../Dtos/UserDto.h"

using namespace Model;
using namespace Service;

PlayListService::PlayListService(const QString &tableName)
{
    this->tableName = tableName;
}

QList<Music> PlayListService::GetMusicList()
{
    QString str = QString("select Music.* from Music, %1 where Music.Id = %1.MusicId;").arg(this->tableName);
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

QList<Music> PlayListService::GetMusicList(const QString &name)
{
    QString str = QString("select Music.* from Music, %1 where Music.Id = %1.MusicId;").arg(name);
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

bool PlayListService::Add(const PlayList &info)
{
    QSqlQuery query;

    QString str1 = QString("select count(*) as count_value from PlayList where ListName = '%1'").arg(info.ListName());

    query.exec(str1);
    query.next();
    // qDebug()<<"num: "<<query.value("count_value");

    if(query.value("count_value").toInt() != 0)
        return false;
    
    BaseService<PlayList>::Add(info);

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

QList<PlayList> PlayListService::GetPlayListFromUser()
{
    int id = User::MyUserInfo()->Id();
    return this->GetAllByParameter("CreatorId", id);
}

QList<PlayList> PlayListService::GetPlayListFromUser(int id)
{
    return this->GetAllByParameter("CreatorId", id);
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
