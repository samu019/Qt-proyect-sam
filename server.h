#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>


class Server : public QTcpServer
{
//Сигнально-слотовые связи
    Q_OBJECT

public:
    Server();
    QTcpSocket *socket;

private:
    //вектор с сокетами подключения
    QVector <QTcpSocket*> Sockets;
//данные, передающиеся между сервером и клиентом
    QByteArray Data;
    void SendToClient(QString str);
//размер блока данных
   quint16 nextBlockSize;


//работа с БД
   QSqlDatabase db;
   QSqlQuery *sqlQuery;


public slots:
    //Обработчик новых подключений
    void incomingConnection(qintptr socketDescriptor);
    //Обработчик полученных от клиента сообщений
    void slotReadyRead();

};

#endif // SERVER_H
