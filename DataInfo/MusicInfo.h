#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QObject>
#include <QList>
#include <QTime>
#include "BaseInfo.h"
#include <QJsonObject>

class MusicInfo:public BaseInfo
{
public:
    // MusicInfo(){}
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
    QString musicPath = "C:\\Users\\qunqing\\Desktop\\音乐\\Liyue 璃月-Laura Brehm,HOYO-MiX.320.mp3";
    QString coverImagePath = "C:\\Users\\qunqing\\Desktop\\图片\\liyue.webp";
    QString musicName = "Liyue 璃月";
    QString album = "皎月云间之梦";
    QString singers = "陈致逸, mihoyo";
    QTime duration = QTime(0,4,36);

    QJsonObject ToJson()
    {
        QJsonObject json = BaseInfo::ToJson();
        json.insert("MusicPath", musicPath);
        json.insert("CoverImagePath", coverImagePath);
        json.insert("MusicName", musicName);
        json.insert("Album", album);
        json.insert("Singers", singers);
        json.insert("Duration", duration.toString("mm:ss"));
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
        BaseInfo::FromJson(json);
    }



};

#endif // MUSICINFO_H
