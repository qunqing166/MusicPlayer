#pragma once

#include "../ImageLabel.h"
#include <QLabel>
#include <QWidget>
#include "../Dtos/PlayListDto.h"

class IndexPlayListItem:public QWidget
{
    Q_OBJECT

    int width = 120;
    Model::PlayList playListInfo;
    ImageLabel *imageLabel;

public:
    IndexPlayListItem(const Model::PlayList &playList, QWidget *parent = nullptr);
    int Width(){return width;}

signals:
    void OpenPlayList(const Model::PlayList &info);

};
