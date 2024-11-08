#include "MusicService.h"

using namespace Service;
using namespace Model;

MusicService::MusicService() {}

QList<Music> MusicService::GetAllByTableName(const QString &tableName)
{
    QString str = QString("select * from Music where BelongingPlayList like '%%1%' order by UpdateTime desc").arg(tableName);
    QSqlQuery query(str);
    QList<Music> musics;
    while(query.next())
    {
        Music music;
        DataBaseService::QueryToObject(&music, query);
        musics.append(music);
    }
    return musics;
}
