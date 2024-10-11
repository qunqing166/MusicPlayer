#ifndef PLAYLISTINFO_H
#define PLAYLISTINFO_H

#include "BaseInfo.h"
#include <QJsonObject>

class PlayListInfo:public BaseInfo
{
public:
    QString listName = "新建歌单";
    QString creator = "";
    QString coverImagePath = ":/scr/icon/cover_empty.png";
    int count = 0;

    static QString ThisName(){return "PlayList";}

    QJsonObject ToJson()
    {
        QJsonObject json = BaseInfo::ToJson();
        json.insert("ListName", listName);
        json.insert("Creator", creator);
        json.insert("CoverImagePath", coverImagePath);
        json.insert("Count", count);
        return json;
    }

    void FromJson(QJsonObject json)
    {
        listName = json.value("ListName").toString();
        creator = json.value("Creator").toString();
        coverImagePath = json.value("CoverImagePath").toString();
        count = json.value("Count").toInt();
        BaseInfo::FromJson(json);
    }
};

// QString PlayListInfo::ThisName = "PlayList";

#endif // PLAYLISTINFO_H
