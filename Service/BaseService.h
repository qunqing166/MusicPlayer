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

    bool Update(T model)
    {
        model.UpdateTimeNow();
        return dbService->Update(&model);
    }

    bool Delete(int id)
    {
        return dbService->Delete(id);
    }

    bool Add(const T &model)
    {
        return dbService->Add(&model);
    }

};

// template<class T>
// class BaseService:public IBaseService<T>
// {
//     DataBaseService<T> *dbService;

// public:
//     BaseService()
//     {
//         dbService = new DataBaseService<T>(T::ThisName());
//     }

//     virtual Response<QList<T>> GetAll() override
//     {
//         Response<QSqlQuery> res = dbService->GetAll();
//         if(!res.Status())
//         {
//             return Response<QList<T>>("GetAll Error In MusicInfoService");
//         }
//         QSqlQuery query = res.Result();
//         QStringList keys = dbService->GetTableHeads();
//         QList<T> list;
//         while(query.next())
//         {
//             QJsonObject obj;
//             foreach (auto key, keys) {
//                 obj.insert(key, query.value(key).toJsonValue());
//             }
//             T m;
//             m.FromJson(obj);
//             list.append(m);
//         }

//         return Response<QList<T>>(true, list);
//     }
//     virtual Response<T> GetOne(int id) override
//     {
//         Response<QSqlQuery> res = dbService->GetOne(id);
//         if(!res.Status())
//         {
//             return Response<T>("GetOne Error In MusicInfoService");
//         }
//         QSqlQuery query = res.Result();
//         QJsonObject json;
//         QStringList keys = dbService->GetTableHeads();
//         query.next();
//         foreach (auto key, keys) {
//             json.insert(key, query.value(key).toJsonValue());
//         }
//         T m;
//         m.FromJson(json);
//         return Response<T>(true, m);
//     }
//     virtual Response<T> Update(T model) override
//     {
//         Response<QSqlQuery> res = dbService->Update(model);
//         if(!res.Status())
//         {
//             return Response<T>("Update Error In MusicInfoService");
//         }
//         // QSqlQuery query = res.Result();
//         return Response<T>(true, model);
//     }
//     virtual Response<QString> Delete(int id) override
//     {
//         Response<QSqlQuery> res = dbService->Delete(id);
//         if(!res.Status())
//         {
//             return Response<QString>("Delete Error In MusicInfoService");
//         }
//         // QSqlQuery query = res.Result();
//         return Response<QString>(true, "delete success!");
//     }
//     virtual Response<T> Add(T model) override
//     {
//         Response<QSqlQuery> res = dbService->Add(model);
//         if(!res.Status())
//         {
//             return Response<T>("Add Error In MusicInfoService");
//         }
//         // QSqlQuery query = res.Result();
//         return Response<T>(true, model);
//     }
// };

#endif // BASESERVICE_H
