#ifndef SIDEPLAYLISTITEM_H
#define SIDEPLAYLISTITEM_H

#include <QWidget>
#include "../ImageLabel.h"
#include <QPushButton>
#include "../Dtos/MusicDto.h"

class SidePlayListItem:public QWidget
{

    ImageLabel *image;
    QLabel *musicName;
    QLabel *singers;
    QPushButton *pbMore;
    QPushButton *pbDel;

    MusicDto info;

public:
    SidePlayListItem(const MusicDto &info, QWidget *parent = nullptr);
    void SetMusicInfo(const MusicDto &info);

private:
    void ObjectInit();
    void WidgetInit();
};

#endif // SIDEPLAYLISTITEM_H
