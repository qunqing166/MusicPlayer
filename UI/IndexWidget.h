#pragma once

#include <QWidget>
#include "../Model/Music.h"
#include <QLabel>
#include "PlayListView.h"
#include "../Model/PlayList.h"
#include "ImageLabel.h"

class IndexWidget : public QWidget
{
    Q_OBJECT

    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    PlayListView *playList;
    QList<Model::PlayList> myPlayList;
    QListWidget *listWidget;
    ImageLabel *imageLabel;

public:
    explicit IndexWidget(QWidget *parent = nullptr);
    
    void SetCurrentMusicInfo(const Model::Music &music);
    void SetCurrentPlayList();
    void OnCurrentPlayListChanged(int index, const QList<Model::Music> &list);
    void SetPlayList();

    PlayListView *getPlayList() const{return playList;}

private:

    void ObjectInit();
    void WidgetInit();

    void UpdatePlayListWidget();

    void InitPlayList();


signals:
    void OpenPlayList(const Model::PlayList &info);
};
