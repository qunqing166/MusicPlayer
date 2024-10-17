#include "PlayListContentView.h"
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "PlayListView.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include "taglib/tag.h"
// #include "taglib/tag.h"
#include "taglib/fileref.h"


PlayListView *PlayListContentView::getPlayListView() const
{
    return playListView;
}

PlayListContentView::PlayListContentView(QWidget *parent):QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("song_sheet_content");
    ObjectInit();
    WidgetInit();
    // ShowPlayList()

    connect(pbAdd, &QPushButton::clicked, this, &PlayListContentView::OnPbAddClicked);
}

PlayListContentView::PlayListContentView(const PlayListDto &info, QWidget *parent):QWidget(parent)
{
    this->playList = info;
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("song_sheet_content");
    ObjectInit();
    WidgetInit();
    ShowPlayList(this->playList);

    connect(pbAdd, &QPushButton::clicked, this, &PlayListContentView::OnPbAddClicked);
}

void PlayListContentView::ShowPlayList(const PlayListDto &info)
{
    // this->playList = info;
    imageLabel->SetPixmap(QPixmap(info.CoverImagePath()));
    sheetTitleLabel->setText(info.ListName());
    userImage->SetPixmap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\yyn.jpg"));
    userNameLabel->setText(info.Creator());
    createTimeLabel->setText(QString("创建于 %1").arg(info.CreateDateTime().toString("yyyy-MM-dd")));
    playListView->ShowPlayList(info.ListName());
    // createTimeLabel->setText("创建于11-45-14");
}

void PlayListContentView::ObjectInit()
{
    imageLabel = new ImageLabel(this);
    int imageSize = 100;
    imageLabel->setFixedSize(imageSize, imageSize);
    // imageLabel->SetPixmap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\liyue.webp"));
    // imageLabel->setObjectName("sheet_image_label");

    sheetTitleLabel = new QLabel(this);
    // sheetTitleLabel->setText("我喜欢");
    sheetTitleLabel->setObjectName("sheet_title_label");

    int userImageSize = 20;
    userImage = new ImageLabel(this);
    userImage->SetPixmap(QPixmap("C:\\Users\\qunqing\\Desktop\\图片\\yyn.jpg"));
    userImage->setFixedSize(userImageSize, userImageSize);

    userNameLabel = new QLabel(this);
    userNameLabel->setText("qunqing166");
    userNameLabel->setObjectName("sheet_user_name");

    createTimeLabel = new QLabel(this);
    // createTimeLabel->setText("创建于11-45-14");
    createTimeLabel->setObjectName("sheet_user_name");

    pbPlay = new QPushButton(this);
    pbPlay->setObjectName("sheet_button_play");
    pbPlay->setText("播放");
    pbPlay->setIcon(QIcon(":/scr/icon/stopping.png"));
    pbPlay->setFixedSize(80, 30);

    pbEdit = new QPushButton(this);
    pbEdit->setObjectName("sheet_button_edit");
    pbEdit->setIcon(QIcon(":/scr/icon/edit.png"));
    pbEdit->setFixedSize(30, 30);

    playListView = new PlayListView(this);

    pbAdd = new QPushButton("+", this);
    pbAdd->setFixedSize(30, 30);
    pbAdd->setObjectName("sheet_button_edit");

    emit ListCreated();
}

void PlayListContentView::WidgetInit()
{
    // QScrollArea *
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setAlignment(Qt::AlignTop);
    this->setLayout(vLayout);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);

    hLayout1->addWidget(imageLabel, Qt::AlignLeft);

    QVBoxLayout *vLayout2 = new QVBoxLayout(this);
    hLayout1->addLayout(vLayout2);
    vLayout2->setAlignment(Qt::AlignBottom);
    vLayout2->addWidget(sheetTitleLabel);

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
    // QLabel *labelTitle = new QLabel("标题", this);
    // QLabel *labelSingers = new QLabel("歌手", this);
    // QLabel *labelAlbum = new QLabel("专辑", this);
    // QLabel *labelDuration = new QLabel("时长", this);
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

        MusicDto music;
        if(title == "")
            music.setMusicName(fileInfo.completeBaseName());
        else
            music.setMusicName(title);
        music.setMusicPath(path);
        music.setAlbum(album);
        music.setDuration(QTime::fromMSecsSinceStartOfDay(duration).toString("mm:ss"));
        music.InsertPlayList(this->sheetTitleLabel->text());
        music.setSingers(artist);
        playListView->Add(music);
        return;
    }

    //将数据写入对象
    QMediaPlayer p(this);
    p.setSource(QUrl::fromLocalFile(path));
    MusicDto music;
    music.setMusicPath(path);
    qDebug()<<p.duration();
    // p.
    // music.setDuration(QString::asprintf("%02lld:%02lld", p.duration() / 60000, p.duration() / 1000));
    qDebug()<<music.Duration();
    music.setMusicName(fileInfo.completeBaseName());
    music.InsertPlayList(this->sheetTitleLabel->text());
    //添加至列表
    playListView->Add(music);
}
