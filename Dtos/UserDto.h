#pragma once

#include "BaseDto.h"

class UserDto:public BaseDto
{

    static QString userName;
    static QString headImagePath;

public:

    static void SetUserName(const QString &name)
    {
        userName = name;
    }
    static void SetHeadImagePath(const QString &path)
    {
        headImagePath = path;
    }

    static QString UserName()
    {
        return userName;
    }
    static QString HeadImagePath()
    {
        return headImagePath;
    }
};

inline QString  UserDto::userName = "qunqing166";
inline QString UserDto::headImagePath = ":/scr/image/yyn.jpg";
