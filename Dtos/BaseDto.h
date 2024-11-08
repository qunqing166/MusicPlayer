#ifndef BASEDTO_H
#define BASEDTO_H

#include <QDateTime>
#include <QMetaObject>
#include <QMetaProperty>

namespace Model
{

class Base:public QObject
{
    Q_OBJECT

    int id;
    QDateTime createTime = QDateTime::currentDateTime();
    QDateTime updateTime = QDateTime::currentDateTime();

public:

    Base():QObject(nullptr){}
    Base(const Base &value):QObject(nullptr)
    {
        this->id = value.id;
        this->createTime = value.createTime;
        this->updateTime = value.updateTime;
    }
    Base &operator=(const Base &value)//:QObject(nullptr)
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


inline QString Base::UpdateTime() const
{
    return createTime.toString("yyyy-MM-dd hh:mm:ss");
}

inline void Base::setUpdateTime(const QString &value)
{
    updateTime = QDateTime::fromString(value, "yyyy-MM-dd hh:mm:ss");
}

inline void Base::UpdateTimeNow()
{
    updateTime = QDateTime::currentDateTime();
}

inline QString Base::CreateTime() const
{
    return updateTime.toString("yyyy-MM-dd hh:mm:ss");
}

inline QDateTime Base::CreateDateTime() const
{
    return createTime;
}

inline void Base::setCreateTime(const QString &value)
{
    createTime = QDateTime::fromString(value, "yyyy-MM-dd hh:mm:ss");
}

inline int Base::Id() const
{
    return id;
}

inline void Base::setId(int value)
{
    id = value;
}

}

#endif
