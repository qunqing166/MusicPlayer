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

    ImageLabel *labelHeadImage;
    QLabel *labelUserName;
    QPushButton *pbUserInfo;
    QPushButton *pbIndex;
    PlayList *playList;

    bool isInPageIndex = true;

public:
    SelectBar(QWidget* parent);
    const PlayList* GetPlayList(){return playList;}

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
