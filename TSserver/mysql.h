#ifndef MYSQL_H
#define MYSQL_H

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>

class MySql
{
public:
    MySql();
    void initsql();
    void createtable_UserInf();
    bool loguser(QString name,QString passward);
    bool signup(QString name,QString passward);

private:
    QSqlQuery *queryLogin;
};

#endif // MYSQL_H
