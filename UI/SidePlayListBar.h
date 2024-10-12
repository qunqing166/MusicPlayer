#ifndef SIDEPLAYLISTBAR_H
#define SIDEPLAYLISTBAR_H

#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTimer>
#include "ClickedEventFilter.h"

class SidePlayListBar:public QWidget
{
    Q_OBJECT

    QPushButton *pbClose;
    QPropertyAnimation *geoAnima;
    int dWidth = 0;
    const int maxWidth = 250;
    QRect parentGeo;
    bool isOpen = false;
    ClickedEventFilter *clickFilter;
    bool isButtonDrive = true;

public:
    SidePlayListBar(QWidget *parent = nullptr);
    void Open(QRect geo);
    void SetIsOpenDrive(bool is){this->isButtonDrive = is;}
    int getDWidth() const;
    void setDWidth(int newWidth);
    bool GetOpenStatus(){return this->isOpen;}
    void Open(int height);
    void Close();

signals:
    void DWidthChanged();

private:
    void ObjectInit();
    void WidgetInit();
    void OnAnimationFinished();
    void OnMousePressed(const QPoint &pos);


    Q_PROPERTY(int DWidth READ getDWidth WRITE setDWidth NOTIFY DWidthChanged FINAL)
};

#endif // SIDEPLAYLISTBAR_H
