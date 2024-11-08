#include "IndexPlayListItem.h"
#include <QVBoxLayout>
#include "../Dtos/UserDto.h"

using namespace Model;
using namespace Service;

IndexPlayListItem::IndexPlayListItem(const PlayList &playList, QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);

    this->playListInfo = playList;

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);

    QFont font;
    font.setBold(true);
    // font.setFamily("黑体");

    imageLabel = new ImageLabel(this, playListInfo.CoverImagePath());
    imageLabel->SetClickable(true);
    // imageLabel->SetPixmap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\liyue.webp"));
    imageLabel->SetPixmap(playList.CoverImagePath());
    imageLabel->setFixedSize(width, width);
    imageLabel->SetHoverStyle(HoverStyle_Play);
    QLabel *label1 = new QLabel(playList.ListName(), this);
    label1->setFont(font);
    QLabel *label2 = new QLabel(QString("by %1").arg(User::MyUserInfo()->UserName()), this);
    vLayout->addWidget(imageLabel);
    vLayout->addWidget(label1);
    vLayout->addWidget(label2);

    connect(imageLabel, &ImageLabel::Clicked, this, [&](){
        emit OpenPlayList(playListInfo);
    });
}
