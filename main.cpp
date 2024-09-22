#include <QCoreApplication>
#include "server.h"
#include "DataContext.h"
#include "unittests.h"

DataContext* DataContext::p_instance = 0;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(!DataContext::getInstance()->connect())
    {
        qDebug("ОШИБКА!!!!");
        return -1;
    }
    //запуск сервера


    qDebug("РЕЗУЛЬТАТ ВЫПОЛНЕНИЯ ТЕСТА: ");
    qDebug(Unit_Tests::Test1() ? "Pass" : "Fail");
    Server s;
    return a.exec();
}
