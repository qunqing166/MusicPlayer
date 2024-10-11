#ifndef IBASESERVICE_H
#define IBASESERVICE_H

#include <QJsonObject>
#include "Response.h"

template<class T>
class IBaseService
{
public:
    virtual Response<QList<T>> GetAll() = 0;
    virtual Response<T> GetOne(int id) = 0;
    virtual Response<T> Update(T model) = 0;
    virtual Response<QString> Delete(int id) = 0;
    virtual Response<T> Add(T model) = 0;
};

#endif
