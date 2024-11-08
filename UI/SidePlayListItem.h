#ifndef SIDEPLAYLISTITEM_H
#define SIDEPLAYLISTITEM_H

#include <QWidget>
#include "ImageLabel.h"
#include <QPushButton>
#include "../Model/Music.h"

class SidePlayListItem:public QWidget
{

    QLabel *index;
    ImageLabel *image;
    QLabel *musicName;
    QLabel *singers;
    QPushButton *pbMore;
    QPushButton *pbDel;
    
    Model::Music info;

public:
    SidePlayListItem(int index, const Model::Music &info, QWidget *parent = nullptr);
    void SetMusicInfo(const Model::Music &info);

private:
    void ObjectInit();
    void WidgetInit();
};

#endif // SIDEPLAYLISTITEM_H
