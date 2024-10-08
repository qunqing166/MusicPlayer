#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "TitleBar.h"
#include "SelectBar.h"
#include "PlayerBar.h"

class CentralWidget:public QWidget
{
    Q_OBJECT

    TitleBar *titleBar;
    SelectBar *selectBar;
    PlayerBar *playerBar;

public:


    CentralWidget(QWidget *parent = nullptr);
    bool IsInTitleBar(QPoint pos);

private:
    void ObjectInit();
    void WidgetInit();

signals:
    void Maximize();
    void Minimize();
};

#endif // CENTRALWIDGET_H
