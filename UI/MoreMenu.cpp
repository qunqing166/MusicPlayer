#include "MoreMenu.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QMenuBar>
#include <QAction>

MoreMenu::MoreMenu(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("more_menu");
    this->setFixedSize(150, 250);

    ObjectInit();
    WidgetInit();

    // connect(pbAddToList, &ToolButton::Hover, this, [&](){
    //     auto menu = CreateSelectList();
    //     menu->show();
    //     menu->move(QCursor::pos());
    // });
}

void MoreMenu::ObjectInit()
{

    btnPlay = new QPushButton("   播放", this);
    btnPlay->setObjectName("more_menu_button");
    btnPlay->setFixedHeight(40);
    btnPlay->setIcon(QIcon(":/scr/icon/stopping.png"));

    btnPlayNext = new QPushButton("   下一首播放", this);
    btnPlayNext->setFixedHeight(40);
    btnPlayNext->setObjectName("more_menu_button");
    btnPlayNext->setIcon(QIcon(":/scr/icon/next.png"));

    // pbAddToList = new QPushButton("   添加到", this);
    btnAddToList = new ToolButton(this);
    btnAddToList->SetText("   添加到");
    btnAddToList->setObjectName("more_menu_button");
    btnAddToList->setFixedHeight(40);
    btnAddToList->SetIcon(QIcon(":/scr/icon/add.png"));

    btnRemoveFromList = new QPushButton("   从列表移除", this);
    btnRemoveFromList->setObjectName("more_menu_button");
    btnRemoveFromList->setFixedHeight(40);
    btnRemoveFromList->setIcon(QIcon(":/scr/icon/remove.png"));
}

void MoreMenu::WidgetInit()
{
    int margin = 0;

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);

    this->setContentsMargins(margin, margin, margin, margin);

    vLayout->addWidget(btnPlay);
    vLayout->addWidget(btnPlayNext);

    vLayout->addWidget(btnAddToList);
    vLayout->addWidget(btnRemoveFromList);
}

QMenu *MoreMenu::CreateSelectList() const
{
    QMenu *menu = new QMenu();
    menu->addAction("nmsl");
    menu->addAction("nmsl");
    return menu;
}
