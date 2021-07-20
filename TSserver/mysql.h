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

    //数据库相关操作函数
    void createtable_UserInf();
    bool loguser(QString name,QString passward);
    bool signup(QString name,QString passward);
    int addFriend(QString userId,QString friendId);
    bool delFriend(QString userId,QString friendId);
    bool updateHistory(QString reciverId,QString senderId,QString timeInf,QString messageInf);
    bool updateGroupHistory(QString reciverId,QString senderId,QString timeInf,QString messageInf);
    bool setGroup(QString user,QString groupNmae);
    QString chatWithFriend(QString userId,QString friendId);
    QString getFriendInf(QString name);
    QString chatWithGroup(QString userId,QString friendId);

private:
    QSqlQuery *queryLogin;
    QSqlQuery *queryFriend;
    QSqlQuery *queryAddFriend;
};

#endif // MYSQL_H
