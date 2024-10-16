#include "MusicService.h"

MusicService::MusicService() {}

QList<MusicDto> MusicService::GetAllByTableName(const QString &tableName)
{
    QString str = QString("select * from Music where BelongingPlayList like '%%1%' order by UpdateTime desc").arg(tableName);
    QSqlQuery query(str);
    QList<MusicDto> musics;
    while(query.next())
    {
        MusicDto music;
        DataBaseService::QueryToObject(&music, query);
        musics.append(music);
    }
    return musics;
}
