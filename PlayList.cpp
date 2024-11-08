#include "PlayList.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QStringListModel>
#include <QSpacerItem>
#include <QStandardItemModel>
#include <QPainter>
#include "Dtos/PlayListDto.h"
#include "Service/BaseService.h"
#include "Service/PlayListService.h"

using namespace Service;
using namespace UI;

PlayList::PlayList(QString title, QWidget *parent):QWidget(parent), title(title)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("PlayList");
    ObjectInit();
    DataInit();
    WidgetInit();

    connect(pbOpen, &QPushButton::clicked, this, &PlayList::OnPbOpenClicked);
    connect(pbOpenAnima, &QPropertyAnimation::valueChanged, this, [&](){
        QPixmap pm = QPixmap::fromImage(QImage(":/scr/icon/botton.png").transformed(QTransform().rotate(angle)));
        this->pbOpen->setIcon(QIcon(pm));
    });
    connect(listHeiAnima, &QPropertyAnimation::valueChanged, this, [&](){
        this->listView->setFixedHeight(listHeight);
    });

    // QListView::in
    connect(listView, &QListView::clicked, this, [&](const QModelIndex &index){
        if(this->isContentOPen)
        {
            emit OpenPlayList(playLists.at(index.row()));
        }
    });

    connect(pbAdd, &QPushButton::clicked, this, [&](){
        playListEditor = new PlayListEditor(Model::PlayList(), Mode_Add);
        playListEditor->show();
        connect(playListEditor, &PlayListEditor::CreatePlayList, this, &PlayList::CreateNewPlayList);
    });
}

void PlayList::ObjectInit()
{
    int size = 30;
    labelInfo = new QLabel(this);
    labelInfo->setObjectName("PlayList_Label");
    labelInfo->setFixedHeight(size);

    pbAdd = new QPushButton(this);

    pbAdd->setFixedSize(size, size);
    pbAdd->setIcon(QIcon(":/scr/icon/add (2).png"));

    pbOpen = new QPushButton(this);
    pbOpen->setFixedSize(size, size);
    pbOpen->setIcon(QIcon(":/scr/icon/top.png"));

    pbOpenAnima = new QPropertyAnimation(this, "Angle");
    pbOpenAnima->startTimer(100);

    listHeiAnima = new QPropertyAnimation(this, "ListHeight");
    listHeiAnima->startTimer(100);

    listView = new QListView(this);
    listView->setObjectName("PlayList_View");
    listView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    model = new QStandardItemModel(this);

    this->setTitle(title);
}

void PlayList::WidgetInit()
{
    this->setContentsMargins(QMargins(0,0,0,0));
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setContentsMargins(0,0,0,0);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);

    QWidget *widget = new QWidget(this);
    widget->setObjectName("song_sheet_bar");
    widget->setFixedHeight(40);
    vLayout->addWidget(widget);
    widget->setLayout(hLayout1);

    hLayout1->addWidget(labelInfo);
    hLayout1->addWidget(pbAdd);
    hLayout1->addWidget(pbOpen);
    vLayout->addWidget(listView);

}

void PlayList::DataInit()
{
    listView->setModel(model);
    PlayListService service;

    playLists = service.GetPlayListFromUser();

    for(int i = 0; i < playLists.count(); i++)
    {
        Model::PlayList p = playLists.at(i);
        QStandardItem *item = new QStandardItem();
        QIcon icon(ImageLabel::GetRadiusPixmap(QPixmap(p.CoverImagePath()), 4));
        item->setIcon(icon);
        item->setText(p.ListName());
        items.append(item);
    }
    model->appendColumn(items);
    int iconSize = 35;
    listView->setIconSize(QSize(iconSize, iconSize));
    int space = 5;
    listView->setSpacing(5);
    listView->setFixedHeight(0);
}

void PlayList::CreateNewPlayList(const Model::PlayList &newList)
{
    PlayListService service;
    service.Add(newList);
    playListEditor->disconnect();
    playListEditor->deleteLater();
    UpdateData();
}

void PlayList::setTitle(QString value)
{
    this->title = value;
    this->labelInfo->setText(this->title);
}

void PlayList::UpdateData()
{
    BaseService<Model::PlayList> service;
    playLists = service.GetAll();

    foreach(auto p, items)
    {
        delete p;
    }
    items.clear();

    for(int i = 0; i < playLists.count(); i++)
    {
        Model::PlayList p = playLists.at(i);
        QStandardItem *item = new QStandardItem();
        item->setIcon(QIcon(p.CoverImagePath()));
        item->setText(p.ListName());
        items.append(item);
    }
    model->appendColumn(items);

    listView->setFixedHeight((50) * listView->model()->rowCount());
    listView->setModel(nullptr);
    listView->setModel(model);

}

void PlayList::OnPbOpenClicked()
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
    }
    isContentOPen = !isContentOPen;

    pbOpenAnima->start();
    listHeiAnima->start();
}
