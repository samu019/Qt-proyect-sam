#include "server.h"
#include "sha256.h"
#include <string>
#include "serverfunctions.h"
#include "DataContext.h"


Server::Server()
{
    //Запуск сервера, QHostAddress::Any - принимает запросы с любого адреса по порту 7777
    if(this->listen(QHostAddress::Any, 7777))
    {
        qDebug() << "Server is started!";
    }
    else
    {
        qDebug() << "Error! Server isn't started.";
    }
    nextBlockSize = 0;

    DataContext::getInstance();
}

void Server::incomingConnection(qintptr socketDescripter)
{
    socket = new QTcpSocket;
    //дексриптор - неотрицательное число, идентифицирующее поток ввода-вывода
    socket->setSocketDescriptor(socketDescripter);
    //сигнальные соедниения
    //соединение readyRead со слотом
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    //удаеление слота, по возможности, после отключения
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
    //функция, вызывающаяся при каждом новом подключении, создает сокет и добавляет в вектор
    Sockets.push_back(socket);

    //вывод дескриптора нового сокета
    qDebug() << "client connected" << socketDescripter;
}

//слот для чтения сообщений
void Server::slotReadyRead()
{
    //сокет, с которого пришёл запрос
    socket = (QTcpSocket*)sender();

    //потоковый ввод-вывод
    //с помощью объекта in работаем с данными, находящимися в сокете
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_9);

    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "read...";

        for(;;)
        {
             //считываем размер блока
            if(nextBlockSize == 0)
            {
                qDebug() << "nextBlockSize = 0";
                if(socket->bytesAvailable() < 2)
                {
                    qDebug() << "Data < 2, break";
                    break;
                }
                //считываем размер блока
                in >> nextBlockSize;
                 qDebug() << "nextBlockSize = " << nextBlockSize;
            }
            //сравниваем размер блока с кол-вом байт, пришедшим с сервера
            if(socket->bytesAvailable() < nextBlockSize)
            {
                 qDebug() << "Data not full, break";
                //данные пришли не полностью
                break;
            }
            //Типы из потока передаваемых значений
            QString login, password;
            quint32 operationNumber;
            in >> operationNumber >> login >> password;
            //обнуляем размер блока, чтобы принимать новые сообщения
            nextBlockSize = 0;
            qDebug() << operationNumber;
            auto sf = new serverFunctions;
            auto result = sf->answerOnOperation(operationNumber, login, password);
SendToClient(result);
                    /*
            if(operationNumber == 1)
            {
                auto p = new SHA256;
                auto test = QString::fromStdString(p->hashString(password.toStdString()));
                SendToClient("Добавление " + login + " " + test);
            }
            else
            {
                SendToClient("Проверить");
            }
            break;*/



        }
    }
    else
    {
        qDebug() << "DataStream error";
    }
}


//метод отправки сообщений клиенту (str) - сообщение, которое нужно отправить
void Server::SendToClient(QString str)
{
    //подготовка сообщения к отправке
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << str;
    out.device()->seek(0);
    //размер сообщения = длина блока - выделенные для размера байты
    out << quint16(Data.size() - sizeof(quint16));

    //отправка одному сокету
    socket->write(Data);

/*
    //отправка всем сокетам
    for(int i = 0; i < Sockets.size(); i++)
    {
        //запись сообщения в каждый сокет вектора
        Sockets[i]->write(Data);
    }
    */
}
