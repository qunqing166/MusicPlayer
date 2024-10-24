#pragma once

#include <QWidget>
#include <QPushButton>
#include "ToolButton.h"
#include <QTimer>
// #include "ClickedEventFilter.h"

class MoreMenu:public QWidget
{
    Q_OBJECT

    QPushButton *btnPlay;
    QPushButton *btnPlayNext;
    ToolButton *btnAddToList;
    QPushButton *btnRemoveFromList;

    static MoreMenu* thisObj;
    // ClickedEventFilter *clickedFilter;

public:
    MoreMenu(QWidget *parent = nullptr);
    ~MoreMenu();

    QPushButton *BtnPlay() const{return btnPlay;}
    QPushButton *BtnPlayNext() const{return btnPlayNext;}

    static MoreMenu* Create()
    {
        if(thisObj == nullptr)
        {
            thisObj = new MoreMenu();
        }
        return thisObj;
    }

private:
    void ObjectInit();
    void WidgetInit();

    QMenu *CreateSelectList() const;

protected:
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

signals:
    void Play();
    void AddToNext();
    void Remove();
};

inline MoreMenu *MoreMenu::thisObj = nullptr;
