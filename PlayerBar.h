#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QWidget>
#include <QLabel>
#include "Dtos/MusicDto.h"
#include "ImageLabel.h"
#include "ProgressBar.h"
#include <QPushButton>
#include "Service/PlayerController.h"
#include <QSlider>

//播放控制栏
class PlayerBar:public QWidget
{
    Q_OBJECT

    MusicDto musicInfo;

    bool isPlaying = false;
    bool isMute = false;
    int volume = 50;
    PlayMode playMode;
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

    bool isFirstPlay = true;

    ProgressBar *progressBar;

public:

    PlayerBar(QWidget *parent = nullptr);
    void SetMusicInfo(const MusicDto &musicInfo, bool isOpen = true);
    void SetPlayStatus(bool is);

    void OnPositionChanged(qint64 sec);

    MusicDto CurrentMusic() const;

    PlayMode getPlayMode() const;
    void setPlayMode(PlayMode value);

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

    void OpenSideBar();

};

#endif // PLAYERBAR_H
