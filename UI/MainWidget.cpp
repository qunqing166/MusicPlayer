#include "MainWidget.h"
#include <QStackedLayout>
#include "PlayListContentView.h"
#include <QScrollArea>
#include <QStackedWidget>
#include "SidePlayListBar.h"
// #include "Service/PlayListItemService.h"

PlayListContentView *MainWidget::getContentView() const
{
    return contentView;
}

SidePlayListBar *MainWidget::getSideBar() const
{
    return sideBar;
}

IndexWidget *MainWidget::getIndexWidget() const
{
    return indexWidget;
}

void MainWidget::ToIndex()
{
    stackedLayout->setCurrentIndex(1);
    //为了使SideBar可以出现在最表面
    sideBar->setParent(nullptr);
    sideBar->setParent(this);
}

void MainWidget::ToPlayList()
{
    stackedLayout->setCurrentIndex(0);
    //为了使SideBar可以出现在最表面
    sideBar->setParent(nullptr);
    sideBar->setParent(this);
}

MainWidget::MainWidget(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("MainWidget");

    ObjectInit();
    WidgetInit();

    connect(sideBar->getSidePlayList(), &SidePlayList::CurrentPlayListChanged,
            indexWidget, &IndexWidget::OnCurrentPlayListChanged);
    connect(contentView, &PlayListContentView::PlayListDataChanged,
            indexWidget, &IndexWidget::SetPlayList);
}

MainWidget::MainWidget(int index, QWidget *parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("main_widget");

    indexInit = index;

    ObjectInit();
    WidgetInit();
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

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(indexWidget);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setObjectName("MainWidget_Scrollarea");
    scrollArea->setWidgetResizable(true);
    stackedLayout->addWidget(scrollArea);
    stackedLayout->setCurrentWidget(scrollArea);
}

