#include "mainwindow.h"

#include <QApplication>
// #include "Service/MusicInfoService.h"
#include "Ui/ClickedEventFilter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // a.installEventFilter(new ClickedEventFilter());
    MainWindow w;
    w.show();
    return a.exec();
}
