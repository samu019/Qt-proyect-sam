#ifndef SERVERFUNCTIONS_H
#define SERVERFUNCTIONS_H

#include <QTextStream>

class serverFunctions
{
public:
    serverFunctions();
    void authorization(QString str);
QString answerOnOperation(quint32 operationType, QString text, QString text2);
};

#endif // SERVERFUNCTIONS_H
