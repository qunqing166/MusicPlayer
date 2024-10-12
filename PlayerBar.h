#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QWidget>
#include <QLabel>
#include "ImageLabel.h"
#include <QPushButton>
#include "DataInfo/MusicInfo.h"


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

class PlayerBar:public QWidget
{
    Q_OBJECT

    MusicInfo musicInfo;

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

public:
    PlayerBar(QWidget *parent = nullptr);
    void SetMusicInfo(MusicInfo musicInfo);
    void SetPlayStatus(bool is);

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
};

#endif // PLAYERBAR_H
