#include "tsserver.h"
#include "ui_tsserver.h"
#include "mysql.h"

TSserver::TSserver(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::TSserver)
{
    ui->setupUi(this);
    init();
}

TSserver::~TSserver()
{
    delete ui;
}

/* 函数名：init()
 * 功  能：创建连接
 */
void TSserver::init()
{
    this->tcpServer=new QTcpServer(this);


    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
}

/* 函数名：receiveData()
 * 功  能：从客户端获取信息并调用相关函数
 */
void TSserver::receiveData()
{
    for(int i=0; i<tcpClient.length(); i++)
    {
        //in  out ...
        QString data = tcpClient[i]->readAll();
        if(data.isEmpty())    continue;
        QStringList list=data.split("#");
        qDebug()<<data;
        int ret=0;
        if(list[0]=="a")     //注册
            ret=checkSignUp(list[1],list[2]);
        else if(list[0]=="b")  //登录
            ret=checkSignIn(list[1],list[2]);
        else if(list[0]=="c")  //添加好友
            ret=addFriendInf(list[1],list[2]);
        else if(list[0]=="d")  //开始聊天
        {
        }
        else if(list[0]=="e")
            ret=deletFriend(list[1], list[2]);  //删除好友
        else if(list[0]=="f")
            ret=updateMessages(list[1],list[2],list[3],list[4]);

        QString sendData=list[0];
        if(list[0]=="d"){
            sendData+="#"+list[1]+"#"+list[2]+beginChat(list[1],list[2]);
        }
        else if(list[0]=="f"){
            if(ret){
                sendData+="#"+list[1]+"#"+list[2]+beginChat(list[1],list[2]);
            }
            else{
                sendData+="#fail";
            }
        }
        else if(list[0]=="e"){
            if(ret){
                sendData+="#Esuccess"+getFriendInf(list[1]);
                qDebug()<<getFriendInf(list[1]);
                qDebug()<<sendData;
            }
            else
                sendData+="#Efail";
        }
        else if(list[0]=="c"){
            if(ret==-1)
                sendData+="#friendExist";
            else if(ret==-2)
                sendData+="#noUser";
            else
                sendData+="#success"+getFriendInf(list[1]);
        }
        else if(ret&&list[0]=="b")
            sendData+="#true"+getFriendInf(list[1]);
        else if(ret)
            sendData+="#true";
        else
            sendData+="#false";
        tcpClient[i]->write(sendData.toUtf8());
    }
}

/* 函数名：on_startBtn_clicked()
 * 功  能：开始监听
 */
void TSserver::on_startBtn_clicked()
{
    ui->startBtn->setEnabled(false);
    if(!tcpServer->listen(QHostAddress::Any,8000))
    {
        qDebug()<<tcpServer->errorString();
        close();
        return;
    }
}

/* 函数名：displayError(QAbstractSocket::SocketError)
 * 功  能：打印错误信息
 */
void TSserver::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}

// newConnection -> newConnectionSlot 新连接建立的槽函数
void TSserver::NewConnectionSlot()
{
    //客户端连接  currentClient客户端的套接字
    tcpSocket = tcpServer->nextPendingConnection();

    //把客户端的套接字存放到 之前容器中
    tcpClient.append(tcpSocket);

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
                     this,SLOT(displayError(QAbstractSocket::SocketError)));
}

// disconnected -> disconnectedSlot 客户端断开连接的槽函数
void TSserver::disconnectedSlot()
{
    //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            // 删除存储在tcpClient列表中的客户端信息
             tcpClient[i]->destroyed();
             tcpClient.removeAt(i);
        }
    }
}

/* 函数名：checkSignIn(QString name,QString passward)
 * 功  能：登陆操作
 */
bool TSserver::checkSignIn(QString name,QString passward)
{
    MySql *mysql=new MySql();
    bool ret=mysql->loguser(name,passward);
    return ret;
}

/* 函数名：checkSignUp(QString name, QString passward)
 * 功  能：注册操作
 */
bool TSserver::checkSignUp(QString name, QString passward)
{
    MySql *mysql=new MySql();
    bool ret=mysql->signup(name,passward);
    return ret;
}

/* 函数名：getFriendInf(QString name)
 * 功  能：获取好友信息
 */
QString TSserver::getFriendInf(QString name)
{
    MySql *mysql=new MySql();
    return mysql->getFriendInf(name);
}

/* 函数名：addFriendInf(QString userId, QString friendId)
 * 功  能：添加好友信息
 */
int TSserver::addFriendInf(QString userId, QString friendId)
{
    MySql *mysql=new MySql();
    int ret=mysql->addFriend(userId,friendId);
    return ret;
}

/* 函数名：deletFriend(QString userId, QString friendId)
 * 功  能：删除好友
 */
bool TSserver::deletFriend(QString userId, QString friendId)
{
    MySql *mysql=new MySql();
    bool ret=mysql->delFriend(userId,friendId);
    return ret;
}

/* 函数名：updateMessages(QString reciverId, QString senderId, QString timeInf, QString messageInf)
 * 功  能：更新信息
 */
bool TSserver::updateMessages(QString reciverId, QString senderId, QString timeInf, QString messageInf)
{
    MySql *mysql=new MySql();
    return mysql->updateHistory(reciverId,senderId,timeInf,messageInf);
}

/* 函数名：beginChat(QString userId, QString friendId)
 * 功  能：开始与好友进行对话
 */
QString TSserver::beginChat(QString userId, QString friendId)
{
    MySql *mysql=new MySql();
    return mysql->chatWithFriend(userId,friendId);
}
