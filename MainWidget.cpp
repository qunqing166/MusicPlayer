#include "MainWidget.h"
#include <QStackedLayout>
#include "PlayListContentView.h"
#include <QStackedWidget>

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
    // this->
    // stackedLayout-
    // QStac
    // QWidget *widget = new QWidget(this);
    // stackedLayout->addWidget(widget);
    // stackedLayout->setCurrentWidget(widget);
    // widget->setObjectName("widget_test");
}
