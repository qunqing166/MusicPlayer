#ifndef IMUSICINFOSERVICE_H
#define IMUSICINFOSERVICE_H

#include "IBaseService.h"
#include "../DataInfo/MusicInfo.h"
#include <QObject>

class IMusicInfoService:public IBaseService<MusicInfo>, QObject
{

};

#endif // IMUSICINFOSERVICE_H
