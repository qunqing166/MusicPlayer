#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "PlayListContentView.h"
#include <QStackedWidget>
#include "UI/SidePlayListBar.h"

class MainWidget:public QStackedWidget
{
    Q_OBJECT

    PlayListContentView *contentView;


public:
    MainWidget(QWidget *parent = nullptr);

    PlayListContentView *getContentView() const;

    SidePlayListBar *sideBar;
private:
    void ObjectInit();
    void WidgetInit();
    Q_PROPERTY(PlayListContentView *contentView READ getContentView CONSTANT FINAL)
};

#endif // MAINWIDGET_H
