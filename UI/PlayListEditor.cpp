#include "PlayListEditor.h"
#include "ImageLabel.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>

using namespace Model;

PlayListEditor::PlayListEditor(const PlayList &info, EditMode mode):QDialog(nullptr)
{
    this->info = info;
    this->mode = mode;

    this->setModal(true);
    this->setFixedSize(400, 250);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    this->setLayout(vLayout);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    vLayout->addLayout(hLayout);

    imageLabel = new ImageLabel(this);
    imageLabel->setFixedSize(150, 150);
    imageLabel->SetPixmap(":/scr/icon/cover_empty.png");
    hLayout->addWidget(imageLabel);

    QPushButton *button = new QPushButton("选择封面", this);
    button->setFixedSize(80, 30);
    hLayout->addWidget(button);

    QLabel *label = new QLabel("歌单名称", this);
    vLayout->addWidget(label);

    lineEdit = new QLineEdit(this);
    lineEdit->setText(info.ListName());
    vLayout->addWidget(lineEdit);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    vLayout->addLayout(hLayout1);

    QPushButton* btnConfirm = new QPushButton("确认", this);
    QPushButton* btnCancel = new QPushButton("取消", this);
    hLayout1->addWidget(btnConfirm);
    hLayout1->addWidget(btnCancel);

    connect(button, &QPushButton::clicked, this, [&](){
        QString filePath = QFileDialog::getOpenFileName(this, "选择", QDir::homePath());
        if(IsImageFilePath(filePath))
        {
            this->info.setCoverImagePath(filePath);
            imageLabel->SetPixmap(this->info.CoverImagePath());
        }
    });
    connect(btnCancel, &QPushButton::clicked, this, [&](){
        this->deleteLater();
    });
    connect(btnConfirm, &QPushButton::clicked, this, [&](){
        this->info.setListName(this->lineEdit->text());
        if(this->mode == Mode_Edit)
            emit SendInfo(this->info);
        else if(this->mode == Mode_Add)
            emit CreatePlayList(this->info);
    });
}

bool PlayListEditor::IsImageFilePath(const QString &path)
{
    bool is = false;

    QFile fi(path);
    if (fi.open(QIODevice::ReadOnly)) {
        QPixmap pix;
        pix.loadFromData(fi.readAll());

        is = !pix.isNull();
        fi.close();
    }

    return is;
}
