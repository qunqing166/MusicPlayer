#include "SongSheetList.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QStringListModel>
#include <QSpacerItem>
#include <QStandardItemModel>
#include <QPainter>

SongSheetList::SongSheetList(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);

    ObjectInit();
    DataInit();
    WidgetInit();

    connect(pbOpen, &QPushButton::clicked, this, &SongSheetList::OnPbOpenClicked);
    connect(pbOpenAnima, &QPropertyAnimation::valueChanged, this, [&](){
        QPixmap pm = QPixmap::fromImage(QImage(":/scr/icon/arrow_down.png").transformed(QTransform().rotate(angle)));
        this->pbOpen->setIcon(QIcon(pm));
    });
    connect(listHeiAnima, &QPropertyAnimation::valueChanged, this, [&](){
        this->listView->setFixedHeight(listHeight);
    });
}

QPixmap SongSheetList::GetRadiusPiamap(QPixmap pixmap, int radius)
{
    QSize size = pixmap.size();
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), radius, radius);

    pixmap.setMask(mask);
    return pixmap;
}

void SongSheetList::ObjectInit()
{
    int size = 30;
    labelInfo = new QLabel(this);
    labelInfo->setObjectName("song_sheet_list_label");
    labelInfo->setFixedHeight(size);

    pbAdd = new QPushButton(this);

    pbAdd->setFixedSize(size, size);
    pbAdd->setObjectName("song_sheet_list_button");
    pbAdd->setIcon(QIcon(":/scr/icon/add.png"));

    pbOpen = new QPushButton(this);
    pbOpen->setFixedSize(size, size);
    pbOpen->setObjectName("song_sheet_list_button");
    pbOpen->setIcon(QIcon(":/scr/icon/arrow_up.png"));

    pbOpenAnima = new QPropertyAnimation(this, "Angle");
    pbOpenAnima->startTimer(500);

    listHeiAnima = new QPropertyAnimation(this, "ListHeight");
    listHeiAnima->startTimer(500);

    listView = new QListView(this);
    listView->setObjectName("song_sheet_list_view");
    listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void SongSheetList::WidgetInit()
{
    this->setContentsMargins(QMargins(0,0,0,0));
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);
    // vLayout->setSpacing(0);
    vLayout->setContentsMargins(0,0,0,0);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    // hLayout1->setSpacing(0);
    // hLayout1->setContentsMargins(0,0,0,0);
    // vLayout->addLayout(hLayout1);

    QWidget *widget = new QWidget(this);
    widget->setObjectName("song_sheet_bar");
    widget->setFixedHeight(40);
    vLayout->addWidget(widget);
    widget->setLayout(hLayout1);

    hLayout1->addWidget(labelInfo);
    hLayout1->addWidget(pbAdd);
    hLayout1->addWidget(pbOpen);
    vLayout->addWidget(listView);


    // this->setStyleSheet("background-color:black;");
    // vLayout->addWidget(new QLabel(this), Qt::AlignTop);
}

void SongSheetList::DataInit()
{
    // listWidget->addItem(new QListWidgetItem("nmsl"));
    // listWidget->addItem(new QListWidgetItem("nmsl"));

    QStandardItemModel *model = new QStandardItemModel(this);
    listView->setModel(model);
    QList<QStandardItem*>items;

    int count = 5;
    for(int i = 0; i < count; i++)
    {
        QStandardItem *item = new QStandardItem();
        QIcon icon(GetRadiusPiamap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\liyue.webp"), 4));
        // item->setIcon(QIcon("C:\\Users\\qunqing\\Desktop\\图片\\liyue.webp"));
        item->setIcon(icon);
        item->setText("nmsl");
        items.append(item);
        // items.append()
    }
    model->appendColumn(items);
    int iconSize = 35;
    listView->setIconSize(QSize(iconSize, iconSize));
    int space = 5;
    listView->setSpacing(5);
    // listView->setFixedHeight((45 + space) * count);
    listView->setFixedHeight(0);
    // listView->setFixedHeight(500);
    // listView->setModel();
}

void SongSheetList::setTitle(QString value)
{
    this->title = value;
    this->labelInfo->setText(this->title);
}

void SongSheetList::OnPbOpenClicked()
{
    if(isContentOPen)
    {
        pbOpenAnima->setStartValue(0);
        pbOpenAnima->setEndValue(180);

        listHeiAnima->setStartValue(listView->height());
        listHeiAnima->setEndValue(0);
    }
    else
    {
        pbOpenAnima->setStartValue(180);
        pbOpenAnima->setEndValue(0);

        listHeiAnima->setStartValue(0);
        listHeiAnima->setEndValue((45 + 5) * listView->model()->rowCount());
        qDebug()<<listView->model()->rowCount();

    }
    isContentOPen = !isContentOPen;

    pbOpenAnima->start();
    listHeiAnima->start();
}
