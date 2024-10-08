#include "CentralWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SelectBar.h"
#include "PlayerBar.h"
#include "MainWidget.h"

CentralWidget::CentralWidget(QWidget *parent):QWidget(parent)
{
    ObjectInit();
    WidgetInit();

    connect(titleBar, &TitleBar::PbMinClicked, this, [&](){emit Minimize();});
    connect(titleBar, &TitleBar::PbMaxClicked, this, [&](){emit Maximize();});
}

bool CentralWidget::IsInTitleBar(QPoint pos)
{
    return titleBar->geometry().contains(pos);
}

void CentralWidget::ObjectInit()
{
    titleBar = new TitleBar(this);
    selectBar = new SelectBar(this);
    playerBar = new PlayerBar(this);
}

void CentralWidget::WidgetInit()
{
    MainWidget *mainWidget = new MainWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout(this);

    // titleBar->setObjectName("title_bar");
    this->setLayout(vLayout);
    // this->layout()->addItem(vLayout)
    // this->layout().ad
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setSpacing(0);
    vLayout->addWidget(titleBar, 10);
    vLayout->addLayout(hLayout, 80);
    vLayout->addWidget(playerBar, 12);
    hLayout->setSpacing(0);
    hLayout->setAlignment(Qt::AlignLeft);
    hLayout->addWidget(selectBar, 20);
    hLayout->addWidget(mainWidget, 80);
}
