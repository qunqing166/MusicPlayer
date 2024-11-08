#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "TitleBar.h"
#include "SelectBar.h"
#include "PlayerBar.h"
#include "MainWidget.h"

class CentralWidget:public QWidget
{
    Q_OBJECT

    TitleBar *titleBar;
    SelectBar *selectBar;
    PlayerBar *playerBar;
    MainWidget *mainWidget;

public:

    CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget();
    bool IsInTitleBar(QPoint pos);

    MainWidget *getMainWidget() const;

    PlayerBar *getPlayerBar() const;

    SelectBar *getSelectBar() const;

    TitleBar *getTitleBar() const;

private:
    void ObjectInit();
    void WidgetInit();

signals:
    void Maximize();
    void Minimize();
    void ChangeOpenSideBarStatus();
};

#endif // CENTRALWIDGET_H
