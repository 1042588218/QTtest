#include "widget.h"
#include<QObject>

#define ip "192.168.136.1"
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

    groupPart=new groupChat_interface(nullptr,tcpSocket);

    connect(this,SIGNAL(sendToLogin(QString)),loginPart,SLOT(loginMessages(QString)));
    connect(this,SIGNAL(sendToMain(QString)),mainPart,SLOT(mainMessages(QString)));
    connect(this,SIGNAL(sendToChat(QString)),chatPart,SLOT(chatMessages(QString)));
    connect(this,SIGNAL(sendToGroupChat(QString)),groupPart,SLOT(groupChatMessages(QString)));

    connect(mainPart->closeBtn,SIGNAL(clicked()),chatPart,SLOT(close()));
    connect(mainPart->closeBtn,SIGNAL(clicked()),groupPart,SLOT(close()));

    connect(loginPart,SIGNAL(loginSuccess()),mainPart,SLOT(setFriendBtn()));

    connect(loginPart,SIGNAL(loginSuccess()),mainPart,SLOT(show()));

    connect(loginPart,SIGNAL(loginUser(QString,QString)),mainPart,SLOT(reciveUsername(QString,QString)));
}


/* 函数名：~Widget()
 * 功  能：析构函数
 */
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
    else if(list[0]=="f"||list[0]=="FileSendSuccessf"||list[0]=="FileSendFailf"||list[0]=="FileSend"||list[0]=="FileSendSuccess"||list[0]=="FileSendFail"){
        emit(sendToChat(data));
    }
    else if(list[0]=="g"){
        emit(sendToMain(data));
    }
    else if(list[0]=="h"||list[0]=="i"||list[0]=="k"||list[0]=="m"||list[0]=="n"){
        emit(sendToGroupChat(data));
    }
    else if(list[0]=="j"){
        emit(sendToMain(data));
        emit(sendToGroupChat(data));
    }
    else
        return;
}
