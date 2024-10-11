#include "PlayListInfoService.h"

PlayListInfoService::PlayListInfoService()
{
    dbService = new DataBaseService<PlayListInfo>("PlayList");
}

PlayListInfoService::~PlayListInfoService()
{
    delete dbService;
}

Response<QList<PlayListInfo> > PlayListInfoService::GetAll()
{
    Response<QSqlQuery> res = dbService->GetAll();
    if(!res.Status())
    {
        return Response<QList<PlayListInfo>>("GetAll Error In MusicInfoService");
    }
    QSqlQuery query = res.Result();
    QStringList keys = dbService->GetTableHeads();
    QList<PlayListInfo> list;
    while(query.next())
    {
        QJsonObject obj;
        foreach (auto key, keys) {
            obj.insert(key, query.value(key).toJsonValue());
        }
        PlayListInfo m;
        m.FromJson(obj);
        list.append(m);
    }

    return Response<QList<PlayListInfo>>(true, list);
}

Response<QList<PlayListInfo> > PlayListInfoService::GetAll(QString str, QueryParameterPlayList type)
{
    QString parameter;
    if(type == PlayListName)
    {
        parameter = QString("ListName = '%1'").arg(str);
    }
    else if(type == Creator)
    {
        parameter = QString("Creator = '%1'").arg(str);
    }

    Response<QSqlQuery> res = dbService->GetAll(parameter);
    if(!res.Status())
    {
        return Response<QList<PlayListInfo>>("GetAll Error In MusicInfoService");
    }
    QSqlQuery query = res.Result();
    QStringList keys = dbService->GetTableHeads();
    QList<PlayListInfo> list;
    while(query.next())
    {
        QJsonObject obj;
        foreach (auto key, keys) {
            obj.insert(key, query.value(key).toJsonValue());
        }
        PlayListInfo m;
        m.FromJson(obj);
        list.append(m);
    }

    return Response<QList<PlayListInfo>>(true, list);
}

Response<PlayListInfo> PlayListInfoService::GetOne(int id)
{
    Response<QSqlQuery> res = dbService->GetOne(id);
    if(!res.Status())
    {
        return Response<PlayListInfo>("GetOne Error In MusicInfoService");
    }
    QSqlQuery query = res.Result();
    QJsonObject json;
    QStringList keys = dbService->GetTableHeads();
    query.next();
    foreach (auto key, keys) {
        json.insert(key, query.value(key).toJsonValue());
    }
    PlayListInfo m;
    m.FromJson(json);
    return Response<PlayListInfo>(true, m);
}

Response<PlayListInfo> PlayListInfoService::Update(PlayListInfo model)
{
    Response<QSqlQuery> res = dbService->Update(model);
    if(!res.Status())
    {
        return Response<PlayListInfo>("Update Error In MusicInfoService");
    }
    // QSqlQuery query = res.Result();
    return Response<PlayListInfo>(true, model);
}

Response<QString> PlayListInfoService::Delete(int id)
{
    Response<QSqlQuery> res = dbService->Delete(id);
    if(!res.Status())
    {
        return Response<QString>("Delete Error In MusicInfoService");
    }
    // QSqlQuery query = res.Result();
    return Response<QString>(true, "delete success!");
}

Response<PlayListInfo> PlayListInfoService::Add(PlayListInfo model)
{
    Response<QSqlQuery> res = dbService->Add(model);
    if(!res.Status())
    {
        return Response<PlayListInfo>("Add Error In MusicInfoService");
    }
    // QSqlQuery query = res.Result();
    return Response<PlayListInfo>(true, model);
}
