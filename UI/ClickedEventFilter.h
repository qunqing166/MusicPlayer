#ifndef CLICKEDEVENTFILTER_H
#define CLICKEDEVENTFILTER_H

#include <QObject>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>

class ClickedEventFilter:public QObject
{
    Q_OBJECT

public:
    ClickedEventFilter(QObject *parent = nullptr):QObject(parent)
    {

    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            emit MousePressed(mouseEvent->globalPosition().toPoint());
            return false;
        }
        return QObject::eventFilter(obj, event);
    }

signals:
    void MousePressed(const QPoint &pos);
};

#endif // CLICKEDEVENTFILTER_H
