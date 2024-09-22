#include <DataContext.h>
#include <QCoreApplication>


    DataContext::~DataContext() {
        if (m_DataContext.isOpen())
            disconnect();
        if (p_instance)
            delete p_instance;
    }
    DataContext* DataContext::getInstance()
    {
        if (!p_instance)
        {
            p_instance = new DataContext();
        }
        return p_instance;
    }

    QStringList DataContext::send_query(QString queryStr, bool is_selection)
    {
        QSqlQuery query;
        QStringList list;
        query.prepare(queryStr);
        if (!query.exec()){
            qDebug() << "Invalid query:" << query.lastError().text();
            list.append("!0!");

            return list;
        }
        if (!is_selection){
            list.append("!1!");

            return list;
        }

        while (query.next())
            list.append(query.value(0).toString());
        return list;
    }

    bool DataContext::connect()
    {
        m_DataContext = QSqlDatabase::addDatabase("QSQLITE");
        m_DataContext.setDatabaseName("C:/Music/projectTDb.db");
        if (!m_DataContext.open())
        {
            qDebug() << "Ошибка соединения с базой данных";
            return false;
        }

        return true;
    }

    void DataContext::disconnect()
    {
        // Отключаемся от базы данных
        m_DataContext.close();
    }
