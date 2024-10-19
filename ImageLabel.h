#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

enum HoverStyle
{
    none,
    HoverStyle_Open,
    HoverStyle_Play
};

class ImageLabel:public QLabel
{
    Q_OBJECT

    QPixmap pixmapOriginal;
    QPixmap pixmap;
    QPixmap pixmapHover;

    bool isContentOpen = false;
    bool isHoverable = false;
    bool isClickable = false;

    int radius = 10;

    HoverStyle hoverStyle = none;

public:
    ImageLabel(QWidget *parent = nullptr);
    void SetPixmap(QPixmap pixmap);
    void SetHoverable(bool is);
    void SetClickable(bool is);
    void SetRadius(int radius);
    void SetHoverStyle(HoverStyle style);

private:
    QPixmap DrawHoverPixmap();
    void DrawShowPixmap();

    QPixmap DrawHoverStyleOpen();
    QPixmap DrawHoverStylePlay();

protected:
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
signals:
    void Clicked();
};

#endif // IMAGELABEL_H
