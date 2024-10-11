#ifndef IMUSICINFOSERVICE_H
#define IMUSICINFOSERVICE_H

#include "IBaseService.h"
#include "../DataInfo/MusicInfo.h"
#include <QObject>

class IMusicInfoService:public IBaseService<MusicInfo>
{
public:
    virtual Response<QList<MusicInfo>> GetAll() override;
    // virtual Response<MusicInfo> GetOne(int id) override;
};

#endif // IMUSICINFOSERVICE_H
