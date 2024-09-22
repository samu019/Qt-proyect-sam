#include "databasefunctions.h"
#include <QSqlQuery>
#include <DataContext.h>
#include <qdebug.h>
dataBaseFunctions::dataBaseFunctions()
{

}

void dataBaseFunctions::AddDb()
{
    //QSqlQuery query;

    auto context = DataContext::getInstance();
    //context->send_query("CREATE TABLE user (username VARCHAR(255) NOT NULL,lastName VARCHAR(255),birthDate Date, typeId INT);", false);
    //query.exec();
}

bool dataBaseFunctions::FindUser(QString login, QString password)
{
    auto context = DataContext::getInstance();
    auto result = context->send_query((QString("SELECT CASE WHEN COUNT(*) > 0 THEN 'true' ELSE 'false' END AS user_exists FROM user WHERE username = '%1' AND passwd = '%2';").arg(login).arg(password)), true);
    qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAAAA";
    qDebug() << result[0];
    if (result[0] == "true") return true;
    else {
        return false;
    }

}

 void dataBaseFunctions::AddUser(qint32 id, QString login, QString password)
{
    auto context = DataContext::getInstance();
    context->send_query((QString("INSERT INTO user (username, passwd) VALUES ('%1', '%2');").arg(login).arg(password)), false);
 }

 quint32 dataBaseFunctions::GetUserId()
 {

 }
