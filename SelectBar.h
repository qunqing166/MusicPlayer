#ifndef SELECTBAR_H
#define SELECTBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "ImageLabel.h"
#include <QListView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "PlayList.h"

class SelectBar : public QWidget
{
    Q_OBJECT

    //用户头像
    ImageLabel *labelUserHeadImage;
    //用户名
    QLabel *labelUserName;
    //按钮, 进入用户信息编辑界面
    QPushButton *pbUserInfo;
    //按钮, 进入首页
    QPushButton *btnToIndex;
    //显示歌单的列表
    PlayList *playList;
    //是否处于首页
    bool isInPageIndex = true;

public:
    SelectBar(QWidget* parent);
    PlayList* GetPlayList() const{return playList;}

private:
    void WidgetInit();
    void ObjectInit();
    void DataInit();

    void OnPbIndexClicked();
    void OnOpenPlayList(const PlayListDto &info);

signals:
    void PageToIndex();
    void OpenPlayList(const PlayListDto &info);
};

#endif // SELECTBAR_H
