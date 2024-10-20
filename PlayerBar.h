#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QWidget>
#include <QLabel>
#include "Dtos/MusicDto.h"
#include "ImageLabel.h"
#include <QPushButton>
// #include "DataInfo/MusicInfo.h"
#include <QSlider>


enum PlayMode
{
    OneLoop,
    ListLoop
};

enum PlaySpeed
{
    zero_point_five_x,
    one_x,
    one_point_five_x,
    two_x,
};

//播放控制栏
class PlayerBar:public QWidget
{
    Q_OBJECT

    MusicDto musicInfo;

    bool isPlaying = false;
    bool isMute = false;
    int volume = 50;
    PlayMode playMode = ListLoop;
    PlaySpeed playSpeed = one_x;
    // QLabel *imageLabel;
    ImageLabel *imageLabel;
    QPushButton *pbStop;
    QPushButton *pbToLast;
    QPushButton *pbToNext;
    QPushButton *pbPlaySpeed;
    QPushButton *pbPlayMode;
    QPushButton *pbVolume;
    QPushButton *pbList;

    QLabel *labelMusicName;
    QLabel *labelSingers;
    QLabel *labelTotleTime;
    QLabel *labelNowTime;

    QSlider *slider;

public:
    PlayerBar(QWidget *parent = nullptr);
    PlayerBar(const MusicDto &music, QWidget *parent = nullptr);
    void SetMusicInfo(const MusicDto &musicInfo, bool isOpen = true);
    void SetPlayStatus(bool is);

    void OnDurationChanged(qint64 sec);

    MusicDto CurrentMusic() const;

private:
    void ObjectInit();
    void WidgetInit();
    void SetSongCover(QPixmap pixmap);

private slots:
    void OnPbStopClicked();
    void OnPbVolumeClicked();
    void OnPbPlaySpeedClicked();
    void OnPbPlayModeClicked();
    void OnPbListClicked();

signals:
    void PlayStatusChanged(bool isPlaying);
    void PlayModeChanged(PlayMode playMode);
    void PlayVolumeChanged(int volume);
    void PlaySpeedChanged(PlaySpeed playSpeed);
    void ChangeSideBarOpenStatus();
    void OpenSideBar();
    void SwitchMusic(bool isNext);
    void LoadMusic(const MusicDto &music);
    void ProgressBarValueChanged(int value);
};

#endif // PLAYERBAR_H
