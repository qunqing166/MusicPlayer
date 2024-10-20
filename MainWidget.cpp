#include "MainWidget.h"
#include <QStackedLayout>
#include "PlayListContentView.h"
#include <QScrollArea>
#include <QStackedWidget>
#include "UI/SidePlayListBar.h"
#include "Service/PlayListItemService.h"

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
    // stackedLayout->setCurrentWidget(indexWidget);
    stackedLayout->setCurrentIndex(1);
    //为了使SideBar可以出现在最表面
    sideBar->setParent(nullptr);
    sideBar->setParent(this);
}

void MainWidget::ToPlayList()
{
    // stackedLayout->setCurrentWidget(contentView);
    stackedLayout->setCurrentIndex(0);
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
    connect(indexWidget->getPlayList(), &PlayListView::UpdatePlayingList,
            sideBar->getSidePlayList(), &SidePlayList::PlayNewList);
    connect(sideBar->getSidePlayList(), &SidePlayList::PlayMusic,
            contentView->getPlayListView(), &PlayListView::OnPlayMusic);
    connect(sideBar->getSidePlayList(), &SidePlayList::PlayMusic,
            indexWidget, &IndexWidget::SetCurrentMusicInfo);
    connect(sideBar->getSidePlayList(), &SidePlayList::CurrentPlayListChanged, indexWidget, &IndexWidget::OnCurrentPlayListChanged);
    connect(contentView, &PlayListContentView::PlayListDataChanged, indexWidget, &IndexWidget::SetPlayList);
    connect(sideBar->getSidePlayList(), &SidePlayList::PlayMusic, this, [&](const MusicDto &music){
        PlayListItemService service("_Record");
        PlayListItemDto item;
        if(service.IsExist(QString("MusicId = %1").arg(music.Id())))
        {
            auto aa = service.GetOneByParameter(QString("MusicId = %1").arg(music.Id()));
            service.Update(aa);
        }
        else
        {
            item.setMusicId(music.Id());
            service.Add(item);
        }
        // sideBar->getSidePlayList()->UpdateList(sideBar->getSidePlayList()->PlayingListName());
        // sideBar->ResetButton();
    });
}

MainWidget::MainWidget(int index, QWidget *parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("main_widget");

    indexInit = index;

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

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(indexWidget);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setObjectName("MainWidget_Scrollarea");
    // scrollArea->setAttribute(Qt::WA_StyledBackground);
    scrollArea->setWidgetResizable(true);
    stackedLayout->addWidget(scrollArea);

    // stackedLayout->addWidget(indexWidget);
    stackedLayout->setCurrentWidget(scrollArea);
}

