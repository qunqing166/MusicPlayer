#include "ToolButton.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

ToolButton::ToolButton(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    this->setLayout(hLayout);
    // hLayout->setContentsMargins(0,0,0,0);

    btn1 = new QPushButton(this);
    QPushButton *btn2 = new QPushButton(this);
    btn1->setObjectName("tool_btn");
    btn2->setObjectName("tool_btn");
    // btn2->setMaximumWidth(20);
    hLayout->addWidget(btn1, Qt::AlignLeft);
    hLayout->addWidget(new QLabel(this));
    hLayout->addWidget(btn2, Qt::AlignRight);
    btn2->setIcon(QIcon(":/scr/icon/arrow_right.png"));

    btn1->setStyleSheet("background-color: transparent;"
                        "color: #666666;");
    btn2->setStyleSheet("background-color: transparent;"
                        "color: #666666;");
}

void ToolButton::SetIcon(const QIcon &icon)
{
    btn1->setIcon(icon);
}

void ToolButton::SetText(const QString &text)
{
    btn1->setText(text);
}

void ToolButton::enterEvent(QEnterEvent *event)
{
    btn1->setStyleSheet("background-color: transparent;"
                        "color: rgb(49, 165, 255);");
    emit Hover();
}

void ToolButton::leaveEvent(QEvent *event)
{
    btn1->setStyleSheet("background-color: transparent;"
                        "color: #666666;");
}
