#include "ImageLabel.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDir>
#include <QStandardPaths>

ImageLabel::ImageLabel(QWidget *parent, const QString &imagePath)
{
    this->imagePath = imagePath;
}

// void ImageLabel::SetPixmap(const QPixmap &pixmap)
// {
//     // this->pixmapOriginal = pixmap;
//     // this->pixmap = GetRadiusPixmap(pixmap, radius);
//     // DrawShowPixmap();
//     // this->setPixmap(this->pixmap);
// }

void ImageLabel::SetPixmap(const QString &path)
{
    this->imagePath = path;
    this->update();
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

QPixmap ImageLabel::GetHoverPixmap()
{
    //获取缩放图
    QPixmap pix = QPixmap(imagePath).scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //添加圆角
    pix = GetRadiusPixmap(pix, radius);
    //绘制半透明层
    QPainter painter(&pix);
    painter.setPen(QColor(0,0,0,0));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setBrush(QColor(0, 0, 0, 150));
    painter.drawRoundedRect(0, 0, pix.width(), pix.height(), radius, radius);
    pix.setMask(GetRadiusMask(pix.size(), radius));
    //绘制图标
    QPixmap p;
    int dy = 5;

    if(hoverStyle == HoverStyle_Play)
    {
        p = QPixmap(":/scr/icon/play.png");

        p = p.scaled(this->size() / 3, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.setOpacity(0.7);
        painter.drawPixmap((this->width() - p.width()) / 2, (this->height() - p.height()) / 2 - dy, p);
        // qDebug()<<isHover<<":"<<"play";
    }
    else if(hoverStyle == HoverStyle_Open)
    {
        qDebug()<<"open hover";
        if(isContentOpen)
        {
            p = QPixmap(":/scr/icon/down_white.png");
        }
        else
        {
            p = QPixmap(":/scr/icon/up_white.png");
        }
        p = p.scaled(QSize(pix.width() * 0.8, pix.height() * 0.4) / 2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.setOpacity(0.9);
        painter.drawPixmap((this->width() - p.width()) / 2, (this->height() - p.height()) / 2 - dy, p);
        painter.setOpacity(0.7);
        painter.drawPixmap((this->width() - p.width()) / 2, (this->height() - p.height()) / 2 + dy, p);
    }

    return pix;
}

QPixmap ImageLabel::GetRadiusPixmap(const QPixmap &pixmap, int radius)
{

    auto mask = GetRadiusMask(pixmap.size(), radius);

    auto pix = pixmap;
    pix.setMask(mask);
    return pix;
}

QBitmap ImageLabel::GetRadiusMask(const QSize &size, int radius)
{
    //配置蒙板
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius);
    return mask;
}

void ImageLabel::mousePressEvent(QMouseEvent *ev)
{
    if(!isClickable)
        return;
    emit Clicked();
    isContentOpen = !isContentOpen;
    // this->repaint();
    this->update();
    // this->setPixmap(DrawHoverPixmap());
}

void ImageLabel::enterEvent(QEnterEvent *event)
{
    qDebug()<<"enter";
    if(!isHoverable)
        return;
    isHover = true;
    this->update();
    // this->setPixmap(DrawHoverPixmap());
}

void ImageLabel::leaveEvent(QEvent *event)
{
    if(!isHoverable)
        return;
    isHover = false;
    this->update();
    // this->setPixmap(this->pixmap);
    // this->setPixmap(this->pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

// void ImageLabel::resizeEvent(QResizeEvent *event)
// {
//     // DrawShowPixmap();

// }

void ImageLabel::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QPixmap pix;
    if(!isHover || !isHoverable)
    {
        pix = QPixmap(imagePath).scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, GetRadiusPixmap(pix, radius));
    }
    else
    {
        pix = GetHoverPixmap();
        painter.drawPixmap(0,0, pix);
    }

}

