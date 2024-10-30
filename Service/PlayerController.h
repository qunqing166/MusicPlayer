#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
// #include "../DataInfo/MusicInfo.h"
#include "../Dtos/MusicDto.h"

class PlayerController:public QObject
{
    Q_OBJECT

    QMediaPlayer *mediaPlayer;
    // QMediaPlayList
    QAudioOutput *audioOutput;

    bool isCheckMusic = false;

    QList<MusicDto> playingList;

    int currentPlayingIndex = 0;

    QList<MusicDto> currentMusicList;
    int currentMusicIndex;
    QString currentPlaylistName;

    bool isListNameChanged = false;

    static PlayerController* instance;

public:
    PlayerController(QObject *parent = nullptr);

    static PlayerController* Instance();

    void AddToPlayList(const MusicDto &music);

    void SetPlayingList(const QList<MusicDto> &value);

    QList<MusicDto> CurrentMusicList() const;
    void setCurrentMusicList(const QList<MusicDto> &value, int index = 0);

    int CurrentMusicIndex() const;
    void setCurrentMusicIndex(int value);

    QString CurrentPlaylistName() const;
    void setCurrentPlaylistName(const QString &value);

    void setPlayStatus(bool is);

    void ReadStartUp(int index);

    QMediaPlayer *getMediaPlayer() const;


private:
    void ObjectInit();

    void PlayMusic(const MusicDto &music);

    void AddToRecord(const MusicDto &music);

public slots:
    void OpenNewMusic(const MusicDto &info);

    QMediaPlayer *MediaPlayer() const;
    void LoadMusic(const MusicDto &music);
    void OnProgressBarValueChanged(int value);


signals:
    void UpdatePlayBarStatus(const MusicDto &music);

    void CurrentMusicChanged(const MusicDto &music);
    void CurrentMusicIndexChanged(int index);
    void CurrentMusicListChanged(const QList<MusicDto> &list, int index);
    void DurationChanged(int duration);
};

#endif // PLAYERCONTROLLER_H
