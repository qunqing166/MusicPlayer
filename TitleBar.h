#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class TitleBar :public QWidget
{
    Q_OBJECT

    QPushButton* pbQuit;
    QPushButton* pbMin;
    QPushButton* pbMax;
    QLabel* labelEmpty;
    QLabel* labelTitle;
    bool isDragged = false;
    QPoint lastPos;
public:
    TitleBar(QWidget* parent = nullptr);

private:
    void WidgetInit();

signals:
    void PbMaxClicked();
    void PbMinClicked();
};

#endif // TITLEBAR_H
