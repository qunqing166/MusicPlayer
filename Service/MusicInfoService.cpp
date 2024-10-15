// #include "MusicInfoService.h"
// #include <QJsonObject>
// #include <QJsonArray>

// MusicInfoService::MusicInfoService()
// {
//     dbService = new DataBaseService<MusicInfo>("Music");
// }

// MusicInfoService::~MusicInfoService()
// {
//     delete dbService;
// }

// Response<QList<MusicInfo>> MusicInfoService::GetAll()
// {
//     Response<QSqlQuery> res = dbService->GetAll();
//     if(!res.Status())
//     {
//         return Response<QList<MusicInfo>>("GetAll Error In MusicInfoService");
//     }
//     QSqlQuery query = res.Result();
//     QStringList keys = dbService->GetTableHeads();
//     QList<MusicInfo> list;
//     while(query.next())
//     {
//         QJsonObject obj;
//         foreach (auto key, keys) {
//             obj.insert(key, query.value(key).toJsonValue());
//             // if(!query.isNull("BelongingPlayList"))
//             // {
//             //     qDebug()<<query.value("BelongingPlayList");
//             // }
//             // query.value(key).
//         }
//         MusicInfo m;
//         m.FromJson(obj);
//         list.append(m);
//     }

//     return Response<QList<MusicInfo>>(true, list);
// }

// Response<QList<MusicInfo> > MusicInfoService::GetAll(QString value, QueryParameterMusic type)
// {
//     QString parameter;
//     if(type == MusicName)
//     {
//         parameter = QString("MusicName = '%1'").arg(value);
//     }
//     else if(type == PlayList)
//     {
//         parameter = QString("BelongingPlayList like '%%1%'").arg(value);
//     }

//     Response<QSqlQuery> res = dbService->GetAll(parameter);
//     if(!res.Status())
//     {
//         return Response<QList<MusicInfo>>("GetAll Error In MusicInfoService");
//     }
//     QSqlQuery query = res.Result();
//     QStringList keys = dbService->GetTableHeads();
//     QList<MusicInfo> list;
//     while(query.next())
//     {
//         QJsonObject obj;
//         foreach (auto key, keys) {
//             obj.insert(key, query.value(key).toJsonValue());
//         }
//         MusicInfo m;
//         m.FromJson(obj);
//         list.append(m);
//     }

//     return Response<QList<MusicInfo>>(true, list);
// }

// Response<MusicInfo> MusicInfoService::GetOne(int id)
// {
//     Response<QSqlQuery> res = dbService->GetOne(id);
//     if(!res.Status())
//     {
//         return Response<MusicInfo>("GetOne Error In MusicInfoService");
//     }
//     QSqlQuery query = res.Result();
//     QJsonObject json;
//     QStringList keys = dbService->GetTableHeads();
//     query.next();
//     foreach (auto key, keys) {
//         json.insert(key, query.value(key).toJsonValue());
//     }
//     MusicInfo m;
//     m.FromJson(json);
//     return Response<MusicInfo>(true, m);
// }

// Response<MusicInfo> MusicInfoService::Update(MusicInfo model)
// {
//     Response<QSqlQuery> res = dbService->Update(model);
//     if(!res.Status())
//     {
//         return Response<MusicInfo>("Update Error In MusicInfoService");
//     }
//     // QSqlQuery query = res.Result();
//     return Response<MusicInfo>(true, model);
// }

// Response<QString> MusicInfoService::Delete(int id)
// {
//     Response<QSqlQuery> res = dbService->Delete(id);
//     if(!res.Status())
//     {
//         return Response<QString>("Delete Error In MusicInfoService");
//     }
//     // QSqlQuery query = res.Result();
//     return Response<QString>(true, "delete success!");
// }

// Response<MusicInfo> MusicInfoService::Add(MusicInfo model)
// {
//     Response<QSqlQuery> res = dbService->Add(model);
//     if(!res.Status())
//     {
//         return Response<MusicInfo>("Add Error In MusicInfoService");
//     }
//     // QSqlQuery query = res.Result();
//     return Response<MusicInfo>(true, model);
// }

