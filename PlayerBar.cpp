#include "PlayerBar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLayout>
#include <QSlider>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QPixmap>
#include <QTime>

PlayerBar::PlayerBar(QWidget *parent) :QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("player_bar");
    this->setFixedHeight(70);
    ObjectInit();
    WidgetInit();

    // connect(pbStop, &QPushButton::clicked, this, &PlayerBar::OnPbStopClicked);
    connect(pbToNext, &QPushButton::clicked, this, [&](){emit SwitchMusic(true);});
    connect(pbToLast, &QPushButton::clicked, this, [&](){emit SwitchMusic(false);});
}

PlayerBar::PlayerBar(const MusicDto &music, QWidget *parent) :QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("player_bar");
    this->setFixedHeight(70);

    this->musicInfo = music;

    ObjectInit();
    WidgetInit();
    SetMusicInfo(music);
    // connect(pbStop, &QPushButton::clicked, this, &PlayerBar::OnPbStopClicked);
    connect(pbToNext, &QPushButton::clicked, this, [&](){emit SwitchMusic(true);});
    connect(pbToLast, &QPushButton::clicked, this, [&](){emit SwitchMusic(false);});

}

void PlayerBar::SetMusicInfo(const MusicDto &musicInfo, bool isOpen)
{
    //更新显示信息
    this->musicInfo = musicInfo;//musicInfo;
    this->imageLabel->SetPixmap(musicInfo.CoverImagePath());
    this->labelSingers->setText(musicInfo.Singers());
    this->labelMusicName->setText(musicInfo.MusicName());
    this->labelTotleTime->setText(musicInfo.Duration());
    QTime time = QTime::fromString(musicInfo.Duration(), "mm:ss");
    qDebug()<<time;
    this->slider->setRange(0, time.minute() * 60 + time.second());
    qDebug()<<slider->maximum();
    this->labelNowTime->setText("00:00");
    //改变即播放, 更新播放状态
    this->SetPlayStatus(isOpen);
}

void PlayerBar::ObjectInit()
{
    imageLabel = new ImageLabel(this);
    imageLabel->SetClickable(true);
    imageLabel->SetHoverable(true);
    imageLabel->setObjectName("image");
    imageLabel->setFixedSize(60, 60);
    imageLabel->SetPixmap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\jntm.jpg"));

    int buttonSize = 30;
    pbStop = new QPushButton(this);
    pbStop->setIcon(QIcon(":/scr/icon/stopping.png"));
    pbStop->setObjectName("player_bar_button");
    pbStop->setFixedSize(buttonSize, buttonSize);
    connect(pbStop, &QPushButton::clicked, this, &PlayerBar::OnPbStopClicked);

    pbToLast = new QPushButton(this);
    pbToLast->setObjectName("player_bar_button");
    pbToLast->setFixedSize(buttonSize, buttonSize);
    pbToLast->setIcon(QIcon(":/scr/icon/to_last.png"));

    pbToNext = new QPushButton(this);
    pbToNext->setObjectName("player_bar_button");
    pbToNext->setFixedSize(buttonSize, buttonSize);
    pbToNext->setIcon(QIcon(":/scr/icon/to_next.png"));

    buttonSize = 40;
    int iconSize = 25;
    pbPlaySpeed = new QPushButton("1X", this);
    pbPlaySpeed->setObjectName("player_bar_button");
    pbPlaySpeed->setFixedSize(buttonSize, buttonSize);
    connect(pbPlaySpeed, &QPushButton::clicked, this, &PlayerBar::OnPbPlaySpeedClicked);

    pbPlayMode = new QPushButton(this);
    pbPlayMode->setObjectName("player_bar_button");
    pbPlayMode->setFixedSize(buttonSize, buttonSize);
    pbPlayMode->setIcon(QIcon(":/scr/icon/list_loop.png"));
    pbPlayMode->setIconSize(QSize(iconSize, iconSize));
    connect(pbPlayMode, &QPushButton::clicked, this, &PlayerBar::OnPbPlayModeClicked);

    pbVolume = new QPushButton(this);
    pbVolume->setObjectName("player_bar_button");
    pbVolume->setFixedSize(buttonSize, buttonSize);
    pbVolume->setIcon(QIcon(":/scr/icon/volume.png"));
    connect(pbVolume, &QPushButton::clicked, this, &PlayerBar::OnPbVolumeClicked);
    // pbVolume->setIconSize(QSize(iconSize, iconSize));
    pbList = new QPushButton(this);
    pbList->setObjectName("player_bar_button");
    pbList->setFixedSize(buttonSize, buttonSize);
    pbList->setIcon(QIcon(":/scr/icon/list.png"));
    connect(pbList, &QPushButton::clicked, this, &PlayerBar::OnPbListClicked);

    labelMusicName = new QLabel("鸡你太美", this);
    labelMusicName->setObjectName("PlayerBar_Label_MusicName");
    labelMusicName->setMaximumWidth(200);

    labelSingers = new QLabel("坤哥", this);
    labelSingers->setObjectName("PlayerBar_Label_Singers");
    // QFont font;
    // font.setFamily("黑体");
    // font.setPointSize(18);
    // labelMusicName->setFont(font);

    labelTotleTime = new QLabel("00:00", this);
    labelNowTime = new QLabel("00:00", this);
}

