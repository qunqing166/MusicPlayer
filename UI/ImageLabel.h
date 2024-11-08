#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

enum HoverStyle
{
    none,
    HoverStyle_Open,
    HoverStyle_Play
};

class ImageLabel:public QWidget
{
    Q_OBJECT

    //
    bool isContentOpen = false;
    bool isHoverable = false;
    bool isClickable = false;
    bool isHover = false;
    bool isAddBorder = true;
    //图片圆角半径
    int radius = 10;
    //hover状态的样式
    HoverStyle hoverStyle = none;
    //图片路径
    QString imagePath;

public:
    //初始化, 传入图片路径
    ImageLabel(QWidget *parent = nullptr, const QString &imagePath = ":/scr/icon/cover_empty.png");

    //属性设置
    void SetPixmap(const QString &path);
    void SetHoverable(bool is);
    void SetClickable(bool is);
    void SetRadius(int radius);
    void SetHoverStyle(HoverStyle style);

    //获取圆角的图片
    static QPixmap GetRadiusPixmap(const QPixmap &pixmap, int radius);

private:

    //绘制hover时的图片
    QPixmap GetHoverPixmap();

    //获取圆角蒙板
    static QBitmap GetRadiusMask(const QSize &size, int radius);

protected:
    //事件重写
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

signals:
    void Clicked();
};

#endif // IMAGELABEL_H
