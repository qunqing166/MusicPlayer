#pragma once

#include <QWidget>
#include <QPushButton>
#include "ToolButton.h"
#include <QTimer>

class MoreMenu:public QWidget
{
    Q_OBJECT

    QPushButton *btnPlay;
    QPushButton *btnPlayNext;
    ToolButton *btnAddToList;
    QPushButton *btnRemoveFromList;

public:
    MoreMenu(QWidget *parent = nullptr);

    QPushButton *BtnPlay() const{return btnPlay;}
    QPushButton *BtnPlayNext() const{return btnPlayNext;}

private:
    void ObjectInit();
    void WidgetInit();

    QMenu *CreateSelectList() const;

// signals:
//     void Play();
//     void AddToNext();
};
