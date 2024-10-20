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

    PlayListDto info;
    ImageLabel *imageLabel;
    QLineEdit *lineEdit;
    EditMode mode;

public:
    PlayListEditor(const PlayListDto &info, EditMode mode = Mode_Edit);

private:
    bool IsImageFilePath(const QString &path);

signals:
    void SendInfo(const PlayListDto &info);
    void CreatePlayList(const PlayListDto &info);
};
