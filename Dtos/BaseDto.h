#ifndef BASEDTO_H
#define BASEDTO_H

#include <QDateTime>
#include <QMetaObject>
#include <QMetaProperty>

class BaseDto:public QObject
{
    Q_OBJECT

    int id;
    QDateTime createTime = QDateTime::currentDateTime();
    QDateTime updateTime = QDateTime::currentDateTime();

public:

    BaseDto():QObject(nullptr){}
    BaseDto(const BaseDto &value):QObject(nullptr)
    {
        this->id = value.id;
        this->createTime = value.createTime;
        this->updateTime = value.updateTime;
    }
    BaseDto &operator=(const BaseDto &value)//:QObject(nullptr)
    {
        if (this != &value)
        {
            this->id = value.id;
            this->createTime = value.createTime;
            this->updateTime = value.updateTime;
            this->setParent(nullptr);
        }
        return *this;
    }

    void Print()
    {
        const QMetaObject *meta = this->metaObject();
        for(int i = 1; i < meta->propertyCount(); i++)
        {
            QString name = meta->property(i).name();
            qDebug()<<name<<": "<<this->property(name.toStdString().c_str());
        }
    }

    int Id() const;
    void setId(int value);

    QString UpdateTime() const;
    void setUpdateTime(const QString &value);
    void UpdateTimeNow();

    QString CreateTime() const;
    QDateTime CreateDateTime() const;
    void setCreateTime(const QString &value);

signals:

    void IdChanged(int id);
    void CreateTimeChanged();
    void UpdateTimeChanged();

private:

    Q_PROPERTY(int Id READ Id WRITE setId NOTIFY IdChanged FINAL)
    Q_PROPERTY(QString CreateTime READ CreateTime WRITE setCreateTime NOTIFY CreateTimeChanged FINAL)
    Q_PROPERTY(QString UpdateTime READ UpdateTime WRITE setUpdateTime NOTIFY UpdateTimeChanged FINAL)
};


inline QString BaseDto::UpdateTime() const
{
    return createTime.toString("yyyy-MM-dd hh:mm:ss");
}

inline void BaseDto::setUpdateTime(const QString &value)
{
    updateTime = QDateTime::fromString(value, "yyyy-MM-dd hh:mm:ss");
}

inline void BaseDto::UpdateTimeNow()
{
    updateTime = QDateTime::currentDateTime();
}

inline QString BaseDto::CreateTime() const
{
    return updateTime.toString("yyyy-MM-dd hh:mm:ss");
}

inline QDateTime BaseDto::CreateDateTime() const
{
    return createTime;
}

inline void BaseDto::setCreateTime(const QString &value)
{
    createTime = QDateTime::fromString(value, "yyyy-MM-dd hh:mm:ss");
}

inline int BaseDto::Id() const
{
    return id;
}

inline void BaseDto::setId(int value)
{
    id = value;
}

#endif
