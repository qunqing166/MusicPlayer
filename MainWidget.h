#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "PlayListContentView.h"
#include <QStackedWidget>

class MainWidget:public QStackedWidget
{
    Q_OBJECT

    PlayListContentView *contentView;

public:
    MainWidget(QWidget *parent = nullptr);

    PlayListContentView *getContentView() const;

private:
    void ObjectInit();
    void WidgetInit();
    Q_PROPERTY(PlayListContentView *contentView READ getContentView CONSTANT FINAL)
};

#endif // MAINWIDGET_H
