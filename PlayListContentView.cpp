#include "PlayListContentView.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "PlayListView.h"

PlayListContentView::PlayListContentView(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("song_sheet_content");
    ObjectInit();
    WidgetInit();
}

void PlayListContentView::ObjectInit()
{
    imageLabel = new ImageLabel(this);
    int imageSize = 100;
    imageLabel->setFixedSize(imageSize, imageSize);
    imageLabel->SetPixmap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\liyue.webp"));
    // imageLabel->setObjectName("sheet_image_label");

    sheetTitleLabel = new QLabel(this);
    sheetTitleLabel->setText("我喜欢");
    sheetTitleLabel->setObjectName("sheet_title_label");

    int userImageSize = 20;
    userImage = new ImageLabel(this);
    userImage->SetPixmap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\yyn.jpg"));
    userImage->setFixedSize(userImageSize, userImageSize);

    userNameLabel = new QLabel(this);
    userNameLabel->setText("qunqing166");
    userNameLabel->setObjectName("sheet_user_name");

    createTimeLabel = new QLabel(this);
    createTimeLabel->setText("创建于11-45-14");
    createTimeLabel->setObjectName("sheet_user_name");

    pbPlay = new QPushButton(this);
    pbPlay->setObjectName("sheet_button_play");
    pbPlay->setText("播放");
    pbPlay->setIcon(QIcon(":/scr/icon/stopping.png"));
    pbPlay->setFixedSize(80, 30);

    pbEdit = new QPushButton(this);
    pbEdit->setObjectName("sheet_button_edit");
    pbEdit->setObjectName("sheet_button_edit");
    pbEdit->setIcon(QIcon(":/scr/icon/edit.png"));
    pbEdit->setFixedSize(30, 30);
}

void PlayListContentView::WidgetInit()
{
    // QScrollArea *
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignTop);
    this->setLayout(vLayout);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);

    hLayout1->addWidget(imageLabel, Qt::AlignLeft);

    QVBoxLayout *vLayout2 = new QVBoxLayout(this);
    hLayout1->addLayout(vLayout2);
    vLayout2->setAlignment(Qt::AlignBottom);
    vLayout2->addWidget(sheetTitleLabel);

    QHBoxLayout *hLayout2_1 = new QHBoxLayout(this);
    hLayout2_1->setAlignment(Qt::AlignLeft);
    hLayout2_1->addWidget(userImage);
    hLayout2_1->addWidget(userNameLabel);
    hLayout2_1->addWidget(createTimeLabel);
    vLayout2->addLayout(hLayout2_1);

    QHBoxLayout *hLayout2_2 = new QHBoxLayout(this);
    hLayout2_2->setAlignment(Qt::AlignLeft);
    hLayout2_2->addWidget(pbPlay);
    hLayout2_2->addWidget(pbEdit);
    vLayout2->addLayout(hLayout2_2);

    QHBoxLayout *hLayout3 = new QHBoxLayout(this);

    QLabel *title = new QLabel("音乐", this);
    title->setFixedHeight(40);
    QLabel *number = new QLabel("10", this);
    // QLabel *labelTitle = new QLabel("标题", this);
    // QLabel *labelSingers = new QLabel("歌手", this);
    // QLabel *labelAlbum = new QLabel("专辑", this);
    // QLabel *labelDuration = new QLabel("时长", this);
    vLayout->addLayout(hLayout3);
    hLayout3->addWidget(title);
    hLayout3->addWidget(number);
    hLayout3->addWidget(new QLabel(this), Qt::AlignLeft);
    vLayout->setAlignment(Qt::AlignLeft);
    // QLabel *label = new QLabel(this);
    // label->setFixedWidth(60);
    // hLayout3->addWidget(label);
    // hLayout3->addWidget(labelTitle, 4);
    // hLayout3->addWidget(labelSingers, 2);
    // hLayout3->addWidget(labelAlbum, 2);
    // hLayout3->addWidget(labelDuration, 2);

    PlayListView *songListView = new PlayListView(this);
    vLayout->addWidget(songListView);

    // vLayout->addWidget(new QWidget(this), Qt::AlignTop);
}
