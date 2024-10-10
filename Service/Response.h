#ifndef RESPONSE_H
#define RESPONSE_H

#include <QString>

// namespace{
// class Response;
// }

// class Response
// {
//     bool status;
//     QString message;
// public:
//     Response(QString message, bool status = false)
//     {
//         this->message = message;
//         this->status = status;
//     }

//     bool Status(){return this->status;}
//     QString Message(){return this->message;}
// };

template<class T>
class Response
{
    bool status;
    QString message;
    T result;
public:
    Response(bool status, T result)
    {
        this->status = status;
        this->result = result;
    }
    Response(QString message, bool status = false)
    {
        this->message = message;
        this->status = status;
    }

    bool Status(){return this->status;}
    QString Message(){return this->message;}
    T Result(){return this->result;}
};

#endif // RESPONSE_H
