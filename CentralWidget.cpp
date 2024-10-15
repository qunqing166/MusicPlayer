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
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("central_widget");

    ObjectInit();
    WidgetInit();

    //标题栏最小化按钮
    connect(titleBar, &TitleBar::PbMinClicked, this, [&](){emit Minimize();});
    //标题栏最大化按钮
    connect(titleBar, &TitleBar::PbMaxClicked, this, [&](){emit Maximize();});
    //打开某个歌单, 显示歌单内容
    connect(selectBar, &SelectBar::OpenPlayList, this, [&](const PlayListDto &info){
        this->mainWidget->ToPlayList();
        mainWidget->getContentView()->ShowPlayList(info);
    });
    //打开首页
    connect(selectBar, &SelectBar::PageToIndex, this, [&](){mainWidget->ToIndex();});
    //打开侧边栏
    connect(playerBar, &PlayerBar::OpenSideBar, this, [&](){
        if(!mainWidget->getSideBar()->GetOpenStatus())
            this->mainWidget->getSideBar()->Open(mainWidget->geometry());
    });
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
