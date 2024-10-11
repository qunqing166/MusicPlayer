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
    bool IsInTitleBar(QPoint pos);


    MainWidget *getMainWidget() const;

    PlayerBar *getPlayerBar() const;

    SelectBar *getSelectBar() const;

    TitleBar *getTitleBar() const;

private:
    void ObjectInit();
    void WidgetInit();

    Q_PROPERTY(MainWidget *mainWidget READ getMainWidget CONSTANT FINAL)

    Q_PROPERTY(PlayerBar *playerBar READ getPlayerBar CONSTANT FINAL)

    Q_PROPERTY(SelectBar *selectBar READ getSelectBar CONSTANT FINAL)

    Q_PROPERTY(TitleBar *titleBar READ getTitleBar CONSTANT FINAL)

signals:
    void Maximize();
    void Minimize();
};

#endif // CENTRALWIDGET_H
