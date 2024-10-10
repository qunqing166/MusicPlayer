#include "AnimationButton.h"
#include <QPainter>

AnimationButton::AnimationButton(QWidget *parent) :QWidget(parent)
{
    angleAnima = new QPropertyAnimation(this, "Angle");
    // angleAnima->setStartValue(0);
    // angleAnima->setEndValue(180);
    angleAnima->startTimer(500);
    connect(angleAnima, &QPropertyAnimation::valueChanged, this, [&](){this->update();});
}

void AnimationButton::SetIcon(QImage image1, QImage image2)
{
    this->image1 = image1;
    this->image2 = image2;
}

void AnimationButton::mousePressEvent(QMouseEvent *event)
{
    if(status)
    {
        angleAnima->setStartValue(0);
        angleAnima->setEndValue(180);
    }
    else
    {
        angleAnima->setStartValue(180);
        angleAnima->setEndValue(0);
    }
    status = !status;
    angleAnima->start();
}

void AnimationButton::paintEvent(QPaintEvent *event)
{
    QImage im = image1.transformed(QTransform().rotate(angle));
    // qDebug()<<"paint";
    QPainter painter(this);
    painter.drawImage(this->rect(), im);
    // pm.toImage().transformed(QTransform())
}
