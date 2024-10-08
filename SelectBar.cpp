#include "SelectBar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

SelectBar::SelectBar(QWidget* parent) :QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("select_bar");

    ObjectInit();
    DataInit();
    WidgetInit();
}

void SelectBar::WidgetInit()
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignTop);
    this->setLayout(vLayout);

    vLayout->addWidget(labelHeadImage);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);
    hLayout1->addWidget(labelHeadImage);
    hLayout1->addWidget(labelUserName);
    hLayout1->addWidget(pbUserInfo);

    QHBoxLayout *hLayout2 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout2);

    vLayout->addWidget(treeWidget);
}

void SelectBar::ObjectInit()
{
    labelHeadImage = new ImageLabel(this);
    labelHeadImage->SetPixmap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\hj.png"));
    int imageSize = 35;
    labelHeadImage->setFixedSize(imageSize, imageSize);

    labelUserName = new QLabel("qunqing166", this);
    labelUserName->setObjectName("select_bar_user_name");

    pbUserInfo = new QPushButton(this);
    pbUserInfo->setFixedSize(40, 40);
    pbUserInfo->setObjectName("select_bar_button");
    pbUserInfo->setIcon(QIcon(":/scr/icon/arrow_right.png"));

    treeWidget = new QTreeWidget(this);
    treeWidget->setHeaderHidden(true);
    // QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
    // item->setText(0, "nmsl");
    // treeWidget->addTopLevelItem(item);
    // item->addChild(new QTreeWidgetItem({"nsml"}));
    // treeWidget->setRootIsDecorated(false);
    // treeWidget->setItemWidget(item, 0, new PlayerBar(this));
}

void SelectBar::DataInit()
{
    // QTreeWidgetItem *headItem = new QTreeWidgetItem(treeWidget);
    // treeWidget->setRootIsDecorated(false);
    // headItem->addChild(new QTreeWidgetItem({"nmsl"}));
    // QTreeWidgetItem *headItem1 = new QTreeWidgetItem(treeWidget);
}
