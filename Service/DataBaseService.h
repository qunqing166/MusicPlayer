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
    const static QString ConnectName;
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

    QString SerializeProperty(const QMetaObject* meta, const QString &format);

    QString TableName() const;

};

inline QString DataBaseService::TableName() const
{
    return this->tableName;
}

inline const QString DataBaseService::ConnectName = "nmsl";
// template<class T>
// class DataBaseService//:public QObject
// {
//     QSqlDatabase dataBase;
//     QString tableName;
//     QSqlQuery query;

//     QStringList tableHeads;

// private:
//     void GetTableInfo()
//     {
//         QString str = "PRAGMA table_info(" + tableName + ")";
//         QSqlQuery query(str);
//         while(query.next())
//         {
//             tableHeads.append(query.value(1).toString());
//         }
//         // qDebug()<<"heads: "<<tableHeads;
//     }

//     QString SerializeList(QStringList sl, QString insert = "")
//     {
//         if(sl.empty())return "";
//         QString str = insert + sl.at(0);

//         for(int i = 1; i < sl.count(); i++)
//         {
//             str = str + QString(", %1%2").arg(insert).arg(sl.at(i));
//         }
//         return str;
//     }

// public:
//     DataBaseService(QString tableName = "")
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
//             GetTableInfo();
//         }
//         else
//         {
//             qDebug()<<"数据库连接失败";
//         }
//     }
//     ~DataBaseService()
//     {
//         if (dataBase.isOpen()) {
//             dataBase.close();
//         }
//     }

//     QStringList GetTableHeads(){return this->tableHeads;}

//     void SetTableName(QString tableName){this->tableName = tableName;};

//     Response<QSqlQuery> GetAll()
//     {
//         // QString str = "select * from " + this->tableName + ";";
//         QString str = QString("select * from %1;").arg(this->tableName);
//         qDebug()<<str;
//         QSqlQuery query;
//         if(query.exec(str))
//         {
//             return Response<QSqlQuery>(true, std::move(query));
//         }
//         else
//         {
//             return Response<QSqlQuery>("GetAll Error");
//         }
//     }

//     Response<QSqlQuery> GetAll(QString parameter)
//     {
//         QString str = QString("select * from %1 where %2;").arg(this->tableName).arg(parameter);
//         qDebug()<<str;
//         QSqlQuery query;
//         if(query.exec(str))
//         {
//             return Response<QSqlQuery>(true, std::move(query));
//             qDebug()<<query.executedQuery();
//         }
//         else
//         {
//             return Response<QSqlQuery>("GetAll Error");
//         }
//     }

//     Response<QSqlQuery> GetOne(int id)
//     {
//         QString str = QString("select * from %1 where Id = %2;")
//                           .arg(this->tableName).arg(id);
//         // qDebug()<<str;
//         QSqlQuery query;
//         if(query.exec(str))
//         {
//             return Response<QSqlQuery>(true, std::move(query));
//         }
//         else
//         {
//             return Response<QSqlQuery>("GetOne Error");
//         }
//         // return QSqlQuery(str);
//     }

//     Response<QSqlQuery> Delete(int id)
//     {
//         QString str = QString("delete from %1 where Id = %2")
//                           .arg(this->tableName).arg(id);
//         QSqlQuery query;
//         if(query.exec(str))
//         {
//             return Response<QSqlQuery>(true, std::move(query));
//         }
//         else
//         {
//             return Response<QSqlQuery>("Delete Error");
//         }
//         // return QSqlQuery(str);
//     }

//     Response<QSqlQuery> Update(T model)
//     {
//         QSqlQuery query;
//         QJsonObject json = model.ToJson();
//         QString str = QString("update %1 set ").arg(this->tableName);
//         QStringList sl = json.keys();
//         if(sl.empty())return Response<QSqlQuery>("更新数据为空");
//         QString newValue = QString("%1 = :%1").arg(sl.at(0));
//         for(int i = 1; i < sl.count(); i++)
//         {
//             QString key = sl.at(i);
//             newValue = newValue + QString(", %1 = :%1").arg(key);
//             query.bindValue(":" + key, json.value(key).toString());
//         }
//         str = QString("update %1 set %2 where id = %3;")
//                   .arg(this->tableName).arg(newValue).arg(json.value("Id").toInt());
//         qDebug()<<json.value("Id").toInt();
//         query.prepare(str);

//         foreach (auto key, sl)
//         {
//             query.bindValue(":" + key, json.value(key).toVariant());
//         }
//         if(query.exec())
//         {
//             return Response<QSqlQuery>(true, std::move(query));
//         }
//         else
//         {
//             return Response<QSqlQuery>("Update Error");
//         }
//         // qDebug()<<"update: "<<query.executedQuery();
//         // return query;
//     }

//     Response<QSqlQuery> Add(T model)
//     {
//         QSqlQuery query;
//         QJsonObject json = model.ToJson();

//         QString keyStr = SerializeList(json.keys());
//         QString valueStr = SerializeList(json.keys(),":");

//         QString str = QString("insert into %1 (%2) values(%3);")
//                           .arg(this->tableName)
//                           .arg(keyStr)
//                           .arg(valueStr);

//         query.prepare(str);
//         foreach (auto key, json.keys())
//         {
//             query.bindValue(":" + key, json.value(key).toString());
//         }
//         // qDebug()<<"add: "<<str;
//         if(query.exec())
//         {
//             return Response<QSqlQuery>(true, std::move(query));
//         }
//         else
//         {
//             return Response<QSqlQuery>("Add Error");
//         }
//         // return query;
//     }

//     Response<QSqlQuery> QueryByString(QString queryStr)
//     {
//         QSqlQuery query(queryStr);
//         return Response<QSqlQuery>(true, std::move(query));
//     }

// private:
//     QString ListToString(QStringList sl, QString insert = "");
// };



#endif // DATABASESERVICE_H
