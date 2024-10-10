#ifndef PLAYLISTCONTENTVIEW_H
#define PLAYLISTCONTENTVIEW_H

#include <QWidget>
#include "ImageLabel.h"
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

class PlayListContentView:public QWidget
{
    Q_OBJECT

    ImageLabel *imageLabel;
    QLabel *sheetTitleLabel;
    ImageLabel *userImage;
    QLabel *userNameLabel;
    QLabel *createTimeLabel;
    QPushButton *pbPlay;
    QPushButton *pbEdit;

public:
    PlayListContentView(QWidget *parent = nullptr);

private:
    void ObjectInit();
    void WidgetInit();
};

#endif // PLAYLISTCONTENTVIEW_H
