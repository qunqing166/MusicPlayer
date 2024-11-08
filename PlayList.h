#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QListView>
#include <QListWidget>
#include <QStandardItemModel>
#include <QSharedPointer>
#include "Dtos/PlayListDto.h"
#include "UI/PlayListEditor.h"
#include <QPointer>

namespace UI
{

//显示歌单的列表
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
    
    QList<Model::PlayList> playLists;
    QString thisName;
    QStandardItemModel *model;

    QPointer<PlayListEditor> playListEditor;
    QList<QStandardItem*>items;

public:
    PlayList(QString title, QWidget *parent = nullptr);

    //更新数据
    void UpdateData();

    void setTitle(QString value);
    void SetThisName(QString value){this->thisName = value;}

private:
    void ObjectInit();
    void WidgetInit();
    void DataInit();

    void setAngle(int value){this->angle = value;}
    int Angle(){return this->angle;}
    void setListHeight(int value){this->listHeight = value;}
    int ListHeight(){return this->listHeight;}
    void CreateNewPlayList(const Model::PlayList &newList);


private slots:
    void OnPbOpenClicked();

signals:
    void AngleChanged();
    void ListHeightChanged();
    //打开歌单的信号
    void OpenPlayList(const Model::PlayList &info);
    // void PlayListChanged();
};

}

#endif // PLAYLIST_H
