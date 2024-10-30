#ifndef BASESERVICE_H
#define BASESERVICE_H

#include "DataBaseService.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QMetaObject>
#include <QObject>
#include <QMetaProperty>
// #include "../DataInfo/MusicInfo.h"

template<class T>
class BaseService
{
    DataBaseService *dbService;
public:
    BaseService<T>()
    {
        dbService = new DataBaseService(T::TableName);
        // qDebug()<<T::TableName;
    }

    BaseService<T>(const QString &tableName)
    {
        dbService = new DataBaseService(tableName);
        // qDebug()<<tableName;
    }

    ~BaseService<T>()
    {
        delete dbService;
    }

    QList<T> GetAll() const
    {
        QSqlQuery query = dbService->GetAll();
        if(query.lastError().isValid())
            qDebug()<<query.lastError().databaseText();
        QList<T> models;
        while(query.next())
        {
            T model;
            DataBaseService::QueryToObject(&model, query);
            models.append(model);
        }
        return models;
    }

    T GetOne(int id) const
    {
        QSqlQuery query = dbService->GetOne(id);
        T model;
        DataBaseService::QueryToObject(&model, query);
        return model;
    }

    T GetOneByParameter(const QString &field, const QVariant &value)
    {
        QString str = QString("select * from %1 where %2 = :%2;").arg(dbService->TableName()).arg(field);
        QSqlQuery query;
        query.prepare(str);
        query.bindValue(":"+field, value);
        query.exec();
        query.next();
        T model;
        DataBaseService::QueryToObject(&model, query);
        return model;
    }

    QList<T> GetAllByParameter(const QString &field, const QVariant &value)
    {
        QString str = QString("select * from %1 where %2 = :%2;").arg(dbService->TableName()).arg(field);
        QSqlQuery query;
        query.prepare(str);
        query.bindValue(":"+field, value);
        query.exec();
        QList<T> list;
        while(query.next())
        {
            T model;
            DataBaseService::QueryToObject(&model, query);
            list.append(model);
        }
        return list;
    }

    T GetOneByParameter(const QString &parameter)
    {
        QString str = QString("select * from %1 where %2;").arg(dbService->TableName()).arg(parameter);
        QSqlQuery query(str);
        T model;
        query.next();
        DataBaseService::QueryToObject(&model, query);
        return model;
    }

    bool IsExist(const QString &field, const QVariant &value)
    {
        QString str = QString("select count(*) as count_value from %1 where %2 = :%2;")
                          .arg(dbService->TableName()).arg(field);
        QSqlQuery query;
        query.prepare(str);
        query.bindValue(":"+field, value);
        query.exec();
        query.next();
        int num = query.value("count_value").toInt();
        return num;
    }

    bool IsExist(const QString &parameter)
    {
        QString str = QString("select count(*) as count_value from %1 where %2;").arg(dbService->TableName()).arg(parameter);
        QSqlQuery query(str);
        query.next();
        int num = query.value("count_value").toInt();
        return num;
    }

    bool Update(T model)
    {
        model.UpdateTimeNow();
        return dbService->Update(&model);
    }

    bool Delete(int id)
    {
        return dbService->Delete(id);
    }

    bool DeleteByParameter(const QString &field, const QVariant &value)
    {
        QString str = QString("delete from %1 where %2 = :%2").arg(dbService->TableName()).arg(field);
        QSqlQuery query;
        query.prepare(str);
        query.bindValue(":" + field, value);
        if(!query.exec())
            return false;
        return true;
    }

    bool Add(const T &model)
    {
        return dbService->Add(&model);
    }

};

#endif // BASESERVICE_H
