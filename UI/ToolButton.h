#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ToolButton:public QWidget
{
    Q_OBJECT

    QPushButton *btn1;

public:
    ToolButton(QWidget *parent = nullptr);

    void SetIcon(const QIcon &icon);
    void SetText(const QString &text);
    void SetIconEnd(const QPixmap &icon);

protected:
    virtual void enterEvent(QEnterEvent *event) override;
     virtual void leaveEvent(QEvent *event) override;

signals:
    void Hover();
};
