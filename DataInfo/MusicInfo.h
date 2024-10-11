#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QObject>
#include <QList>
#include <QTime>
#include "BaseInfo.h"
#include <QJsonObject>
#include <QDataStream>
#include <QJsonArray>
#include <QJsonDocument>

class MusicInfo:public BaseInfo
{
public:
    // MusicInfo()
    // {
    //     setThisName("Music");
    // }
    // MusicInfo(QObject *parent = nullptr):BaseInfo(parent){}
    // MusicInfo(const MusicInfo &a):BaseInfo(a)
    // {
    //     this->musicName = a.musicName;
    //     this->musicPath = a.musicPath;
    //     this->coverImagePath = a.coverImagePath;
    //     this->album = a.album;
    //     this->singers = a.singers;
    //     this->duration = a.duration;
    //     // this->setParent(a.parent());
    // }
    QString musicPath = "";
    QString coverImagePath = "";
    QString musicName = "未知";
    QString album = "未知";
    QString singers = "未知";
    QJsonArray belongingPlayList;
    QTime duration = QTime(0, 0, 0);

    static QString ThisName(){return "Music";}

    QJsonObject ToJson()
    {
        QJsonObject json = BaseInfo::ToJson();
        json.insert("MusicPath", musicPath);
        json.insert("CoverImagePath", coverImagePath);
        json.insert("MusicName", musicName);
        json.insert("Album", album);
        json.insert("Singers", singers);
        json.insert("Duration", duration.toString("mm:ss"));
        json.insert("BelongingPlayList", QString(QJsonDocument(belongingPlayList).toJson(QJsonDocument::Compact)));
        // belongingPlayList
        // qDebug()<<json.value("BelongingPlayList").toString();
        return json;
    }

    void FromJson(QJsonObject json)
    {
        musicPath = json.value("MusicPath").toString();
        coverImagePath = json.value("CoverImagePath").toString();
        musicName = json.value("MusicName").toString();
        album = json.value("Album").toString();
        singers = json.value("Singers").toString();
        duration = QTime::fromString(json.value("Duration").toString(),"mm:ss");
        belongingPlayList = QJsonDocument::fromJson(json.value("BelongingPlayList").toString().toUtf8()).array();
        BaseInfo::FromJson(json);
    }

private:
    // QString ListToString()
    // {
    //     // QDataStream stream()
    //     QString str = "";
    //     QTextStream stream(&str);
    //     foreach (auto s, this->belongingPlayList) {
    //         stream << s;
    //     }
    //     qDebug() << str;
    //     return str;
    // }

    // void ListFromString(QString)
    // {
    //     QString str = "";
    //     QTextStream stream(&str);
    //     // stream.
    //     qDebug() << str;
    // }
};

// QString MusicInfo::ThisName = "Music";

#endif // MUSICINFO_H
