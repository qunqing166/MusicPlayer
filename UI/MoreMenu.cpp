#include "MoreMenu.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

inline MoreMenu *MoreMenu::instance = nullptr;

MoreMenu::MoreMenu(QWidget *parent):QWidget(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明化
    this->setFixedSize(150, 250);
    this->setWindowFlags(Qt::Popup);
    // this->setObjectName("MoreMenu");

    ObjectInit();
    WidgetInit();

    connect(btnPlay, &QPushButton::clicked, this, [&](){emit Operate(Play);});
    connect(btnRemoveFromList, &QPushButton::clicked, this, [&](){emit Operate(Remove);});
    connect(btnRemoveFromList, &QPushButton::clicked, this, [&](){emit Operate(Remove);});
    connect(btnPlayNext, &QPushButton::clicked, this, [&](){emit Operate(AddToNext);});
}

MoreMenu::~MoreMenu()
{
    this->disconnect();
}

MoreMenu *MoreMenu::Instance()
{
    if(instance == nullptr)
    {
        instance = new MoreMenu();
    }
    return instance;
}

void MoreMenu::ObjectInit()
{

    btnPlay = new QPushButton("         播放    ", this);
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

    // clickedFilter = new ClickedEventFilter(this);
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

    // QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    // shadowEffect->setBlurRadius(15);
    // shadowEffect->setXOffset(-5);
    // shadowEffect->setYOffset(-5);
    // shadowEffect->setColor(QColor(200, 200, 200));
    // this->setGraphicsEffect(shadowEffect);
}

QMenu *MoreMenu::CreateSelectList() const
{
    QMenu *menu = new QMenu();
    menu->addAction("nmsl");
    menu->addAction("nmsl");
    return menu;
}

void MoreMenu::leaveEvent(QEvent *event)
{
    // this->deleteLater();
}

void MoreMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(239, 242, 247));
    painter.setBrush(Qt::white);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRoundedRect(this->rect(), 15, 15);
}
