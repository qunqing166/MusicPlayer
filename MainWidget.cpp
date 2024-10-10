#include "MainWidget.h"
#include <QStackedLayout>
#include "PlayListContentView.h"
// #include

MainWidget::MainWidget(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("main_widget");

    ObjectInit();
    WidgetInit();
}

void MainWidget::ObjectInit()
{

}

void MainWidget::WidgetInit()
{
    QStackedLayout* stackedLayout = new QStackedLayout(this);
    this->setLayout(stackedLayout);



    PlayListContentView *contentView = new PlayListContentView(this);
    stackedLayout->addWidget(contentView);
}
