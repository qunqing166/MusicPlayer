#include "DataBaseService.h"
#include <QMetaObject>
#include <QSqlResult>
#include <QSqlError>

QSqlQuery DataBaseService::GetAll()
{
    QString str = QString("select * from %1;").arg(tableName);
    return QSqlQuery(str);
    // QSqlQuery query(str);
    // query.next();
    // return query;
}

QSqlQuery DataBaseService::GetOne(int id)
{
    QString str = QString("select * from %1 where Id = %2;").arg(tableName).arg(id);
    QSqlQuery query(str);
    query.next();
    return query;
}

bool DataBaseService::Add(const QObject *obj)
{
    QString keys = SerializeProperty(obj->metaObject(), "%1");
    QString values = SerializeProperty(obj->metaObject(), ":%1");
    QString str = QString("insert into %1 (%2) values (%3);").arg(tableName).arg(keys).arg(values);
    // QString ss = QString::asprintf("insert into %1 (%2) values (%2);", tableNam)

    QSqlQuery query;
    query.prepare(str);

    const QMetaObject *meta = obj->metaObject();
    for(int i = 1; i < meta->propertyCount(); i++)
    {
        QString propertyName = meta->property(i).name();
        query.bindValue(":"+propertyName, obj->property(propertyName.toStdString().c_str()));
    }
    qDebug()<<query.boundValueNames();
    qDebug()<<query.boundValues();
    qDebug()<<query.executedQuery();
    if(!query.exec())
    {
        qDebug()<<query.lastError().databaseText();
        return false;
    }
    return true;
}

bool DataBaseService::Delete(int id)
{
    QString str = QString("delete from %1 where Id = %2").arg(tableName).arg(id);
    QSqlQuery query;
    if(!query.exec(str))
        return false;
    return true;
}

bool DataBaseService::Update(const QObject *obj)
{
    const QMetaObject *meta = obj->metaObject();
    QString set = SerializeProperty(meta, "%1 = :%1");
    QString str = QString("update %1 set %2 where Id = :Id").arg(tableName).arg(set);

    QSqlQuery query;
    query.prepare(str);

    for(int i = 1; i < meta->propertyCount(); i++)
    {
        QString propertyName = meta->property(i).name();
        query.bindValue(":"+propertyName, obj->property(propertyName.toStdString().c_str()));
    }

    if(!query.exec())
        return false;
    return true;
}

inline QSqlQuery DataBaseService::QueryByString(QString str)
{
    return QSqlQuery(str);
}

void DataBaseService::QueryToObject(QObject *obj, const QSqlQuery &query)
{
    const QMetaObject *metaObj = obj->metaObject();
    for(int i = 0; i < metaObj->propertyCount(); i++)
    {
        QMetaProperty property = metaObj->property(i);
        if(query.record().contains(property.name()))
        {
            obj->setProperty(property.name(), query.value(property.name()));
            // qDebug()<<property.name()<<":"<<obj->property(property.name());
        }
    }
}

bool DataBaseService::Connect()
{
    QSqlDatabase dataBase;
    // if(dataBase.contains(ConnectName))
    // {
    //     dataBase = QSqlDatabase::database(ConnectName);
    // }
    // else
    // {
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    // dataBase.setDatabaseName(qApp->applicationDirPath() + "/scr/db/db.db");
    dataBase.setDatabaseName("D:\\code\\Qt\\learning\\MusicPlayer\\scr\\db\\db.db");
    // }

    if(dataBase.open())
    {
        qDebug()<<"数据库连接成功";
        return true;
    }
    else
    {
        qDebug()<<"数据库连接失败";
        return false;
    }
}

void DataBaseService::Disconnect()
{
    QSqlDatabase dataBase;
    // if(dataBase.contains(ConnectName))
    // {
    //     dataBase = QSqlDatabase::database(ConnectName);
    // }
    // else
    // {
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    // dataBase.setDatabaseName(qApp->applicationDirPath() + "/scr/db/db.db");
    dataBase.setDatabaseName("D:\\code\\Qt\\learning\\MusicPlayer\\scr\\db\\db.db");
    // }

    dataBase.close();
}

QString DataBaseService::SerializeProperty(const QMetaObject *meta, const QString &format)
{
    QString str = "";

    if(meta->propertyCount() > 1)
        str = QString(format).arg(meta->property(1).name());

    for(int i = 2; i < meta->propertyCount(); i++)
    {
        str = str + QString(", " + format).arg(meta->property(i).name());
    }
    return str;
}


DataBaseService::DataBaseService()
{
    Connect();
}

DataBaseService::DataBaseService(QString tableName)
{
    this->tableName = tableName;
    Connect();
    // qDebug()<<"db: "<<tableName;
}

DataBaseService::~DataBaseService()
{
    Disconnect();
}

void DataBaseService::SetTableName(const QString &tableName)
{
    this->tableName = tableName;
}