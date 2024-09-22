#ifndef DataContext_H
#define DataContext_H

#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>


class DataContext
{

private:

    static DataContext * p_instance;
    QSqlDatabase m_DataContext;

protected:
    DataContext(){}
    DataContext(const DataContext& );
    DataContext& operator = (DataContext&);
    ~DataContext();

public:
    static DataContext* getInstance();
    QStringList send_query(QString queryStr, bool is_selection);
    bool connect();
    void disconnect();
};

#endif // DataContext_H
