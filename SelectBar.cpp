#include "SelectBar.h"
#include "Dtos/UserDto.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>

SelectBar::SelectBar(QWidget* parent) :QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("select_bar");

    ObjectInit();
    WidgetInit();

    connect(btnToIndex, &QPushButton::clicked, this, &SelectBar::OnPbIndexClicked);
    connect(playList, &PlayList::OpenPlayList, this, &SelectBar::OpenPlayList);
}

void SelectBar::WidgetInit()
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setContentsMargins(0,10,0,10);
    this->setLayout(vLayout);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);
    hLayout1->setContentsMargins(10,0,0,0);
    hLayout1->setSpacing(3);
    hLayout1->addWidget(labelUserHeadImage);
    hLayout1->addWidget(labelUserName);
    hLayout1->addWidget(pbUserInfo, Qt::AlignRight);

    vLayout->addWidget(btnToIndex);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setObjectName("select_bar_scrollarea");
    // scrollArea->setAttribute(Qt::WA_StyledBackground);
    vLayout->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setContentsMargins(0,0,0,0);

    QVBoxLayout *vLayout3 = new QVBoxLayout(this);
    vLayout3->setAlignment(Qt::AlignTop);
    QWidget *widget = new QWidget(this);
    widget->setStyleSheet("background-color:transparent;");
    widget->setLayout(vLayout3);
    scrollArea->setWidget(widget);
    widget->setObjectName("scroll_widget");

    PlayList *sl = new PlayList("收藏", this);

    sl->setObjectName("song_sheet_list");

    vLayout3->addWidget(playList);
    vLayout3->addWidget(sl);
    vLayout3->addWidget(new QWidget(this), Qt::AlignTop);

    vLayout3->setAlignment(Qt::AlignTop);
    vLayout3->setContentsMargins(0,0,0,0);
}

void SelectBar::ObjectInit()
{
    labelUserHeadImage = new ImageLabel(this, UserDto::MyUserInfo()->HeadImagePath());
    int imageSize = 36;
    labelUserHeadImage->SetRadius(imageSize / 2);
    labelUserHeadImage->setFixedSize(imageSize, imageSize);

    labelUserName = new QLabel(UserDto::MyUserInfo()->UserName(), this);
    labelUserName->setObjectName("select_bar_user_name");
    labelUserName->setFixedHeight(40);

    pbUserInfo = new QPushButton(this);
    pbUserInfo->setFixedSize(40, 40);
    pbUserInfo->setObjectName("select_bar_button");
    pbUserInfo->setIcon(QIcon(":/scr/icon/arrow_right.png"));

    playList = new PlayList("自建", this);
    playList->setObjectName("song_sheet_list");
    btnToIndex = new QPushButton("首页", this);
    btnToIndex->setObjectName("button_index");
    btnToIndex->setFixedHeight(30);
}

void SelectBar::OnPbIndexClicked()
{
    // if(!isInPageIndex)
    emit PageToIndex();
    // isInPageIndex = true;
}

void SelectBar::OnOpenPlayList(const PlayListDto &info)
{
    if(isInPageIndex)
        emit OpenPlayList(info);
    isInPageIndex = false;
}

