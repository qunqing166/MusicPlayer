#include "CentralWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "SelectBar.h"
#include "PlayerBar.h"
#include "MainWidget.h"

// MainWidget *CentralWidget::MainWidget() const
// {
//     return mainWidget;
// }

MainWidget *CentralWidget::getMainWidget() const
{
    return mainWidget;
}

PlayerBar *CentralWidget::getPlayerBar() const
{
    return playerBar;
}

SelectBar *CentralWidget::getSelectBar() const
{
    return selectBar;
}

TitleBar *CentralWidget::getTitleBar() const
{
    return titleBar;
}

CentralWidget::CentralWidget(QWidget *parent):QWidget(parent)
{
    ObjectInit();
    WidgetInit();

    connect(titleBar, &TitleBar::PbMinClicked, this, [&](){emit Minimize();});
    connect(titleBar, &TitleBar::PbMaxClicked, this, [&](){emit Maximize();});
    connect(selectBar->GetPlayList(), &PlayList::OpenPlayList, this->mainWidget->getContentView(), &PlayListContentView::ShowPlayList);
    connect(this->getMainWidget()->getContentView()->getPlayListView(), &PlayListView::PlayMusic, playerBar, &PlayerBar::SetMusicInfo);
    connect(this->getPlayerBar(), &PlayerBar::OpenSideBar,this, [&](){
        // mainWidget->sideBar->ChangeOpenStatus(mainWidget->geometry());
        if(mainWidget->sideBar->GetOpenStatus() == false)
            mainWidget->sideBar->Open(mainWidget->geometry());
    });
    // connect(this->getPlayerBar(), &PlayerBar::C)
    // connect()
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
    mainWidget = new MainWidget(this);
}

void CentralWidget::WidgetInit()
{

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
