#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "PlayListContentView.h"
#include <QStackedWidget>
#include "UI/SidePlayListBar.h"
#include "UI/IndexWidget.h"
#include <QStackedLayout>

class MainWidget:public QWidget
{
    Q_OBJECT

    PlayListContentView *contentView;
    SidePlayListBar *sideBar;
    IndexWidget *indexWidget;
    QStackedLayout *stackedLayout;
    int indexInit;

public:
    MainWidget(QWidget *parent = nullptr);
    MainWidget(int index, QWidget *parent = nullptr);

    PlayListContentView *getContentView() const;

    SidePlayListBar *getSideBar() const;

    void ToIndex();
    void ToPlayList();

private:
    void ObjectInit();
    void WidgetInit();
    Q_PROPERTY(PlayListContentView *contentView READ getContentView CONSTANT FINAL)
};

#endif // MAINWIDGET_H
