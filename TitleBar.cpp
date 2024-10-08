#include "TitleBar.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>

TitleBar::TitleBar(QWidget* parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("title_bar");
    pbMax = new QPushButton("o", this);
    pbMin = new QPushButton("-", this);
    pbQuit = new QPushButton("X", this);
    labelEmpty = new QLabel(this);
    labelTitle = new QLabel("MusicPlayer", this);

    WidgetInit();

    connect(pbQuit, &QPushButton::clicked, this, [&](){QApplication::quit();});
    connect(pbMax, &QPushButton::clicked, this, [&](){emit PbMaxClicked();});
    connect(pbMin, &QPushButton::clicked, this, [&](){emit PbMinClicked();});
}

void TitleBar::WidgetInit()
{
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    hLayout->addWidget(labelTitle);
    hLayout->addWidget(labelEmpty);
    hLayout->addWidget(pbMin, Qt::AlignRight);
    hLayout->addWidget(pbMax, Qt::AlignRight);
    hLayout->addWidget(pbQuit, Qt::AlignRight);
    this->setLayout(hLayout);

    int pbSize = 30;
    pbMax->setFixedSize(pbSize, pbSize);
    pbMin->setFixedSize(pbSize, pbSize);
    pbQuit->setFixedSize(pbSize, pbSize);

    QFont font;
    font.setPixelSize(30);
    font.setFamily("Brush Script MT");
    labelTitle->setFont(font);
    labelTitle->setObjectName("title_label");
    //labelTitle->setMargin(20)
}

// void TitleBar::mouseMoveEvent(QMouseEvent *event)
// {
//     if(isDragged)
//     {
//         QPoint dPos = event->pos() - lastPos;
//         emit LocationChanged(dPos);
//         lastPos = event->pos();
//     }
// }

// void TitleBar::mousePressEvent(QMouseEvent *event)
// {
//     event->ignore();
//     isDragged = true;
//     lastPos = event->pos();
// }

// void TitleBar::mouseReleaseEvent(QMouseEvent *event)
// {
//     isDragged = false;
// }
