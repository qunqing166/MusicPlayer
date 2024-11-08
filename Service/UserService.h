#pragma once

#include "BaseService.h"
#include "../Dtos/UserDto.h"

namespace Service
{

class UserService:public BaseService<Model::User>
{
public:
    UserService();
};

}
