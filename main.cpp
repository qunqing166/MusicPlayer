#include "mainwindow.h"
#include <QApplication>
#include <QFileInfo>
#include "Service/DataBaseService.h"

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);

    QFileInfo fileInfo(qApp->applicationDirPath() + "/db.db");
    if(!fileInfo.isFile())
    {
        Service::DataBaseService::CreateDataBase();
    }

    MainWindow w;
    w.show();
    return a.exec();
}
