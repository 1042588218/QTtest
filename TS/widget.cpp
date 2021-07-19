#include "widget.h"
#include<QObject>

#define ip "192.168.31.140"
#define port 8000

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
        tcpSocket=new QTcpSocket(this);
    init();
    connectServer();

    loginPart=new login_interface(nullptr,tcpSocket);

    mainPart=new main_interface(nullptr,tcpSocket);

    chatPart=new chat_interface(nullptr,tcpSocket);

    connect(this,SIGNAL(sendToLogin(QString)),loginPart,SLOT(loginMessages(QString)));
    connect(this,SIGNAL(sendToMain(QString)),mainPart,SLOT(mainMessages(QString)));
    connect(this,SIGNAL(sendToChat(QString)),chatPart,SLOT(chatMessages(QString)));

    connect(mainPart->closeBtn,SIGNAL(clicked()),chatPart,SLOT(close()));
    connect(mainPart->exitBtn,SIGNAL(clicked()),chatPart,SLOT(close()));

    connect(loginPart,SIGNAL(loginSuccess()),mainPart,SLOT(setFriendBtn()));

    connect(loginPart,SIGNAL(loginSuccess()),mainPart,SLOT(show()));

    connect(loginPart,SIGNAL(loginUser(QString,QString)),mainPart,SLOT(reciveUsername(QString,QString)));
}

Widget::~Widget()
{

}

/* 函数名：init()
 * 功  能：报错
 */
void Widget::init()
{
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数
}

/* 函数名：connectServer()
 * 功  能：连接到服务器
 */
void Widget::connectServer()
{
    tcpSocket->abort();   //取消已有的连接
    tcpSocket->connectToHost(ip,port);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));
}

/* 函数名：displayError(QAbstractSocket::SocketError)
 * 功  能：打印错误信息
 */
void Widget::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<tcpSocket->errorString();   //输出出错信息
}

/* 函数名：readMessages()
 * 功  能：获取服务器返回的信息
 */
void Widget::readMessages()
{
    QString data=tcpSocket->readAll();
    //qDebug()<<data;
    QStringList list=data.split("#");
    if(list[0]=="a" ||list[0]=="b")
        emit(sendToLogin(data));
    else if (list[0]=="c") {
        emit(sendToMain(data));
    }
    else if(list[0]=="d"){
        emit(sendToChat(data));
    }
    else if(list[0]=="e"){
        emit(sendToMain(data));
        emit(sendToChat(data));
    }
    else if(list[0]=="f"){
        emit(sendToChat(data));
    }
    else
        return;
}
