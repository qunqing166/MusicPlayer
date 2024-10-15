#include "IndexWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include "MoreMenu.h"

IndexWidget::IndexWidget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QLabel *label = new QLabel("还没想好做啥", this);
    this->setLayout(hLayout);
    hLayout->addWidget(label);

    QFont font;
    font.setPointSize(30);
    label->setFont(font);

    MoreMenu *menu = new MoreMenu(this);
    menu->hide();
}
