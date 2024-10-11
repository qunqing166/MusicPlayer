#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
// #include "AnimationButton.h"
#include <QPropertyAnimation>
#include <QListView>
#include <QListWidget>
#include "DataInfo/PlayListInfo.h"
#include <QStandardItemModel>

class PlayList:public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int Angle READ Angle WRITE setAngle NOTIFY AngleChanged FINAL)
    Q_PROPERTY(int ListHeight READ ListHeight WRITE setListHeight NOTIFY ListHeightChanged FINAL)

    QLabel *labelInfo;
    QPushButton *pbAdd;
    QPushButton *pbOpen;
    QListView *listView;

    QPropertyAnimation *pbOpenAnima;
    QPropertyAnimation *listHeiAnima;
    int angle = 180;
    int listHeight = 0;
    bool isContentOPen = false;

    QString title;
    QString listName = "新建歌单";

    QList<PlayListInfo> playLists;
    QString thisName;
    QStandardItemModel *model;

public:
    PlayList(QString title, QWidget *parent = nullptr);
    static QPixmap GetRadiusPiamap(QPixmap pixmap, int radius);
    void setTitle(QString value);
    void SetThisName(QString value){this->thisName = value;}

    // void SetIsOPen(bool value);

private:
    void ObjectInit();
    void WidgetInit();
    void DataInit();

    void setAngle(int value){this->angle = value;}
    int Angle(){return this->angle;}
    void setListHeight(int value){this->listHeight = value;}
    int ListHeight(){return this->listHeight;}


private slots:
    void OnPbOpenClicked();

signals:
    void AngleChanged();
    void ListHeightChanged();
    void OpenPlayList(const PlayListInfo &info);
};

#endif // PLAYLIST_H
