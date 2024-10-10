// #include "DataBaseService.h"
#include <QApplication>
#include <QJsonObject>

// template<class T>
// DataBaseSerice<T>::DataBaseSerice(QObject *parent, QString tableName):QObject(parent), tableName(tableName)
// {
//     // this->tableName = tableName;
//     if(dataBase.contains("nmsl"))
//     {
//         dataBase = QSqlDatabase::database("nmsl");
//     }
//     else
//     {
//         dataBase = QSqlDatabase::addDatabase("QSQLITE", "nmsl");
//         dataBase.setDatabaseName(qApp->applicationDirPath() + "/db.db");
//     }

//     if(dataBase.open())
//     {
//         qDebug()<<"数据库连接成功";
//     }
//     else
//     {
//         qDebug()<<"数据库连接失败";
//     }
// }

// template<class T>
// DataBaseSerice<T>::~DataBaseSerice()
// {
//     if (dataBase.isOpen()) {
//         dataBase.close();
//     }
// }

// template<class T>
// QSqlQuery DataBaseSerice<T>::execute(QString queryStr)
// {
//     QSqlQuery query1;
//     query1.exec(queryStr);
//     return query1;
// }

// template<class T>
// QSqlQuery DataBaseSerice<T>::GetAll()
// {
//     QString str = "select * from" + this->tableName + ";";
//     qDebug()<<str;
//     return execute(str);
// }

// template<class T>
// QSqlQuery DataBaseSerice<T>::GetOne(int id)
// {
//     QString str = "select * from " + this->tableName + "where id = " + QString::number(id) + " ;";
//     qDebug()<<str;
//     return execute(str);
// }

// template<class T>
// QSqlQuery DataBaseSerice<T>::Delete(int id)
// {
//     QString str = "delete from " + this->tableName + "where id = " + QString::number(id) + " ;";
//     qDebug()<<str;
//     return execute(str);
// }

// template<class T>
// QSqlQuery DataBaseSerice<T>::Update(T model)
// {
//     QJsonObject json = model.ToJson();
//     QStringList keyList = json.keys();

//     QString keys = ListToString(keyList);
//     QString values = ListToString(keyList, ":");

//     QSqlQuery query;
//     for(int i = 0; i < keyList.count(); i++)
//     {
//         QString key = keyList.at(i);
//         query.bindValue(":"+key, json.value(key));
//     }

//     QString str = "update " + this->tableName + " set " + "where id = " + json.value("Id").toString();
//     // query.exec(str);
//     qDebug()<<str;
//     return query;
// }

// template<class T>
// QSqlQuery DataBaseSerice<T>::Add(T model)
// {
//     QJsonObject json = model.ToJson();
//     QStringList keyList = json.keys();

//     QString keys = ListToString(keyList);
//     QString values = ListToString(keyList, ":");

//     QSqlQuery query;
//     for(int i = 0; i < keyList.count(); i++)
//     {
//         QString key = keyList.at(i);
//         query.bindValue(":"+key, json.value(key));
//     }

//     QString str = "insert into test (" + keys +") values (" + values + ")";
//     query.exec(str);
//     qDebug()<<str;
//     return query;
// }

// template<class T>
// QString DataBaseSerice<T>::ListToString(QStringList sl, QString insert)
// {
//     QString ret = "";
//     if(sl.empty())
//         return ret;
//     ret = ret + insert + sl.at(0);
//     for (int i = 0; i < sl.count(); ++i) {
//         ret = ret + ", " + insert + sl.at(i);
//     }
//     return ret;
// }
