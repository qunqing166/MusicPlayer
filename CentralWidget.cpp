#include "CentralWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QJsonObject>
#include <QDir>
#include "SelectBar.h"
#include "PlayerBar.h"
#include "MainWidget.h"

// MainWidget *CentralWidget::MainWidget() const
// {
//     return mainWidget;
// }

MainWidget *CentralWidget::getMainWidget() const
{
    return mainWidget;
}

PlayerBar *CentralWidget::getPlayerBar() const
{
    return playerBar;
}

SelectBar *CentralWidget::getSelectBar() const
{
    return selectBar;
}

TitleBar *CentralWidget::getTitleBar() const
{
    return titleBar;
}

void CentralWidget::SetStartUp(int index, const MusicDto &music)
{
    this->playerBar->SetMusicInfo(music, false);
    this->mainWidget->getSideBar()->SetListCurrentIndex(index);
    this->mainWidget->getIndexWidget()->SetCurrentMusicInfo(music);
}

CentralWidget::CentralWidget(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("central_widget");

    ObjectInit();
    WidgetInit();

    //标题栏最小化按钮
    connect(titleBar, &TitleBar::PbMinClicked, this, [&](){emit Minimize();});
    //标题栏最大化按钮
    connect(titleBar, &TitleBar::PbMaxClicked, this, [&](){emit Maximize();});
    //打开某个歌单, 显示歌单内容
    connect(selectBar, &SelectBar::OpenPlayList, this, [&](const PlayListDto &info){
        this->mainWidget->ToPlayList();
        mainWidget->getContentView()->ShowPlayList(info);
    });
    connect(mainWidget->getIndexWidget(), &IndexWidget::OpenPlayList, this, [&](const PlayListDto &info){
        this->mainWidget->ToPlayList();
        mainWidget->getContentView()->ShowPlayList(info);
    });
    //打开首页
    connect(selectBar, &SelectBar::PageToIndex, this, [&](){mainWidget->ToIndex();});
    //打开侧边栏
    connect(playerBar, &PlayerBar::OpenSideBar, this, [&](){
        if(!mainWidget->getSideBar()->GetOpenStatus())
            this->mainWidget->getSideBar()->Open(mainWidget->geometry());
    });
}

CentralWidget::~CentralWidget()
{
    QJsonObject jsonObj;
    jsonObj.insert("current_playing_index", mainWidget->getSideBar()->getSidePlayList()->currentRow());

    MusicDto music = playerBar->CurrentMusic();
    QJsonObject jsonMusic;

    const QMetaObject *meta = music.metaObject();
    for(int i = 0; i < meta->propertyCount(); i++)
    {
        QString pro = meta->property(i).name();
        jsonMusic.insert(pro, music.property(pro.toStdString().c_str()).toJsonValue());
    }

    jsonObj.insert("current_playing_music", jsonMusic);

    QByteArray jsonStr = QJsonDocument(jsonObj).toJson();
    QFile file(QDir::currentPath() + "/start_up.json");
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        file.write(jsonStr);
        file.close();
    }
}

bool CentralWidget::IsInTitleBar(QPoint pos)
{
    return titleBar->geometry().contains(pos);
}

void CentralWidget::ObjectInit()
{
    int index;
    MusicDto music;
    // ReadStartUp(index, music);
    titleBar = new TitleBar(this);
    selectBar = new SelectBar(this);
    playerBar = new PlayerBar(this);
    mainWidget = new MainWidget(this);
}

void CentralWidget::WidgetInit()
{

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout(this);

    // titleBar->setObjectName("title_bar");
    this->setLayout(vLayout);
    // this->layout()->addItem(vLayout)
    // this->layout().ad
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setSpacing(0);
    vLayout->addWidget(titleBar, 10);
    vLayout->addLayout(hLayout, 80);
    vLayout->addWidget(playerBar, 12);
    hLayout->setSpacing(0);
    hLayout->setAlignment(Qt::AlignLeft);
    hLayout->addWidget(selectBar, 20);
    hLayout->addWidget(mainWidget, 80);
}

// void CentralWidget::ReadStartUp(int &index, MusicDto &music)
// {
//     QByteArray jsonStr;
//     QFile file(QDir::currentPath() + "/start_up.json");
//     if (file.open(QFile::ReadOnly | QFile::Text)) {
//         jsonStr = file.readAll();
//         // qDebug()<<QString(jsonStr.toStdString().c_str());
//         file.close();
//     }

//     QJsonObject jsonObj = QJsonDocument::fromJson(jsonStr).object();

//     index = jsonObj.value("current_playing_index").toInt();
//     // MusicDto m;
//     const QMetaObject *meta = music.metaObject();
//     QJsonObject jsonMusic = jsonObj.value("current_playing_music").toObject();
//     for(int i = 0; i < meta->propertyCount(); i++)
//     {
//         QString name = meta->property(i).name();
//         if(jsonMusic.contains(name))
//         {
//             music.setProperty(name.toStdString().c_str(), jsonMusic.value(name));
//         }
//     }

//     qDebug()<<index;
//     music.Print();
// }
