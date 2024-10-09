#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QObject>
#include <QList>
#include <QTime>

class MusicInfo
{
public:
    QString musicPath = "C:\\Users\\qunqing\\Desktop\\音乐\\Liyue 璃月-Laura Brehm,HOYO-MiX.320.mp3";
    QString coverImagePath = "C:\\Users\\qunqing\\Desktop\\图片\\liyue.webp";
    QString musicName = "Liyue 璃月";
    QString album = "皎月云间之梦";
    QList<QString> singers{ "陈致逸", "mihoyo"};
    QTime duration = QTime(0,4,36);
};

#endif // MUSICINFO_H
