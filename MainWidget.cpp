#include "MainWidget.h"
#include <QStackedLayout>
#include "PlayListContentView.h"
#include <QStackedWidget>
#include "UI/SidePlayListBar.h"

PlayListContentView *MainWidget::getContentView() const
{
    return contentView;
}

MainWidget::MainWidget(QWidget *parent):QStackedWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("main_widget");

    ObjectInit();
    WidgetInit();
}

void MainWidget::ObjectInit()
{
    contentView = new PlayListContentView(this);
}

void MainWidget::WidgetInit()
{
    // QStackedLayout* stackedLayout = new QStackedLayout(this);
    // this->setLayout(stackedLayout);

    this->addWidget(contentView);
    QWidget *widget = new QWidget(this);
    this->addWidget(widget);

    sideBar = new SidePlayListBar(this);

    // sideBar->show();
}
