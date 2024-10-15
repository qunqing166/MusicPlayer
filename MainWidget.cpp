#include "MainWidget.h"
#include <QStackedLayout>
#include "PlayListContentView.h"
#include <QStackedWidget>
#include "UI/SidePlayListBar.h"

PlayListContentView *MainWidget::getContentView() const
{
    return contentView;
}

SidePlayListBar *MainWidget::getSideBar() const
{
    return sideBar;
}

void MainWidget::ToIndex()
{
    stackedLayout->setCurrentWidget(indexWidget);
    //为了使SideBar可以出现在最表面
    sideBar->setParent(nullptr);
    sideBar->setParent(this);
}

void MainWidget::ToPlayList()
{
    stackedLayout->setCurrentWidget(contentView);
    //为了使SideBar可以出现在最表面
    sideBar->setParent(nullptr);
    sideBar->setParent(this);
}

MainWidget::MainWidget(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("main_widget");

    ObjectInit();
    WidgetInit();

    connect(contentView->getPlayListView(), &PlayListView::UpdatePlayingList,
            sideBar->getSidePlayList(), &SidePlayList::PlayNewList);
    connect(sideBar->getSidePlayList(), &SidePlayList::PlayMusic,
            contentView->getPlayListView(), &PlayListView::OnPlayMusic);
}

void MainWidget::ObjectInit()
{
    stackedLayout = new QStackedLayout(this);
    contentView = new PlayListContentView(this);
    indexWidget = new IndexWidget(this);
    sideBar = new SidePlayListBar(this);
}

void MainWidget::WidgetInit()
{
    this->setLayout(stackedLayout);
    stackedLayout->addWidget(contentView);
    stackedLayout->addWidget(indexWidget);
    stackedLayout->setCurrentWidget(indexWidget);
}
