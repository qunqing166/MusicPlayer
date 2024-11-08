#pragma once
#ifndef PLAYLISTDTO_H
#define PLAYLISTDTO_H

#include "BaseDto.h"

namespace Model
{

class PlayList:public Base
{
    Q_OBJECT

    QString listName = "新建歌单";
    int creatorId = 0;
    QString coverImagePath = ":/scr/icon/cover_empty.png";
    int count = 0;

public:
    PlayList(){}

    const static QString TableName;

    QString ListName() const;
    void setListName(const QString &value);

    QString CoverImagePath() const;
    void setCoverImagePath(const QString &value);

    int Count() const;
    void setCount(int value);

    int CreatorId() const;
    void setCreatorId(int value);

signals:
    void ListNameChanged(QString listName);

    void CreatorChanged(QString creator);

    void CoverImagePathChanged(QString coverImagePath);

    void CountChanged(int count);

    void CreatorIdChanged(int creatorId);

private:
    Q_PROPERTY(QString ListName READ ListName WRITE setListName NOTIFY ListNameChanged FINAL)
    Q_PROPERTY(QString CoverImagePath READ CoverImagePath WRITE setCoverImagePath NOTIFY CoverImagePathChanged FINAL)
    Q_PROPERTY(int Count READ Count WRITE setCount NOTIFY CountChanged FINAL)
    Q_PROPERTY(int CreatorId READ CreatorId WRITE setCreatorId NOTIFY CreatorIdChanged FINAL)
};

inline const QString PlayList::TableName = "PlayList";

inline QString PlayList::CoverImagePath() const
{
    return coverImagePath;
}

inline void PlayList::setCoverImagePath(const QString &value)
{
    if (coverImagePath == value)
        return;
    coverImagePath = value;
    emit CoverImagePathChanged(coverImagePath);
}

inline int PlayList::Count() const
{
    return count;
}

inline void PlayList::setCount(int value)
{
    if (count == value)
        return;
    count = value;
    emit CountChanged(count);
}

inline int PlayList::CreatorId() const
{
    return creatorId;
}

inline void PlayList::setCreatorId(int value)
{
    if (creatorId == value)
        return;
    creatorId = value;
    emit CreatorIdChanged(creatorId);
}

inline QString PlayList::ListName() const
{
    return listName;
}



inline void PlayList::setListName(const QString &value)
{
    if (listName == value)
        return;
    listName = value;
    emit ListNameChanged(listName);
}

}

#endif
