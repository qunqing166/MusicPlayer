#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
// #include "AnimationButton.h"
#include <QPropertyAnimation>
#include <QListView>
#include <QListWidget>

class PlayList:public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int Angle READ Angle WRITE setAngle NOTIFY AngleChanged FINAL)
    Q_PROPERTY(int ListHeight READ ListHeight WRITE setListHeight NOTIFY ListHeightChanged FINAL)

    QLabel *labelInfo;
    QPushButton *pbAdd;
    QPushButton *pbOpen;
    // QListView *listView;
    // QListWidget *listWidget;
    QListView *listView;

    QPropertyAnimation *pbOpenAnima;
    QPropertyAnimation *listHeiAnima;
    int angle = 180;
    int listHeight = 0;
    bool isContentOPen = false;

    QString title;

public:
    PlayList(QWidget *parent = nullptr);
    static QPixmap GetRadiusPiamap(QPixmap pixmap, int radius);
    void setTitle(QString value);

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
};

#endif // PLAYLIST_H
