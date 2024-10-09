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

PlayerBar::PlayerBar(QWidget *parent) :QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("player_bar");
    this->setFixedHeight(70);
    ObjectInit();
    WidgetInit();

    SetMusicInfo(MusicInfo());

}

void PlayerBar::SetMusicInfo(MusicInfo musicInfo)
{
    this->musicInfo = musicInfo;

    this->imageLabel->SetPixmap(musicInfo.coverImagePath);
    if(!musicInfo.singers.empty())
    {
        QString str = musicInfo.singers.at(0);
        int t = 0;
        foreach (QString name, musicInfo.singers)
        {
            if(t == 0)
            {
                t++;
                continue;
            }
            str = str + ", " + name;
        }
        this->labelSingers->setText(str);
    }
    this->labelMusicName->setText(musicInfo.musicName);
    this->labelTotleTime->setText(musicInfo.duration.toString("mm:ss"));
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

    labelMusicName = new QLabel("鸡你太美", this);
    labelSingers = new QLabel("坤哥", this);
    QFont font;
    font.setFamily("黑体");
    font.setPointSize(18);
    labelMusicName->setFont(font);

    labelTotleTime = new QLabel("00:00", this);
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
    // hLayout->addLayout(vLayout1, Qt::AlignLeft);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    hLayout->addLayout(hLayout1, 20);
    hLayout1->addWidget(imageLabel);
    hLayout1->addLayout(vLayout1);
    hLayout1->addWidget(new QLabel(this));
    hLayout1->setSpacing(10);

    QVBoxLayout *vLayout2 = new QVBoxLayout(this);
    QHBoxLayout *hLayout2_1 = new QHBoxLayout(this);

    QLabel *label1 = new QLabel(this);
    QLabel *label2 = new QLabel(this);
    hLayout->addLayout(vLayout2, 35);
    hLayout2_1->addWidget(label1);
    hLayout2_1->addWidget(pbToLast);
    hLayout2_1->addWidget(pbStop);
    hLayout2_1->addWidget(pbToNext);
    hLayout2_1->addWidget(label2);
    vLayout2->addLayout(hLayout2_1);

    QHBoxLayout *hLayout2_2 = new QHBoxLayout(this);
    QLabel *labelNowTime = new QLabel("00:00", this);
    QSlider *slider = new QSlider(Qt::Horizontal, this);
    slider->setFixedHeight(20);
    slider->setRange(0, 100);
    vLayout2->addLayout(hLayout2_2);
    hLayout2_2->addWidget(labelNowTime);
    hLayout2_2->addWidget(slider, Qt::AlignBottom);
    hLayout2_2->addWidget(labelTotleTime);

    QHBoxLayout *hLayout3 = new QHBoxLayout(this);
    hLayout3->addWidget(new QLabel(this));
    hLayout->addLayout(hLayout3, 20);

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

void PlayerBar::OnPbStopClicked()
{
    if(isPlaying)
    {
        pbStop->setIcon(QIcon(":/scr/icon/stopping.png"));
    }
    else
    {
        pbStop->setIcon(QIcon(":/scr/icon/playing.png"));
    }
    isPlaying = !isPlaying;
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
