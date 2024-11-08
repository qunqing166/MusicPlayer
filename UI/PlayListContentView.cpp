#include "PlayListContentView.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "PlayListView.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include "../Service/BaseService.h"
#include "taglib/tag.h"
#include "../Model/User.h"
#include "taglib/fileref.h"
#include "PlayListEditor.h"

using namespace Model;
using namespace Service;

PlayListView *PlayListContentView::getPlayListView() const
{
    return playListView;
}

PlayListContentView::PlayListContentView(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    ObjectInit();
    WidgetInit();

    connect(pbAdd, &QPushButton::clicked, this, &PlayListContentView::OnPbAddClicked);

    connect(pbEdit, &QPushButton::clicked, this, [&](){
        playListEditor = new PlayListEditor(this->playList);
        playListEditor.data()->show();
        connect(playListEditor, &PlayListEditor::SendInfo, this, &PlayListContentView::OnEditPlayList);
    });

    connect(pbPlay, &QPushButton::clicked, playListView, &PlayListView::OnPlayList);
}

void PlayListContentView::ShowPlayList(const Model::PlayList &info)
{

    this->playList = info;
    imageLabel->SetPixmap(info.CoverImagePath());
    playListNameLabel->setText(info.ListName());
    userImage->SetPixmap("C:\\Users\\qunqing\\Desktop\\图片\\yyn.jpg");
    userNameLabel->setText(User::MyUserInfo()->UserName());
    createTimeLabel->setText(QString("·创建于 %1").arg(info.CreateDateTime().toString("yyyy-MM-dd")));
    playListView->ShowPlayList(info.ListName());
}

void PlayListContentView::ObjectInit()
{
    imageLabel = new ImageLabel(this);
    int imageSize = 100;
    imageLabel->setFixedSize(imageSize, imageSize);

    playListNameLabel = new QLabel(this);
    playListNameLabel->setObjectName("PlayList_Name");

    int userImageSize = 20;
    userImage = new ImageLabel(this);
    userImage->SetPixmap("C:\\Users\\qunqing\\Desktop\\图片\\yyn.jpg");
    userImage->setFixedSize(userImageSize, userImageSize);

    userNameLabel = new QLabel(this);
    userNameLabel->setText("qunqing166");
    userNameLabel->setObjectName("user_name");

    createTimeLabel = new QLabel(this);
    createTimeLabel->setObjectName("user_name");

    pbPlay = new QPushButton(this);
    pbPlay->setObjectName("button_play");
    pbPlay->setText("播放");
    pbPlay->setIcon(QIcon(":/scr/icon/stopping.png"));
    pbPlay->setFixedSize(80, 30);

    pbEdit = new QPushButton(this);
    pbEdit->setObjectName("button_edit");
    pbEdit->setIcon(QIcon(":/scr/icon/edit.png"));
    pbEdit->setFixedSize(30, 30);

    playListView = new PlayListView("", this);

    pbAdd = new QPushButton("+", this);
    pbAdd->setFixedSize(30, 30);
    pbAdd->setObjectName("button_edit");

}

void PlayListContentView::WidgetInit()
{
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignTop);
    this->setLayout(vLayout);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);

    hLayout1->addWidget(imageLabel, Qt::AlignLeft);

    QVBoxLayout *vLayout2 = new QVBoxLayout(this);
    hLayout1->addLayout(vLayout2);
    vLayout2->setAlignment(Qt::AlignBottom);
    vLayout2->addWidget(playListNameLabel);

    QHBoxLayout *hLayout2_1 = new QHBoxLayout(this);
    hLayout2_1->setAlignment(Qt::AlignLeft);
    hLayout2_1->addWidget(userImage);
    hLayout2_1->addWidget(userNameLabel);
    hLayout2_1->addWidget(createTimeLabel);
    vLayout2->addLayout(hLayout2_1);

    QHBoxLayout *hLayout2_2 = new QHBoxLayout(this);
    hLayout2_2->setAlignment(Qt::AlignLeft);
    hLayout2_2->addWidget(pbPlay);
    hLayout2_2->addWidget(pbEdit);
    hLayout2_2->addWidget(pbAdd, Qt::AlignRight);
    vLayout2->addLayout(hLayout2_2);

    QHBoxLayout *hLayout3 = new QHBoxLayout(this);

    QLabel *title = new QLabel("音乐", this);
    title->setFixedHeight(40);
    QLabel *number = new QLabel("10", this);
    vLayout->addLayout(hLayout3);
    hLayout3->addWidget(title);
    hLayout3->addWidget(number);
    hLayout3->addWidget(new QLabel(this), Qt::AlignLeft);
    vLayout->setAlignment(Qt::AlignLeft);

    vLayout->addWidget(playListView);
}

void PlayListContentView::OnPbAddClicked()
{
    //获取文件路径
    QString path = QFileDialog::getOpenFileName(this, "选择", QDir::homePath(), "*.mp3");
    QFileInfo fileInfo(path);
    //如果路径无效, 直接返回
    if(!fileInfo.isFile())
        return;

    // TagLib::FileRef file(path.toStdString().c_str());
    TagLib::FileRef file(path.toStdWString().c_str());
    // TagLib::FileRef file(TagLib::FileName( QStringToTString(path).toCString(true)));
    if(!file.isNull() && file.tag())
    {
        qDebug()<<"add";
        TagLib::Tag *tag = file.tag();
        TagLib::AudioProperties *properties = file.audioProperties();
        QString title = tag->title().toCString();
        QString artist = tag->artist().toCString();
        QString album = tag->album().toCString();
        int duration = properties->lengthInMilliseconds();
        
        Music music;
        if(title == "")
            music.setMusicName(fileInfo.completeBaseName());
        else
            music.setMusicName(title);
        music.setMusicPath(path);
        music.setAlbum(album);
        music.setDuration(QTime::fromMSecsSinceStartOfDay(duration).toString("mm:ss"));
        music.InsertPlayList(this->playListNameLabel->text());
        music.setSingers(artist);
        playListView->Add(music);
        return;
    }
}

void PlayListContentView::OnEditPlayList(const PlayList &info)
{
    BaseService<PlayList> service;

    QString str = QString("alter table PlayList_%1 rename to PlayList_%2;").arg(this->playList.ListName(), info.ListName());

    this->playList = info;
    service.Update(info);

    QSqlQuery query(str);

    ShowPlayList(this->playList);
    emit PlayListDataChanged();
    playListEditor->deleteLater();
}
