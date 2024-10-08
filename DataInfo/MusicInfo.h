#ifndef MUSICINFO_H
#define MUSICINFO_H

#include <QObject>
#include <QList>
#include <QTime>

class MusicInfo
{
public:
    QString musicPath = "C:\\Users\\qunqing\\Desktop\\音乐\\Liyue 璃月-Laura Brehm,HOYO-MiX.320.mp3";
    QString coverImagePath = "C:\\Users\\qunqing\\Desktop\\图片\\d1b8370ff9fa8335e8065414fa2524005d663847.png@1000w_1000h_1c.webp";
    QString musicName = "Liyue 璃月";
    QString album = "皎月云间之梦";
    QList<QString> singers{ "陈致逸", "mihoyo"};
    QTime duration = QTime(0,4,36);
};

#endif // MUSICINFO_H
