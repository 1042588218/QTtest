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

void TSserver::init()
{
    this->tcpServer=new QTcpServer(this);
    this->tcpSocket=new QTcpSocket(this);


    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
                     this,SLOT(displayError(QAbstractSocket::SocketError)));
}


void TSserver::receiveData()
{
    QString data=tcpSocket->readAll();
    //qDebug()<<data;
    QStringList list=data.split("#");
    int ret=0;
    if(list[0]=="a")     //注册
        ret=checkSignUp(list[1],list[2]);
    else if(list[0]=="b")  //登录
        ret=checkSignIn(list[1],list[2]);
    else if(list[0]=="c")  //添加好友
        ret=addFriendInf(list[1],list[2]);
    else if(list[0]=="d");  //开始聊天


    QString sendData=list[0];
    if(list[0]=="d"){
        sendData+=+"#"+list[2]+beginChat(list[1],list[2]);
    }
    else if(list[0]=="c"){
        if(ret==-1)
            sendData+="#friendExist";
        else if(ret==-2)
            sendData+="#noUser";
        else if(ret)
            sendData+="#success"+getFriendInf(list[1]);
        else
            sendData+="#fail";
    }
    else if(ret&&list[0]=="b")
        sendData+="#true"+getFriendInf(list[1]);
    else if(ret)
        sendData+="#true";
    else
        sendData+="#false";
    qDebug()<<sendData;
    tcpSocket->write(sendData.toLatin1());
}

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


void TSserver::acceptConnection()
{
    tcpSocket=tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

void TSserver::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();
    tcpSocket->close();
}

bool TSserver::checkSignIn(QString name,QString passward)
{
    MySql *mysql=new MySql();
    bool ret=mysql->loguser(name,passward);
    return ret;
}

bool TSserver::checkSignUp(QString name, QString passward)
{
    MySql *mysql=new MySql();
    bool ret=mysql->signup(name,passward);
    return ret;
}

QString TSserver::getFriendInf(QString name)
{
    MySql *mysql=new MySql();
    return mysql->getFriendInf(name);
}

int TSserver::addFriendInf(QString userId, QString friendId)
{
    MySql *mysql=new MySql();
    int ret=mysql->addFriend(userId,friendId);
    return ret;
}

QString TSserver::beginChat(QString userId, QString friendId)
{
    MySql *mysql=new MySql();
    return mysql->chatWithFriend(userId,friendId);
}
