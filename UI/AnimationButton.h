#ifndef ANIMATIONBUTTON_H
#define ANIMATIONBUTTON_H

#include <QWidget>
#include <QPixmap>
#include <QPropertyAnimation>

class AnimationButton:public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int Angle READ Angle WRITE setAngle NOTIFY AngleChanged FINAL)

    QImage image1;
    QImage image2;

    QPropertyAnimation *angleAnima;

    int angle = 180;
    bool status = false;

public:
    AnimationButton(QWidget *parent = nullptr);
    void SetIcon(QImage image1, QImage image2);

private:
    void setAngle(int value){this->angle = value;}
    int Angle(){return this->angle;}

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

signals:
    void AngleChanged();
};

#endif // ANIMATIONBUTTON_H
