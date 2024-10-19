#pragma once

#include "../ImageLabel.h"
#include <QLabel>
#include <QWidget>
#include "../Dtos/PlayListDto.h"

class IndexPlayListItem:public QWidget
{
    Q_OBJECT

    int width = 120;
    PlayListDto playListInfo;
    ImageLabel *imageLabel;

public:
    IndexPlayListItem(const PlayListDto &playList, QWidget *parent = nullptr);
    int Width(){return width;}

    // ImageLabel *getImageLabel() const{return imageLabel;}

signals:
    void OpenPlayList(const PlayListDto &info);

    // void SetPlayList
};
