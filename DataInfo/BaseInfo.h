#ifndef BASEINFO_H
#define BASEINFO_H

#include <QObject>
#include <QDateTime>
#include <QJsonObject>

class BaseInfo
{
public:
    // BaseInfo(QObject *parent = nullptr):QObject(parent){}
    // BaseInfo(const BaseInfo &a):QObject()
    // {
    //     this->id = a.id;
    //     this->createTime = a.createTime;
    //     this->updateTime = a.updateTime;
    // }

    int id = 0;
    QDateTime createTime = QDateTime::currentDateTime();
    QDateTime updateTime = QDateTime::currentDateTime();

    QJsonObject ToJson()
    {
        QJsonObject json;
        json.insert("Id", id);
        json.insert("CreateTime", createTime.toString("yyyy-MM-dd hh:mm:ss"));
        json.insert("UpdateTime", updateTime.toString("yyyy-MM-dd hh:mm:ss"));
        return json;
    }
    void FromJson(QJsonObject json)
    {
        id = json.value("Id").toInt();
        createTime = QDateTime::fromString(json.value("CreateTime").toString(), "yyyy-MM-dd hh:mm:ss");
        updateTime = QDateTime::fromString(json.value("UpdateTime").toString(), "yyyy-MM-dd hh:mm:ss");
    }
};

#endif // BASEINFO_H
