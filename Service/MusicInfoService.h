// #ifndef MUSICINFOSERVICE_H
// #define MUSICINFOSERVICE_H

// // #include "IBaseService.h"
// #include "../DataInfo/MusicInfo.h"
// #include "DataBaseService.h"
// // #include "IMusicInfoService.h"
// #include "Response.h"

// enum QueryParameterMusic
// {
//     MusicName,
//     PlayList
// };

// class MusicInfoService//:public IBaseService<MusicInfo>
// {
//     DataBaseService<MusicInfo> *dbService;

// public:
//     MusicInfoService();
//     ~MusicInfoService();

//     Response<QList<MusicInfo>> GetAll();
//     Response<QList<MusicInfo>> GetAll(QString musicName, QueryParameterMusic type);
//     Response<QList<MusicInfo>> GetAll(int idStart, int idEnd);
//     Response<MusicInfo> GetOne(int id);
//     Response<MusicInfo> Update(MusicInfo model);
//     Response<QString> Delete(int id);
//     Response<MusicInfo> Add(MusicInfo model);
// };

// #endif // MUSICINFOSERVICE_H
