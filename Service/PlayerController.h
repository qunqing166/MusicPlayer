#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "../Model/Music.h"

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

class PlayerController:public QObject
{
    Q_OBJECT

    QMediaPlayer *mediaPlayer;
    // QMediaPlayList
    QAudioOutput *audioOutput;

    bool isCheckMusic = false;
    
    QList<Model::Music> playingList;
    
    QList<Model::Music> currentMusicList;
    int currentMusicIndex;
    QString currentPlaylistName;

    bool isListNameChanged = false;

    long long position;

    float volume = 100;

    static PlayerController* instance;

    PlayMode playMode;
    PlaySpeed playSpeed;

public:
    PlayerController(QObject *parent = nullptr);
    ~PlayerController();

    static PlayerController* Instance();
    
    void AddToPlayList(const Model::Music &music);
    
    void SetPlayingList(const QList<Model::Music> &value);
    
    QList<Model::Music> CurrentMusicList() const;
    void setCurrentMusicList(const QList<Model::Music> &value, int index = 0);
    
    Model::Music CurrentMusic() const;

    int CurrentMusicIndex() const;
    void setCurrentMusicIndex(int value);

    QString CurrentPlaylistName() const;
    void setCurrentPlaylistName(const QString &value);

    void setPlayStatus(bool is);

    void ReadStartUp();

    QMediaPlayer *getMediaPlayer() const;
    QAudioOutput *getAudioOutput() const;

    void ToNextMusic();
    void ToLastMusic();


    long long Position() const;

    PlayMode getPlayMode() const;

    void setPlayMode(const PlayMode &value);

    void SetVolume(bool isMute);

private:
    void ObjectInit();
    
    void PlayMusic(const Model::Music &music);
    
    void AddToRecord(const Model::Music &music);

public slots:
    void OpenNewMusic(const Model::Music &info);

    QMediaPlayer *MediaPlayer() const;
    void LoadMusic(const Model::Music &music);
    void OnProgressBarValueChanged(int value);


signals:
    void UpdatePlayBarStatus(const Model::Music &music);
    
    void CurrentMusicChanged(const Model::Music &music);
    void CurrentMusicIndexChanged(int index);
    void CurrentMusicListChanged(const QList<Model::Music> &list, int index);
    void DurationChanged(int duration);
};

#endif // PLAYERCONTROLLER_H
