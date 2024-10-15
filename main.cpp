#include "mainwindow.h"

#include <QApplication>
// #include "Service/MusicInfoService.h"
// #include "Ui/ClickedEventFilter.h"
// #include "Dtos/MusicDto.h"
// #include "Service/DataBaseService.h"
// #include "Service/BaseService.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
