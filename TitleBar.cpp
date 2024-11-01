#include "TitleBar.h"
#include <QHBoxLayout>
#include <QApplication>

TitleBar::TitleBar(QWidget* parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("TitleBar");
    pbMax = new QPushButton(this);
    pbMin = new QPushButton(this);
    pbQuit = new QPushButton(this);
    labelEmpty = new QLabel(this);
    labelTitle = new QLabel("MusicPlayer", this);

    pbMax->setObjectName("title_bar_btn");
    pbMin->setObjectName("title_bar_btn");
    pbQuit->setObjectName("title_bar_btn");

    pbMax->setIcon(QIcon(":/scr/icon/max.png"));
    pbMin->setIcon(QIcon(":/scr/icon/-.png"));
    pbQuit->setIcon(QIcon(":/scr/icon/close.png"));

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
}
