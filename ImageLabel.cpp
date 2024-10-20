#include "ImageLabel.h"
#include <QPainter>
#include <QPaintEvent>

ImageLabel::ImageLabel(QWidget *parent):QLabel(parent)
{

}

void ImageLabel::SetPixmap(QPixmap pixmap)
{
    this->pixmapOriginal = pixmap;
    DrawShowPixmap();
}

void ImageLabel::SetHoverable(bool is)
{
    isHoverable = is;
    this->hoverStyle = HoverStyle_Open;
}

void ImageLabel::SetClickable(bool is)
{
    isClickable = is;
}

void ImageLabel::SetRadius(int radius)
{
    this->radius = radius;
}

void ImageLabel::SetHoverStyle(HoverStyle style)
{
    this->hoverStyle = style;
    if(style == none)
    {
        isHoverable = false;
    }
    else
    {
        isHoverable = true;
    }
}

QPixmap ImageLabel::DrawHoverPixmap()
{

    if(this->hoverStyle == HoverStyle_Open)
    {
        return DrawHoverStyleOpen();
    }
    else if(this->hoverStyle == HoverStyle_Play)
    {
        return DrawHoverStylePlay();
    }

    return QPixmap();
}

void ImageLabel::DrawShowPixmap()
{
    //配置蒙板
    QSize size = this->size();
    // qDebug()<<size;
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius);

    //缩放图片
    this->pixmap = pixmapOriginal.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->pixmap.setMask(mask);

    QPainter painter2(&pixmap);
    QPen pen;
    pen.setColor(QColor(237, 246, 254, 200));
    pen.setWidth(2);
    painter2.setPen(pen);
    painter2.setRenderHint(QPainter::Antialiasing);
    painter2.setRenderHint(QPainter::SmoothPixmapTransform);
    painter2.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius);

    this->setPixmap(this->pixmap);

    // painter.setPen(QColor(226, 228, 229));
    // painter.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius);

    if(!isHoverable)
        return;

    QPixmap pm = this->pixmap;
    QPainter painter1(&pm);
    painter1.setPen(QColor(0,0,0,0));
    painter1.setRenderHint(QPainter::Antialiasing);
    painter1.setRenderHint(QPainter::SmoothPixmapTransform);
    painter1.setBrush(QColor(0, 0, 0, 150));
    painter1.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius);
    pm.setMask(mask);
    this->pixmapHover = pm;
    // this->setPixmap(this->pixmap);
}

QPixmap ImageLabel::DrawHoverStyleOpen()
{
    QPixmap p;
    if(isContentOpen)
    {
        p = QPixmap(":/scr/icon/down_white.png");
    }
    else
    {
        p = QPixmap(":/scr/icon/up_white.png");
    }

    QPixmap pm = this->pixmapHover;
    QPainter painter(&pm);
    QSize size(this->width() - 10, this->width() * 0.4);
    int dy = 6;
    // QPixmap p(":/scr/icon/up_white.png");
    p = p.scaled(size / 2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.setOpacity(0.9);
    painter.drawPixmap((this->width() - p.width()) / 2, (this->height() - p.height()) / 2 - dy, p);
    painter.setOpacity(0.7);
    painter.drawPixmap((this->width() - p.width()) / 2, (this->height() - p.height()) / 2 + dy, p);

    return pm;
}

QPixmap ImageLabel::DrawHoverStylePlay()
{
    QPixmap p(":/scr/icon/play.png");

    QPixmap pm = this->pixmapHover;
    QPainter painter(&pm);
    // QSize size(this->width() - 10, this->width() * 0.4);
    int dy = 6;
    // QPixmap p(":/scr/icon/up_white.png");
    p = p.scaled(this->size() / 3, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.setOpacity(0.7);
    painter.drawPixmap((this->width() - p.width()) / 2, (this->height() - p.height()) / 2 - dy, p);
    // painter.setOpacity(0.9);
    // painter.drawPixmap((this->width() - p.width()) / 2, (this->height() - p.height()) / 2 - dy, p);
    // painter.setOpacity(0.7);
    // painter.drawPixmap((this->width() - p.width()) / 2, (this->height() - p.height()) / 2 + dy, p);

    return pm;
}

void ImageLabel::mousePressEvent(QMouseEvent *ev)
{
    if(!isClickable)
        return;
    emit Clicked();
    isContentOpen = !isContentOpen;
    // this->repaint();
    this->setPixmap(DrawHoverPixmap());
}

void ImageLabel::enterEvent(QEnterEvent *event)
{
    if(!isHoverable)
        return;
    this->setPixmap(DrawHoverPixmap());
}

void ImageLabel::leaveEvent(QEvent *event)
{
    if(!isHoverable)
        return;
    this->setPixmap(this->pixmap);
}

void ImageLabel::resizeEvent(QResizeEvent *event)
{
    DrawShowPixmap();
}

