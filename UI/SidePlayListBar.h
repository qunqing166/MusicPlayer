#ifndef SIDEPLAYLISTBAR_H
#define SIDEPLAYLISTBAR_H

#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTimer>
#include "ClickedEventFilter.h"
#include "SidePlayList.h"

class SidePlayListBar:public QWidget
{
    Q_OBJECT

    QPushButton *pbClose;           //关闭bar
    QPushButton *pbCrt;             //显示当前播放列表
    QPushButton *pbRecord;          //显示播放记录
    QPropertyAnimation *geoAnima;   //出场动画
    ClickedEventFilter *clickFilter;//过滤器, 用作打开bar后的全局点击事件检测
    QRect parentGeo;                //父窗口的窗口数据
    SidePlayList *sidePlayList;     //显示歌曲列表

    int dWidth = 0;     //用作动画的移动的偏移量
    bool isButtonDrive = true;
    bool isOpen = false;
    const int maxWidth = 300;

public:
    SidePlayListBar(QWidget *parent = nullptr);
    //打开Bar, 传入父窗口信息, 用于位置判断和高度设置
    void Open(QRect geo);
    //关闭窗口
    void Close();
    //获取当前的打开状态
    bool GetOpenStatus(){return this->isOpen;}

    int DWidth() const;
    void setDWidth(int newWidth);

    SidePlayList* getSidePlayList() const;

    void setCurrentMusicIndex(int index);

    void ResetButton();

signals:
    void DWidthChanged();
    void OpenRecordList(const QString &tableName);
    // void CurrentPlayListChanged(const QList<MusicDto> &list);

private:
    void ObjectInit();
    void WidgetInit();
    //动画结束响应
    void OnAnimationFinished();
    //全局点击事件响应
    void OnMousePressed(const QPoint &pos);
    //打开播放历史
    void OnPbRecordClicked();
    //打开播放列表
    void OnPbCrtClicked();

    Q_PROPERTY(int DWidth READ DWidth WRITE setDWidth NOTIFY DWidthChanged FINAL)
};

#endif // SIDEPLAYLISTBAR_H
