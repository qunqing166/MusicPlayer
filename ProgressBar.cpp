#include "ProgressBar.h"

#include <QMouseEvent>
#include <QPainter>

int ProgressBar::SliderRadius() const
{
    return sliderRadius;
}

void ProgressBar::setSliderRadius(int value)
{
    if(sliderRadius == value)
        return;
    sliderRadius = value;
}

int ProgressBar::Value() const
{
    return value;
}

void ProgressBar::setValue(int value)
{
    if(this->value == value || value > range || value < 0)
        return;
    this->value = value;
    this->update();

    emit SliderMoved(value);
}

void ProgressBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setPen(QColor(0,0,0,0));

    int spacing = 6;
    int radius = (this->height() - spacing * 2) / 2;

    QColor colorDisCovered(225, 231, 240);
    QColor colorCovered(38, 161, 255);

    painter.setBrush(colorDisCovered);
    QRect rectDiscovered(sliderRadiusMax, spacing, this->width() - sliderRadiusMax * 2, this->height() - spacing * 2);
    painter.drawRoundedRect(rectDiscovered, radius, radius);

    painter.setBrush(colorCovered);
    QRect rectCovered(sliderRadiusMax, spacing, value * (this->width() - sliderRadiusMax * 2) / range, this->height() - spacing * 2);
    painter.drawRoundedRect(rectCovered, radius, radius);

    int px = sliderRadiusMax + value * (this->width() - sliderRadiusMax * 2) / range;
    painter.drawEllipse(QPoint(px, this->height() / 2), sliderRadius, sliderRadius);

}

void ProgressBar::mouseMoveEvent(QMouseEvent *event)
{
    setValue((event->pos().x() - sliderRadiusMax) * range / (this->width() - sliderRadiusMax * 2));
    this->update();
}

void ProgressBar::mouseReleaseEvent(QMouseEvent *event)
{
    isDragged = false;
    if(value < 0)
    {
        animaValue->setStartValue(this->value);
        animaValue->setEndValue(0);
        animaValue->startTimer(10);
        animaValue->start();
        emit ValueChanged(0);
    }
    else
    {
        emit ValueChanged(value);
    }
}

void ProgressBar::mousePressEvent(QMouseEvent *event)
{
    isDragged = true;
    setValue((event->pos().x() - sliderRadiusMax) * range / (this->width() - sliderRadiusMax * 2));
    this->update();
}

void ProgressBar::leaveEvent(QEvent *event)
{
    // isMouseOn = false;
    animaSliderRadius->setStartValue(sliderRadius);
    animaSliderRadius->setEndValue(0);
    animaSliderRadius->startTimer(10);
    animaSliderRadius->start();
}

void ProgressBar::enterEvent(QEnterEvent *event)
{
    // isMouseOn = true;
    animaSliderRadius->setStartValue(sliderRadius);
    animaSliderRadius->setEndValue(sliderRadiusMax);
    animaSliderRadius->startTimer(10);
    animaSliderRadius->start();
}

bool ProgressBar::IsDragged() const
{
    return isDragged;
}

void ProgressBar::setIsDragged(bool value)
{
    isDragged = value;
}

int ProgressBar::Range() const
{
    return range;
}

void ProgressBar::setRange(int value)
{
    range = value;
}

ProgressBar::ProgressBar(QWidget *parent):QWidget(parent)
{
    this->setMaximumHeight(16);

    ObjectInit();

    connect(animaSliderRadius, &QPropertyAnimation::valueChanged, this, [&](){
        this->update();
    });
    connect(animaValue, &QPropertyAnimation::valueChanged, this, [&](){
        this->update();
    });
    connect(animaValue, &QPropertyAnimation::finished, this, [&](){
        animaSliderRadius->start();
    });
}

void ProgressBar::ObjectInit()
{
    animaSliderRadius = new QPropertyAnimation(this, "SliderRadius");

    animaValue = new QPropertyAnimation(this, "Value");
}
