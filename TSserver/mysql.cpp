#include "mysql.h"

MySql::MySql()
{

}

/* 函数名：initsql()
 * 功  能：连接本地数据库
 */
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

/* 函数名：createtable_UserInf()
 * 功  能：建立用户列表
 */
void MySql::createtable_UserInf()
{
    queryLogin=new QSqlQuery;

    queryLogin->exec("create table user(name VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL,passward VARCHAR(30))");

    /*创建root用户*/
    queryLogin->exec("insert into user value('root', 'root')");
}

/* 函数名：loguser(QString name, QString passward)
 * 功  能：验证登录信息是否正确
 */
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

/* 函数名：signup(QString name,QString passward)
 * 功  能：注册账号，并为新账号创建好友列表
 */
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
        queryFriend->exec(("create table "+name+"FriendList(name VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL)"));
        /*创建root好友*/
        queryFriend->exec(("insert into "+name+"FriendList value('root')"));
    }
    return ret;
}

/* 函数名：addFriend(QString userId, QString friendId)
 * 功  能：添加好友
 */
int MySql::addFriend(QString userId, QString friendId)
{
    QString str=QString("select * from "+userId+"FriendList where name='%1'").arg(friendId);
    queryAddFriend=new QSqlQuery;
    queryAddFriend->exec(str);
    queryAddFriend->last();
    int record=queryAddFriend->at()+1;
    if(record!=0)
        return -1;
    QString str1=QString("select * from user where name='%1'").arg(friendId);
    queryLogin=new QSqlQuery;
    queryLogin->exec(str1);
    queryLogin->last();
    int record1=queryLogin->at()+1;
    if(record1==0)
        return -2;
    str=QString("insert into "+userId+"FriendList value('%1')").arg(friendId);
    str1=QString("insert into "+friendId+"FriendList value('%1')").arg(userId);
    bool ret=queryLogin->exec(str);
    if (ret) {
        ret=queryLogin->exec(str1);
        /*创建两者聊天记录数据库*/
        queryFriend=new QSqlQuery;
        if(userId.toInt()>friendId.toInt()){
            queryFriend->exec(("create table "+userId+"to"+friendId+"(chat VARCHAR(30),time VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL,messages VARCHAR(100))"));
            queryFriend->exec(("insert into "+userId+"to"+friendId+" value('root', 'root', 'root')"));
        }
        else{
            queryFriend->exec(("create table "+friendId+"to"+userId+"(chat VARCHAR(30),time VARCHAR(30) PRIMARY KEY UNIQUE NOT NULL,messages VARCHAR(100))"));
            queryFriend->exec(("insert into "+friendId+"to"+userId+" value('root', 'root', 'root')"));
        }
    }

    return ret;
}

/* 函数名：delFriend(QString userId, QString friendId)
 * 功  能：删除好友
 */
bool MySql::delFriend(QString userId, QString friendId)
{
    QString str=QString("delete from "+userId+"FriendList where name='%1'").arg(friendId);
    queryLogin=new QSqlQuery;
    queryLogin->exec(str);
    str=QString("delete from "+friendId+"FriendList where name='%1'").arg(userId);
    queryLogin=new QSqlQuery;
    queryLogin->exec(str);
    if(userId.toInt()>friendId.toInt()){
        str=QString("drop table "+userId+"to"+friendId);
    }
    else {
        str=QString("drop table "+friendId+"to"+userId);
    }
    queryLogin=new QSqlQuery;
    queryLogin->exec(str);
    return 1;
}

/* 函数名：updateHistory(QString reciverId, QString senderId, QString timeInf, QString messageInf)
 * 功  能：更新聊天记录
 */
bool MySql::updateHistory(QString reciverId, QString senderId, QString timeInf, QString messageInf)
{
    queryLogin=new QSqlQuery;
    QString str;
    if(reciverId.toInt()>senderId.toInt()){
        str=QString("insert into "+reciverId+"to"+senderId+" value('%1','%2','%3')").arg(senderId).arg(timeInf).arg(messageInf);
    }
    else {
        str=QString("insert into "+senderId+"to"+reciverId+" value('%1','%2','%3')").arg(senderId).arg(timeInf).arg(messageInf);
    }
    bool ret=queryLogin->exec(str);
    return ret;
}

/* 函数名：chatWithFriend(QString userId, QString friendId)
 * 功  能：与朋友开始聊天，返回聊天历史记录
 */
QString MySql::chatWithFriend(QString userId, QString friendId)
{
    QString FriendInf="";
    QString str;
    if(userId.toInt()>friendId.toInt()){
        str=QString("SELECT * FROM "+userId+"to"+friendId);
    }
    else {
        str=QString("SELECT * FROM "+friendId+"to"+userId);
    }
        queryLogin=new QSqlQuery(str);
    while (queryLogin->next()) //依次取出查询结果的每一条记录，直至结束
    {
        FriendInf=FriendInf+"#"+queryLogin->value(0).toString()+"#"+queryLogin->value(1).toString()+"#"+queryLogin->value(2).toString();
    }
    return FriendInf;
}

/* 函数名：getFriendInf(QString name)
 * 功  能：获取当前登录帐号好友信息
 */
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
