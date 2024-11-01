#include "SelectBar.h"
#include "Dtos/UserDto.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>

SelectBar::SelectBar(QWidget* parent) :QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("SelectBar");

    ObjectInit();
    WidgetInit();

    connect(btnToIndex, &QPushButton::clicked, this, &SelectBar::OnPbIndexClicked);
    connect(playList, &PlayList::OpenPlayList, this, &SelectBar::OpenPlayList);
}

void SelectBar::WidgetInit()
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setContentsMargins(10,10,10,10);
    this->setLayout(vLayout);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);
    hLayout1->setContentsMargins(10,0,10,0);
    hLayout1->setSpacing(3);
    hLayout1->addWidget(labelUserHeadImage);
    hLayout1->addWidget(labelUserName);
    hLayout1->addWidget(pbUserInfo, Qt::AlignRight);

    // QFrame *frame1 = new QFrame(this);
    // frame1->setStyleSheet("background-color:rgb(205, 207, 208);");
    // frame1->setFixedHeight(1);
    // vLayout->addWidget(frame1);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    vLayout->addLayout(hLayout);
    hLayout->addWidget(btnToIndex);

    // QFrame *frame2 = new QFrame(this);
    // frame2->setStyleSheet("background-color:rgb(205, 207, 208);");
    // frame2->setFixedHeight(1);
    // vLayout->addWidget(frame2);


    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setObjectName("SelectBar_ScrollArea");
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

    // PlayList *sl = new PlayList("收藏", this);

    // sl->setObjectName("song_sheet_list");

    QFrame *frame1 = new QFrame(this);
    frame1->setStyleSheet("background-color:rgb(205, 207, 208);");
    frame1->setFixedHeight(1);
    vLayout3->addWidget(frame1);

    vLayout3->addWidget(playList);

    QFrame *frame2 = new QFrame(this);
    frame2->setStyleSheet("background-color:rgb(205, 207, 208);");
    frame2->setFixedHeight(1);
    vLayout3->addWidget(frame2);
    // vLayout3->addWidget(sl);
    vLayout3->addWidget(new QWidget(this), Qt::AlignTop);



    vLayout3->setAlignment(Qt::AlignTop);
    vLayout3->setContentsMargins(20,10,20,10);
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
    pbUserInfo->setIcon(QIcon(":/scr/icon/right.png"));

    playList = new PlayList("创建的歌单", this);
    playList->setObjectName("song_sheet_list");
    btnToIndex = new QPushButton("首页", this);
    btnToIndex->setObjectName("button_index");
    btnToIndex->setFixedSize(150, 30);
}

void SelectBar::OnPbIndexClicked()
{
    btnToIndex->setCheckable(true);
    btnToIndex->setChecked(true);

    emit PageToIndex();
}

void SelectBar::OnOpenPlayList(const PlayListDto &info)
{
    btnToIndex->setChecked(false);
    // btnToIndex->setCheckable(true);


    if(isInPageIndex)
        emit OpenPlayList(info);
    isInPageIndex = false;
}

