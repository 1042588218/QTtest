#include "mysql.h"

MySql::MySql()
{

}

void MySql::initsql()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("589926");
    db.setDatabaseName("User");
    if(db.open())
        {
            qDebug()<<"Database connected successfully!";
            createtable_UserInf();
            return;
        }
    else
        {
            qDebug()<<"Database connected failed!";
            return;
        }
}

void MySql::createtable_UserInf()
{
    queryLogin=new QSqlQuery;

    queryLogin->exec("create table user(name VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL,passward VARCHAR(30))");

    /*创建root用户*/
    queryLogin->exec("insert into user value('root', 'root')");
}


bool MySql::loguser(QString name, QString passward)
{
    QString str=QString("select * from user where name='%1' and passward='%2'").arg(name).arg(passward);
    queryLogin=new QSqlQuery;
    queryLogin->exec(str);
    queryLogin->last();
    int record=queryLogin->at()+1;
    if(record==0)
        return false;
    return true;
}


bool MySql::signup(QString name,QString passward)
{
    QString str=QString("select * from user where name='%1").arg(name);
    queryLogin=new QSqlQuery;
    queryLogin->exec(str);
    queryLogin->last();
    int record=queryLogin->at()+1;
    if(record!=0)
        return false;
    str=QString("insert into user value('%1','%2')").arg(name).arg(passward);
    bool ret=queryLogin->exec(str);
    if(ret){
        qDebug()<<"为账号"+name+"创建好友列表";
        queryFriend=new QSqlQuery;
        queryFriend->exec(("create table "+name+"FriendList(name VARCHAR(30))"));
        /*创建root好友*/
        queryFriend->exec(("insert into "+name+"FriendList value('root')"));
    }
    return ret;
}

QString MySql::getFriendInf(QString name)
{
    QString FriendInf="";
    QString str=QString("SELECT * FROM "+name+"FriendList");
    queryLogin=new QSqlQuery(str);
    while (queryLogin->next()) //依次取出查询结果的每一条记录，直至结束
        {
               FriendInf=FriendInf+"#"+queryLogin->value(0).toString();
        }
    return FriendInf;
}
