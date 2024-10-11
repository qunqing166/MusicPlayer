#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QWidget>
#include <QLabel>
#include "ImageLabel.h"
#include <QPushButton>
// #include "Service/DataBaseService.h"
#include "DataInfo/MusicInfo.h"

class PlayListItem:public QWidget
{
    Q_OBJECT

    QLabel *index;
    ImageLabel *image;
    QLabel *songName;
    QLabel *singers;
    QLabel *album;
    QLabel *duration;
    QPushButton *pbMore;

    MusicInfo musicInfo;

public:
    PlayListItem(MusicInfo value, QWidget *parent = nullptr);
    void SetData(MusicInfo value);

    MusicInfo getMusicInfo() const;

private:
    void ObjectInit();
    void WidgetInit();
    Q_PROPERTY(MusicInfo musicInfo READ getMusicInfo CONSTANT FINAL)
};

#endif // PLAYLISTITEM_H
