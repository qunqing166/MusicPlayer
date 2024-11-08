#pragma once

#include <QDialog>
#include "../Dtos/PlayListDto.h"
#include "../ImageLabel.h"
#include <QLineEdit>

enum EditMode
{
    Mode_Add,
    Mode_Edit
};

class PlayListEditor:public QDialog
{

    Q_OBJECT
    
    Model::PlayList info;
    ImageLabel *imageLabel;
    QLineEdit *lineEdit;
    EditMode mode;

public:
    PlayListEditor(const Model::PlayList &info, EditMode mode = Mode_Edit);

private:
    bool IsImageFilePath(const QString &path);

signals:
    void SendInfo(const Model::PlayList &info);
    void CreatePlayList(const Model::PlayList &info);
};