void PlayerBar::WidgetInit()
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    this->setLayout(hLayout);
    hLayout->setSpacing(0);

    QVBoxLayout *vLayout1 = new QVBoxLayout(this);
    vLayout1->addWidget(labelMusicName);
    vLayout1->addWidget(labelSingers);
    vLayout1->setSpacing(0);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);

    hLayout1->addWidget(imageLabel);
    hLayout1->addLayout(vLayout1);
    // hLayout1->addWidget(new QLabel(this));
    hLayout1->setSpacing(10);

    QVBoxLayout *vLayout2 = new QVBoxLayout(this);
    QHBoxLayout *hLayout2_1 = new QHBoxLayout(this);

    QLabel *label1 = new QLabel(this);
    QLabel *label2 = new QLabel(this);

    hLayout2_1->addWidget(label1);
    hLayout2_1->addWidget(pbToLast);
    hLayout2_1->addWidget(pbStop);
    hLayout2_1->addWidget(pbToNext);
    hLayout2_1->addWidget(label2);
    vLayout2->addLayout(hLayout2_1);

    QHBoxLayout *hLayout2_2 = new QHBoxLayout(this);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setFixedHeight(20);
    slider->setRange(0, 100);
    vLayout2->addLayout(hLayout2_2);
    hLayout2_2->addWidget(labelNowTime);
    hLayout2_2->addWidget(slider, Qt::AlignBottom);
    hLayout2_2->addWidget(labelTotleTime);

    QHBoxLayout *hLayout3 = new QHBoxLayout(this);
    hLayout3->addWidget(new QLabel(this));

    hLayout3->addWidget(pbPlaySpeed);
    hLayout3->addWidget(pbPlayMode);
    hLayout3->addWidget(pbVolume);
    QFrame *frame = new QFrame(this);
    QSlider *slider1 = new QSlider(Qt::Horizontal, this);
    // slider1->setMinimumWidth(20);
    slider1->setFixedWidth(50);
    hLayout3->addWidget(slider1);
    hLayout3->addWidget(frame);
    hLayout3->setSpacing(5);
    frame->setFixedWidth(1);
    frame->setStyleSheet("QFrame{background-color:#666666;}");
    hLayout3->addWidget(pbList);

    //封面, 歌名
    hLayout->addLayout(hLayout1, 20);
    //进度条
    hLayout->addLayout(vLayout2, 30);
    //控制btn
    hLayout->addLayout(hLayout3, 20);
    // QLabel *label = new QLabel(this);
    // hLayout->addLayout(vLayout1, 1);
    // hLayout->addWidget(slider, 5);
    // hLayout->setAlignment(Qt::AlignLeft);
    // QPushButton *pb = new QPushButton(this);
    // hLayout->addWidget(pb);
}

void PlayerBar::SetSongCover(QPixmap pixmap)
{
    QSize size(60, 60);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 10, 10);

    pixmap = pixmap.scaled(size);
    pixmap.setMask(mask);
    imageLabel->setPixmap(pixmap);
}

void PlayerBar::SetPlayStatus(bool is)
{
    this->isPlaying = is;
    if(!isPlaying)
    {
        pbStop->setIcon(QIcon(":/scr/icon/stopping.png"));
    }
    else
    {
        pbStop->setIcon(QIcon(":/scr/icon/playing.png"));
    }
}

void PlayerBar::OnDurationChanged(qint64 ms)
{
    this->slider->setValue(ms / 1000);
    labelNowTime->setText(QString::asprintf("%02lld:%02lld", (ms / (1000 * 60)) % 60, (ms / 1000) % 60));
    // qDebug()<<sec;
    // qDebug()<<time.toString("mm:ss");
    // qDebug()<<time;
}

MusicDto PlayerBar::CurrentMusic() const
{
    return this->musicInfo;
}

void PlayerBar::OnPbStopClicked()
{
    isPlaying = !isPlaying;
    SetPlayStatus(isPlaying);
    emit PlayStatusChanged(isPlaying);
}

void PlayerBar::OnPbVolumeClicked()
{
    if(isMute)
    {
        pbVolume->setIcon(QIcon(":/scr/icon/volume.png"));
        emit PlayVolumeChanged(0);
    }
    else
    {
        pbVolume->setIcon(QIcon(":/scr/icon/mute.png"));
        emit PlayVolumeChanged(volume);
    }
    isMute = !isMute;
}

void PlayerBar::OnPbPlaySpeedClicked()
{

}

void PlayerBar::OnPbPlayModeClicked()
{
    if(playMode == ListLoop)
    {
        playMode = OneLoop;
        pbPlayMode->setIcon(QIcon(":/scr/icon/one_loop.png"));
    }
    else if(playMode == OneLoop)
    {
        playMode = ListLoop;
        pbPlayMode->setIcon(QIcon(":/scr/icon/list_loop.png"));
    }
    emit PlayModeChanged(playMode);
}

void PlayerBar::OnPbListClicked()
{
    // emit ChangeSideBarOpenStatus();
    emit OpenSideBar();
}
