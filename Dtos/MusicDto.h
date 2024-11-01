#pragma once
#ifndef MUSICDTO_H
#define MUSICDTO_H

#include "BaseDto.h"
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>

class MusicDto:public BaseDto
{
    Q_OBJECT

    QString musicName = "";
    QString musicPath = "";
    QString singers = "";
    QString album = "";
    QTime duration = QTime(0,0,0);
    QString coverImagePath = ":/scr/icon/cover_empty.png";
    QJsonArray belongingPlayList;


public:

    MusicDto()
    {
        int r = rand() % 2 + 1;
        coverImagePath = QString(":/scr/image/default_cover%1").arg(r);
    }

    const static QString TableName;


    void InsertPlayList(const QString &playListName);
    void RemovePlayList(const QString &playListName);

    QString MusicName() const;
    void setMusicName(const QString &value);

    QString MusicPath() const;
    void setMusicPath(const QString &value);

    QString Singers() const;
    void setSingers(const QString &value);

    QString Album() const;
    void setAlbum(const QString &value);

    QString Duration() const;
    void setDuration(const QString &value);

    QString CoverImagePath() const;
    void setCoverImagePath(const QString &value);

    QString BelongingPlayList() const;
    void setBelongingPlayList(const QString &value);

signals:
    void MusicNameChanged(QString MusicName);

    void MusicPathChanged(QString MusicPath);

    void SingersChanged(QString singers);

    void AlbumChanged(QString album);

    void DurationChanged(QString duration);

    void BelongingPlayListChanged();

    void CoverImagePathChanged();

private:

    Q_PROPERTY(QString Album READ Album WRITE setAlbum NOTIFY AlbumChanged FINAL)
    Q_PROPERTY(QString MusicName READ MusicName WRITE setMusicName NOTIFY MusicNameChanged FINAL)
    Q_PROPERTY(QString MusicPath READ MusicPath WRITE setMusicPath NOTIFY MusicPathChanged FINAL)
    Q_PROPERTY(QString Singers READ Singers WRITE setSingers NOTIFY SingersChanged FINAL)
    Q_PROPERTY(QString Duration READ Duration WRITE setDuration NOTIFY DurationChanged FINAL)
    Q_PROPERTY(QString CoverImagePath READ CoverImagePath WRITE setCoverImagePath NOTIFY CoverImagePathChanged FINAL)
    Q_PROPERTY(QString BelongingPlayList READ BelongingPlayList WRITE setBelongingPlayList NOTIFY BelongingPlayListChanged FINAL)
};

inline const QString MusicDto::TableName = "Music";

#endif

inline void MusicDto::InsertPlayList(const QString &playListName)
{
    belongingPlayList.append(playListName);
}

inline void MusicDto::RemovePlayList(const QString &playListName)
{
    if(!belongingPlayList.contains(playListName))
        return;
    for(int i = 0; i < belongingPlayList.count(); i++)
    {
        if(belongingPlayList.at(i).toString() == playListName)
        {
            belongingPlayList.removeAt(i);
            return;
        }
    }
}

inline QString MusicDto::MusicName() const
{
    return musicName;
}

inline void MusicDto::setMusicName(const QString &value)
{
    if (musicName == value)
        return;
    musicName = value;
    // emit MusicNameChanged(musicName);
}

inline QString MusicDto::MusicPath() const
{
    return musicPath;
}

inline void MusicDto::setMusicPath(const QString &value)
{
    if (musicPath == value)
        return;
    musicPath = value;
    // emit MusicPathChanged(musicPath);
}

inline QString MusicDto::Singers() const
{
    return singers;
}

inline void MusicDto::setSingers(const QString &value)
{
    if (singers == value)
        return;
    singers = value;
    // emit SingersChanged(singers);
}

inline QString MusicDto::Album() const
{
    return album;
}

inline void MusicDto::setAlbum(const QString &value)
{
    if (album == value)
        return;
    album = value;
    // emit AlbumChanged(album);
}

inline QString MusicDto::Duration() const
{
    return duration.toString("mm:ss");
}

inline void MusicDto::setDuration(const QString &value)
{
    duration = QTime::fromString(value, "mm:ss");
    // emit DurationChanged(duration);
}

inline QString MusicDto::CoverImagePath() const
{
    return coverImagePath;
}

inline void MusicDto::setCoverImagePath(const QString &value)
{
    coverImagePath = value;
}

inline QString MusicDto::BelongingPlayList() const
{
    return QString(QJsonDocument(belongingPlayList).toJson(QJsonDocument::Compact));
}

inline void MusicDto::setBelongingPlayList(const QString &value)
{
    belongingPlayList = QJsonDocument::fromJson(value.toUtf8()).array();
}
