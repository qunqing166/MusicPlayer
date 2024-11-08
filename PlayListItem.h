#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QWidget>
#include <QLabel>
#include "Dtos/MusicDto.h"
#include "ImageLabel.h"
#include <QPushButton>
#include "UI/MoreMenu.h"
#include <QPointer>
// #include "Service/DataBaseService.h"

namespace UI
{

//歌曲列表item界面
class PlayListItem:public QWidget
{
    Q_OBJECT

    //UI组件
    QLabel *indexLabel;     //索引
    ImageLabel *image;      //封面
    QLabel *songName;       //歌名
    QLabel *singers;        //歌手
    QLabel *album;          //专辑
    QLabel *duration;       //时长
    QPushButton *pbMore;    //更多
    //保存数据
    Model::Music musicInfo;

    QPointer<MoreMenu> menu;

    int index;

public:
    PlayListItem(const Model::Music &value, int index, QWidget *parent = nullptr);
    //设置显示数据
    void SetData(Model::Music &value);
    //获取数据
    Model::Music getMusicInfo() const;

private:
    void ObjectInit();
    void WidgetInit();

signals:
    
    void MenuOperateTrigger(const Model::Music &music, const MenuOperate &op);

};

}

#endif // PLAYLISTITEM_H
