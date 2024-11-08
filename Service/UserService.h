#pragma once

#include "BaseService.h"
#include "../Model/User.h"

namespace Service
{

class UserService:public BaseService<Model::User>
{
public:
    UserService();
};

}
