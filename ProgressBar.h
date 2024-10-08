#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QSlider>

class ProgressBar:public QSlider
{
public:
    ProgressBar(QWidget *parent = nullptr);
};

#endif // PROGRESSBAR_H
