#pragma once

#include "BaseDto.h"
#include "../Service/BaseService.h"

class UserDto:public BaseDto
{
    Q_OBJECT

    QString userName;
    QString headImagePath;

    static UserDto *myUserInfo;

public:

    const static QString TableName;

    static void GetUserInfo(int id);
    static const UserDto* MyUserInfo();

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

inline UserDto* UserDto::myUserInfo = nullptr;

inline const QString UserDto::TableName = "User";

inline QString UserDto::HeadImagePath() const
{
    return headImagePath;
}

inline void UserDto::setHeadImagePath(const QString &value)
{
    if (headImagePath == value)
        return;
    headImagePath = value;
    emit HeadImagePathChanged(headImagePath);
}

inline void UserDto::GetUserInfo(int id)
{
    if(myUserInfo == nullptr)
    {
        myUserInfo = new UserDto();
        BaseService<UserDto> service;
        *myUserInfo = service.GetOne(id);
    }
}

inline const UserDto* UserDto::MyUserInfo()
{
    return myUserInfo;
}

inline QString UserDto::UserName() const
{
    return userName;
}

inline void UserDto::setUserName(const QString &value)
{
    if (userName == value)
        return;
    userName = value;
    emit UserNameChanged(userName);
}
