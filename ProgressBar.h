#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include <QPropertyAnimation>

class ProgressBar:public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int Value READ Value WRITE setValue NOTIFY ValueChanged FINAL)
    Q_PROPERTY(int SliderRadius READ SliderRadius WRITE setSliderRadius NOTIFY SliderRadiusChanged FINAL)

    int range = 100;

    int sliderRadius = 0;

    const int sliderRadiusMax = 5;

    int value = 50;

    bool isDragged = false;

    QPropertyAnimation *animaSliderRadius = nullptr;

    QPropertyAnimation *animaValue = nullptr;

public:
    ProgressBar(QWidget *parent = nullptr);

    int SliderRadius() const;
    void setSliderRadius(int value);

    int Value() const;
    void setValue(int value);

    bool IsDragged() const;
    void setIsDragged(bool value);

    int Range() const;
    void setRange(int value);

protected:

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    // virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void enterEvent(QEnterEvent *event) override;

private:

    void ObjectInit();

signals:
    void ValueChanged(int value);
    void SliderMoved(int value);
    void SliderRadiusChanged();
};

#endif // PROGRESSBAR_H
