#pragma once

#include <QWidget>
#include "../Dtos/MusicDto.h"
#include <QLabel>
#include "../PlayListView.h"
#include "../Dtos/PlayListDto.h"
#include "../ImageLabel.h"

class IndexWidget : public QWidget
{
    Q_OBJECT

    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    PlayListView *playList;
    QList<PlayListDto> myPlayList;
    QListWidget *listWidget;
    ImageLabel *imageLabel;

public:
    explicit IndexWidget(QWidget *parent = nullptr);

    void SetCurrentMusicInfo(const MusicDto &music);
    void SetCurrentPlayList();
    void OnCurrentPlayListChanged(int index, const QList<MusicDto> &list);
    void SetPlayList();

    PlayListView *getPlayList() const{return playList;}

private:

    void ObjectInit();
    void WidgetInit();

    void UpdatePlayListWidget();

    void InitPlayList();


signals:
    void OpenPlayList(const PlayListDto &info);
};
