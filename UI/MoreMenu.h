#pragma once

#include <QWidget>
#include <QPushButton>
#include "ToolButton.h"
#include <QTimer>
// #include "ClickedEventFilter.h"

enum MenuOperate
{
    Play,
    AddToNext,
    AddToList,
    Remove
};

class MoreMenu:public QWidget
{
    Q_OBJECT

    QPushButton *btnPlay;
    QPushButton *btnPlayNext;
    ToolButton *btnAddToList;
    QPushButton *btnRemoveFromList;

    static MoreMenu* instance;
    // ClickedEventFilter *clickedFilter;

public:
    MoreMenu(QWidget *parent = nullptr);
    ~MoreMenu();

    static MoreMenu* Instance();

private:
    void ObjectInit();
    void WidgetInit();

    QMenu *CreateSelectList() const;

protected:
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

signals:
    void Operate(const MenuOperate &op);
};
