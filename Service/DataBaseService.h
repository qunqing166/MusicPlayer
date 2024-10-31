#ifndef DATABASESERVICE_H
#define DATABASESERVICE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>
// #include <QApplication>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QSqlRecord>
// #include "Response.h"

class DataBaseService
{
    // const static QString ConnectName(){return "nmsl";};
    // const static QString ConnectName;
    QString tableName;

public:

    DataBaseService();

    DataBaseService(QString tableName);

    ~DataBaseService();

    void SetTableName(const QString &tableName);

    QSqlQuery GetAll();

    QSqlQuery GetOne(int id);

    bool Add(const QObject* obj);

    bool Delete(int id);

    bool Update(const QObject* obj);
    //通过自定义字符串查询
    QSqlQuery QueryByString(QString str);
    //将查询结果转成对象
    static void QueryToObject(QObject* obj, const QSqlQuery &query);
    //链接数据库
    static bool Connect();
    //断开数据库
    static void Disconnect();

    static void CreateDataBase();

    QString SerializeProperty(const QMetaObject* meta, const QString &format);

    QString TableName() const
    {
        return this->tableName;
    }

};

#endif // DATABASESERVICE_H
