#pragma once

#include "BaseDto.h"
#include "../Service/BaseService.h"

namespace Model
{

class User:public Base
{
    Q_OBJECT

    QString userName;
    QString headImagePath;

    static User *myUserInfo;

public:

    const static QString TableName;

    static void GetUserInfo(int id);
    static const User* MyUserInfo();

    QString UserName() const;
    void setUserName(const QString &value);

    QString HeadImagePath() const;
    void setHeadImagePath(const QString &value);

signals:
    void UserNameChanged(QString userName);

    void HeadImagePathChanged(QString headImagePath);

private:
    Q_PROPERTY(QString UserName READ UserName WRITE setUserName NOTIFY UserNameChanged FINAL)
    Q_PROPERTY(QString HeadImagePath READ HeadImagePath WRITE setHeadImagePath NOTIFY HeadImagePathChanged FINAL)
};

inline User* User::myUserInfo = nullptr;

inline const QString User::TableName = "User";

inline QString User::HeadImagePath() const
{
    return headImagePath;
}

inline void User::setHeadImagePath(const QString &value)
{
    if (headImagePath == value)
        return;
    headImagePath = value;
    emit HeadImagePathChanged(headImagePath);
}

inline void User::GetUserInfo(int id)
{
    if(myUserInfo == nullptr)
    {
        myUserInfo = new User();
        Service::BaseService<User> service;
        *myUserInfo = service.GetOne(id);
    }
}

inline const User* User::MyUserInfo()
{
    return myUserInfo;
}

inline QString User::UserName() const
{
    return userName;
}

inline void User::setUserName(const QString &value)
{
    if (userName == value)
        return;
    userName = value;
    emit UserNameChanged(userName);
}

}
