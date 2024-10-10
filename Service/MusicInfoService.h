#ifndef MUSICINFOSERVICE_H
#define MUSICINFOSERVICE_H

#include "IBaseService.h"
#include "../DataInfo/MusicInfo.h"
#include "DataBaseService.h"

class MusicInfoService:public IBaseService<MusicInfo>
{
    DataBaseService<MusicInfo> *dbService;

public:
    MusicInfoService();
    ~MusicInfoService();

    virtual Response<QList<MusicInfo>> GetAll() override;
    virtual Response<MusicInfo> GetOne(int id) override;
    virtual Response<MusicInfo> Update(MusicInfo model) override;
    virtual Response<QString> Delete(int id) override;
    virtual Response<MusicInfo> Add(MusicInfo model) override;
};

#endif // MUSICINFOSERVICE_H
