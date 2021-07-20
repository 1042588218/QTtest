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



/* 函数名：~TSserver()
 * 功  能：析构函数
 */
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
        else if(list[0]=="e")  //删除好友
            ret=deletFriend(list[1], list[2]);
        else if(list[0]=="f")  //发送消息
            ret=updateMessages(list[1],list[2],list[3],list[4]);
        else if(list[0]=="g")  //创建群聊
            ret=setGroup(list[1],list[2]);
        else if(list[0]=="h")  //开始群聊
        {}
        else if(list[0]=="i")  //发送群聊消息
            ret=updateGroupMessages(list[1],list[2],list[3],list[4]);
        else if(list[0]=="j")  //退出群聊
            ret=deletFriend(list[1], list[2]);
        else if(list[0]=="k")  //获取群聊成员信息
        {}
        else if(list[0]=="m")  //添加群聊成员
        {
            ret=addFriendInf(list[2],list[1]);
        }
        else if(list[0]=="n")  //删除群聊成员
        {
            ret=deletFriend(list[1],list[2]);
        }

        QString sendData=list[0];
        if(list[0]=="d"){
            sendData+="#"+list[1]+"#"+list[2]+beginChat(list[1],list[2]);
        }
        else if(list[0]=="h"){
            sendData+="#"+list[1]+"#"+list[2]+beginChatGroup(list[1],list[2]);
        }
        else if(list[0]=="g"){
            if(ret){
                sendData+="#Gsuccess"+getFriendInf(list[1]);
            }
            else {
                sendData+="#Gfail";
            }
        }
        else if(list[0]=="m"){
            if(ret==-1)
                sendData+="#friendExist";
            else if(ret==-2)
                sendData+="#noUser";
            else{
                sendData+="#success"+getFriendInf(list[2]);
                QString tmp="c"+("#success"+getFriendInf(list[1]));
                if(map.contains(list[1]))
                    map.value(list[1])->write(tmp.toUtf8());
            }
        }
        else if(list[0]=="n"){
            if(ret){
                sendData+="#Esuccess"+getFriendInf(list[2]);
                QString tmp="e#"+("Esuccess"+getFriendInf(list[1]));
                if(map.contains(list[1]))
                    map.value(list[1])->write(tmp.toUtf8());
            }
            else
                sendData+="#Efail";
        }
        else if(list[0]=="k"){
            sendData="k"+getFriendInf(list[1]);
        }
        else if(list[0]=="FileSend"){
            if(map.contains(list[2])){
                sendData="FileSendSuccess";
                map.value(list[1])->write(sendData.toUtf8());
                map.value(list[2])->write(data.toUtf8());
                return;
            }
            else{
                sendData="FileSendFail";
                map.value(list[1])->write(sendData.toUtf8());
                qDebug()<<sendData;
                return;
            }
        }
        else if(list[0]=="f"){
            if(ret){
                sendData+="#"+list[1]+"#"+list[2]+beginChat(list[1],list[2]);
                QString tmp="f"+("#"+list[2]+"#"+list[1]+beginChat(list[2],list[1]));
                if(map.contains(list[1]))
                    map.value(list[1])->write(tmp.toUtf8());
            }
            else{
                sendData+="#fail";
            }
        }
        else if(list[0]=="i"){
            if(ret){
                //sendData+="#"+list[1]+"#"+list[2]+beginChat(list[2],list[1]);
                QString tmp=getFriendInf(list[1]);
                QStringList groupers=tmp.split("#");
                int i=0;
                while(groupers[i]!="root"){
                    if(map.contains(groupers[i])){
                        sendData="i#"+list[1]+"#"+groupers[i]+beginChatGroup(groupers[i],list[1]);
                        map.value(groupers[i])->write(sendData.toUtf8());
                    }
                    i++;
                }
                return;
            }
            else{
                sendData+="#fail";
            }
        }
        else if(list[0]=="e"){
            if(ret){
                sendData+="#Esuccess"+getFriendInf(list[1]);
                QString tmp="e#"+("Esuccess"+getFriendInf(list[2]));
                if(map.contains(list[2]))
                    map.value(list[2])->write(tmp.toUtf8());
            }
            else
                sendData+="#Efail";
        }
        else if(list[0]=="j"){
            if(ret){
                sendData+="#Jsuccess"+getFriendInf(list[1]);
            }
            else
                sendData+="#Efail";
        }
        else if(list[0]=="c"){
            if(ret==-1)
                sendData+="#friendExist";
            else if(ret==-2)
                sendData+="#noUser";
            else{
                sendData+="#success"+getFriendInf(list[1]);
                QString tmp="c"+("#success"+getFriendInf(list[2]));
                if(map.contains(list[2]))
                    map.value(list[2])->write(tmp.toUtf8());
            }
        }
        else if(ret&&list[0]=="b"){
            sendData+="#true"+getFriendInf(list[1]);
                map.insert(list[1],tcpClient[i]);
        }
        else if(ret)
            sendData+="#true";
        else
            sendData+="#false";
        qDebug()<<sendData;
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


/* 函数名：NewConnectionSlot()
 * 功  能：建立新连接
 */
void TSserver::NewConnectionSlot()
{
    //客户端连接  currentClient客户端的套接字
    tcpSocket = tcpServer->nextPendingConnection();
    tcpClient.append(tcpSocket);

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
                     this,SLOT(displayError(QAbstractSocket::SocketError)));
}


/* 函数名：disconnectedSlot()
 * 功  能：断开一个链接
 */
void TSserver::disconnectedSlot()
{
    //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            QString tmp=map.key(tcpClient[i]);
            map.remove(tmp);
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


/* 函数名：updateGroupMessages(QString reciverId, QString senderId, QString timeInf, QString messageInf)
 * 功  能：更新群聊信息
 */
bool TSserver::updateGroupMessages(QString reciverId, QString senderId, QString timeInf, QString messageInf)
{
    MySql *mysql=new MySql();
    return mysql->updateGroupHistory(reciverId,senderId,timeInf,messageInf);
}


/* 函数名：setGroup(QString setUser, QString groupName)
 * 功  能：建立群聊
 */
bool TSserver::setGroup(QString setUser, QString groupName)
{
    MySql *mysql=new MySql();
    return mysql->setGroup(setUser,groupName);
}


/* 函数名：beginChatGroup(QString userId, QString friendId)
 * 功  能：开始群聊
 */
QString TSserver::beginChatGroup(QString userId, QString friendId)
{
    MySql *mysql=new MySql();
    return mysql->chatWithGroup(userId,friendId);
}


/* 函数名：beginChat(QString userId, QString friendId)
 * 功  能：开始与好友进行对话
 */
QString TSserver::beginChat(QString userId, QString friendId)
{
    MySql *mysql=new MySql();
    return mysql->chatWithFriend(userId,friendId);
}
