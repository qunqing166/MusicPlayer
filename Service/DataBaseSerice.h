// #ifndef DATABASESERVICE_H
// #define DATABASESERVICE_H

// #include <QtSql/QSqlDatabase>
// #include <QtSql/QSqlError>
// #include <QtSql/QSqlQuery>
// #include <QObject>
// #include <QApplication>

// template<class T>
// class DataBaseSerice:public QObject
// {
//     QSqlDatabase dataBase;
//     QString tableName;
//     QSqlQuery query;

// public:
//     DataBaseSerice(QObject *parent = nullptr, QString tableName = "")
//     {
//         this->tableName = tableName;
//         // if(dataBase.contains("nmsl"))
//         // {
//         //     dataBase = QSqlDatabase::database("nmsl");
//         // }
//         // else
//         // {
//         dataBase = QSqlDatabase::addDatabase("QSQLITE");
//         // dataBase.setDatabaseName(qApp->applicationDirPath() + "/scr/db/db.db");
//         dataBase.setDatabaseName("D:\\code\\Qt\\learning\\MusicPlayer\\scr\\db\\db.db");
//             // qDebug()<<qApp->applicationDirPath() + "/scr/db/db.db";
//         // }

//         if(dataBase.open())
//         {
//             qDebug()<<"数据库连接成功";
//         }
//         else
//         {
//             qDebug()<<"数据库连接失败";
//         }
//     }
//     ~DataBaseSerice()
//     {
//         if (dataBase.isOpen()) {
//             dataBase.close();
//         }
//     }
//     void SetTableName(QString tableName){this->tableName = tableName;};

//     QSqlQuery execute(QString queryStr)
//     {
//         QSqlQuery query1;
//         query1.exec(queryStr);
//         return query1;
//     }
//     QSqlQuery GetAll()
//     {
//         QString str = "select * from " + this->tableName + ";";
//         qDebug()<<str;
//         return QSqlQuery(str);
//         // qDebug()<<str;
//         // return execute(str);
//     }

//     QSqlQuery GetOne(int id);
//     QSqlQuery Delete(int id);
//     QSqlQuery Update(T model);
//     QSqlQuery Add(T model);

// private:
//     QString ListToString(QStringList sl, QString insert = "");
// };

// #endif // DATABASESERVICE_H
