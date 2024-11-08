#include "PlayerBar.h"
#include "../Service/MusicService.h"
#include "../Service/PlayerController.h"
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
#include <QStyle>

using namespace Model;
using namespace Service;

PlayMode PlayerBar::getPlayMode() const
{
    return playMode;
}

void PlayerBar::setPlayMode(PlayMode value)
{
    if (playMode == value)
        return;
    playMode = value;
    if(playMode == OneLoop)
    {
        pbPlayMode->setIcon(QIcon(":/scr/icon/one_loop.png"));
    }
    else if(playMode == ListLoop)
    {
        pbPlayMode->setIcon(QIcon(":/scr/icon/list_loop.png"));
    }
}

PlayerBar::PlayerBar(QWidget *parent) :QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("PlayerBar");
    this->setFixedHeight(70);
    ObjectInit();
    WidgetInit();

    auto music = PlayerController::Instance()->CurrentMusic();
    this->SetMusicInfo(music, false);
    this->OnPositionChanged(PlayerController::Instance()->Position());
    setPlayMode(PlayerController::Instance()->getPlayMode());

    connect(pbStop, &QPushButton::clicked, this, &PlayerBar::OnPbStopClicked);
    connect(pbToNext, &QPushButton::clicked, this, [&](){PlayerController::Instance()->ToNextMusic();});
    connect(pbToLast, &QPushButton::clicked, this, [&](){PlayerController::Instance()->ToLastMusic();});
    
    connect(PlayerController::Instance(), &PlayerController::CurrentMusicChanged, this, [&](const Music &music){
        this->SetMusicInfo(music);
    });
    connect(PlayerController::Instance()->getMediaPlayer(), &QMediaPlayer::positionChanged, this, &PlayerBar::OnPositionChanged);

    connect(progressBar, &ProgressBar::ValueChanged, [&](int value){
        PlayerController::Instance()->getMediaPlayer()->setPosition(value * 1000);
    });
    connect(progressBar, &ProgressBar::SliderMoved, this, [&](int value){
        labelNowTime->setText(QString::asprintf("%02d:%02d", (value / 60) % 60, value % 60));
    });
    connect(pbPlayMode, &QPushButton::clicked, this, &PlayerBar::OnPbPlayModeClicked);
    connect(pbVolume, &QPushButton::clicked, this, &PlayerBar::OnPbVolumeClicked);
}

void PlayerBar::SetMusicInfo(const Music &musicInfo, bool isOpen)
{
    MusicService service;
    if(!service.IsExist(QString("Id = %1").arg(musicInfo.Id())))
        return;
    //更新显示信息
    this->musicInfo = musicInfo;//musicInfo;
    this->imageLabel->SetPixmap(musicInfo.CoverImagePath());
    this->labelSingers->setText(musicInfo.Singers());
    this->labelMusicName->setText(musicInfo.MusicName());
    this->labelTotleTime->setText(musicInfo.Duration());
    QTime time = QTime::fromString(musicInfo.Duration(), "mm:ss");
    this->progressBar->setRange(time.minute() * 60 + time.second());
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
    imageLabel->setFixedSize(50, 50);
    imageLabel->SetPixmap("C:\\Users\\qunqing\\Desktop\\图片\\jntm.jpg");

    int buttonSize = 30;
    pbStop = new QPushButton(this);
    pbStop->setIcon(QIcon(":/scr/icon/stopping.png"));
    pbStop->setObjectName("player_bar_button");
    pbStop->setFixedSize(buttonSize, buttonSize);
    // connect(pbStop, &QPushButton::clicked, this, &PlayerBar::OnPbStopClicked);

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


    pbVolume = new QPushButton(this);
    pbVolume->setObjectName("player_bar_button");
    pbVolume->setFixedSize(buttonSize, buttonSize);
    pbVolume->setIcon(QIcon(":/scr/icon/volume.png"));

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

    labelTotleTime = new QLabel("00:00", this);
    labelNowTime = new QLabel("00:00", this);

    QPalette pa;
    pa.setColor(QPalette::WindowText, QColor("#808283"));
    labelTotleTime->setPalette(pa);
    labelNowTime->setPalette(pa);

    progressBar = new ProgressBar(this);
}

void PlayerBar::WidgetInit()
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    this->setLayout(hLayout);
    // hLayout->setSpacing(0);
    // hLayout->setContentsMargins(10,10,10,10);

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

    vLayout2->addLayout(hLayout2_2);
    hLayout2_2->setSpacing(10);
    hLayout2_2->addWidget(labelNowTime);
    // hLayout2_2->addWidget(slider, Qt::AlignBottom);
    hLayout2_2->addWidget(progressBar, Qt::AlignBottom);
    hLayout2_2->addWidget(labelTotleTime);

    QHBoxLayout *hLayout3 = new QHBoxLayout(this);
    hLayout3->addWidget(new QLabel(this));

    hLayout3->addWidget(pbPlaySpeed);
    hLayout3->addWidget(pbPlayMode);
    hLayout3->addWidget(pbVolume);
    QFrame *frame = new QFrame(this);

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

void PlayerBar::OnPositionChanged(qint64 ms)
{
    qDebug()<<ms;
    if(progressBar->IsDragged())
        return;
    int s = (ms / 1000) % progressBar->Range();
    progressBar->setValue(s);
    labelNowTime->setText(QString::asprintf("%02d:%02d", (s / 60) % 60, s % 60));
}

Music PlayerBar::CurrentMusic() const
{
    return this->musicInfo;
}

void PlayerBar::OnPbStopClicked()
{
    isPlaying = !isPlaying;
    if(!isPlaying)
    {
        pbStop->setIcon(QIcon(":/scr/icon/stopping.png"));
    }
    else
    {
        pbStop->setIcon(QIcon(":/scr/icon/playing.png"));
    }
    // SetPlayStatus(isPlaying);
    if(isFirstPlay)
    {
        PlayerController::Instance()->getMediaPlayer()->setPosition(progressBar->Value() * 1000);
        isFirstPlay = false;
    }
    PlayerController::Instance()->setPlayStatus(isPlaying);

    // emit PlayStatusChanged(isPlaying);
}

void PlayerBar::OnPbVolumeClicked()
{
    if(isMute)
    {
        pbVolume->setIcon(QIcon(":/scr/icon/volume.png"));
    }
    else
    {
        pbVolume->setIcon(QIcon(":/scr/icon/mute.png"));
        // emit PlayVolumeChanged(volume);
    }
    isMute = !isMute;
    PlayerController::Instance()->SetVolume(isMute);
}

void PlayerBar::OnPbPlaySpeedClicked()
{

}

void PlayerBar::OnPbPlayModeClicked()
{
    if(playMode == ListLoop)
    {
        setPlayMode(OneLoop);
    }
    else if(playMode == OneLoop)
    {
        setPlayMode(ListLoop);
    }
    PlayerController::Instance()->setPlayMode(this->playMode);
}

void PlayerBar::OnPbListClicked()
{
    emit OpenSideBar();
}
