#pragma once

#include "BaseService.h"
#include "../Dtos/UserDto.h"

class UserService:public BaseService<UserDto>
{
public:
    UserService();
};
