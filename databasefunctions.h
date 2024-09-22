#ifndef DATABASEFUNCTIONS_H
#define DATABASEFUNCTIONS_H

#include <QString>

class dataBaseFunctions
{
public:
    dataBaseFunctions();
    void static AddUser(qint32 id, QString login, QString password);
    quint32 GetUserId();
    void static AddDb();
    bool static FindUser(QString login, QString password);
};

#endif // DATABASEFUNCTIONS_H
