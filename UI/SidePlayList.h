#ifndef SIDEPLAYLIST_H
#define SIDEPLAYLIST_H

#include <QListWidget>
#include "../Dtos/MusicDto.h"

class SidePlayList:public QListWidget
{
    Q_OBJECT

    //保存播放列表数据
    QList<MusicDto> *musicInfos;
    //musicInfos索引对Id的映射
    QMap<int, int> *musicsMap;
    //当前播放列表
    QString playingListName;

public:
    SidePlayList(QWidget *parent = nullptr);
    //根据歌单名更新列表, 从数据库获得数据
    void UpdateList(const QString &tableName);
    //根据传入的列表更新
    void UpdateList(const QList<MusicDto> &musicList);
    //添加播放列表一条记录
    void Add(const MusicDto &value);
    //当前播放列表名
    QString PlayingListName() const;

public slots:
    //用于响应歌单内播放音乐，加载如播放列表
    void PlayNewList(const QString &name, int index, const QList<MusicDto> &list);

signals:
    //播放音乐信号
    void PlayMusic(const MusicDto &music);

protected:
    //拦截单击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //双击事件发送信号
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    //拦截鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    //初始化操作
    void ObjectInit();
    void WidgetInit();
    void DataInit();

    //根据数据列表的改变更新显示内容
    void UpdateWidget();
    //用于删除播放列表的一条记录
    void Delete(int index);
    //根据数据列表的改变，更新map
    void UpdateMap();
};

#endif // SIDEPLAYLIST_H
