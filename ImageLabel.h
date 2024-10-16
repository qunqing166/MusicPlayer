#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

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

public:
    ImageLabel(QWidget *parent = nullptr);
    void SetPixmap(QPixmap pixmap);
    void SetHoverable(bool is);
    void SetClickable(bool is);
    void SetRadius(int radius);

private:
    QPixmap DrawHoverPixmap();
    void DrawShowPixmap();

protected:
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
signals:
    void Clicked();
};

#endif // IMAGELABEL_H
