#ifndef SELECTBAR_H
#define SELECTBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "ImageLabel.h"
#include <QListView>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class SelectBar : public QWidget
{
    Q_OBJECT

    ImageLabel *labelHeadImage;
    QLabel *labelUserName;
    QPushButton *pbUserInfo;
    QTreeWidget *treeWidget;

public:
    SelectBar(QWidget* parent);

private:
    void WidgetInit();
    void ObjectInit();
    void DataInit();
};

#endif // SELECTBAR_H
