#include "chat_interface.h"
#include<QGridLayout>
#include <windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include<QValidator>
#include<QRegExp>
#include<QRegExpValidator>
#include<QtNetwork/QTcpSocket>

chat_interface::chat_interface(QWidget *parent,QTcpSocket *tcpSocket)
    : QWidget(parent)
{
    this->tcpSocket=tcpSocket;
    //基本窗口设置
    this->setWindowTitle("聊天界面");
    setFixedSize(1000,800);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background,QColor(236,65,65));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    setWindowFlags(Qt::FramelessWindowHint);
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 10, 10);
    setMask(bmp);
    setWindowOpacity(0.98);
    this->close();
    chatPic=new QLabel(this);
    QPixmap pic(":/new/prefix1/src/chat.png");
    chatPic->setPixmap(pic.scaled(100,100));
    chatPic->setGeometry(5,5,100,100);

    //关闭最小化按钮设置，按钮功能实现
    closeBtn=new QPushButton(this);
    closeBtn->setText("×");
    closeBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:30px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
                minBtn=new QPushButton(this);
            minBtn->setText("-");
    minBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:35px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
            connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));
            connect(minBtn,SIGNAL(clicked()),this,SLOT(minBtn_clicked()));
    closeBtn->setGeometry(925,0,75,35);
    closeBtn->show();
    minBtn->setGeometry(840,0,75,35);
    minBtn->show();

    backgroundBtn=new QPushButton(this);
    backgroundBtn->setFocusPolicy(Qt::NoFocus);
    backgroundBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(212,255,255,255);}\
                QPushButton{background:rgb(245,245,245);border:1px;border-radius:10px;padding:5px 5px;}");
    backgroundBtn->setDisabled(true);
    backgroundBtn->setGeometry(10,70,980,720);

    chatHistory=new QTextBrowser(this);
    chatMessage=new QTextEdit(this);
    chatMessage->setFixedSize(960,150);
    sendFile=new QPushButton("发送文件",this);
    sendFile->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    deletFriend=new QPushButton("删除好友",this);
    deletFriend->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    closeChatBtn=new QPushButton("关闭",this);
    connect(closeChatBtn,SIGNAL(clicked()),this,SLOT(close()));
    closeChatBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    sendBtn=new QPushButton("发送",this);
    sendBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    QHBoxLayout* deletlayout=new QHBoxLayout;
    deletlayout->addStretch();
    deletlayout->addWidget(deletFriend);
    QHBoxLayout* filelayout=new QHBoxLayout;
    filelayout->addStretch();
    filelayout->addWidget(sendFile);
    QHBoxLayout* bottomlayout=new QHBoxLayout;
    bottomlayout->addStretch();
    bottomlayout->addWidget(closeChatBtn);
    bottomlayout->addWidget(sendBtn);
    QVBoxLayout* mainlayout=new QVBoxLayout;
    mainlayout->addLayout(deletlayout);
    mainlayout->addWidget(chatHistory);
    mainlayout->addLayout(filelayout);
    mainlayout->addWidget(chatMessage);
    mainlayout->addLayout(bottomlayout);
    mainlayout->setContentsMargins(20,80,20,20);
    setLayout(mainlayout);
}

chat_interface::~chat_interface()
{

}

void chat_interface::chatMessages(QString chatMessage)
{
    qDebug()<<chatMessage;
    QString data=chatMessage;
    QStringList* list=new QStringList(data.split("#"));
    chatFriendLab=new QLabel(this);
    chatFriendLab->setText(list->at(1));
    chatFriendLab->setGeometry(0,20,1000,40);
    QFont *labFont=new QFont;
    labFont->setBold(true);
    chatFriendLab->setFont(*labFont);
    chatFriendLab->setStyleSheet("QLabel{font-family:'微软雅黑';font-size:30px;color:rgb(255,255,255,255);}");
    chatFriendLab->setAlignment(Qt::AlignCenter);
    chatFriendLab->setAlignment(Qt::AlignHCenter);
    if(list->size()<=5){

    }
    else {
        int i=2;
        while(i<list->size()-3){

        }
    }
    this->show();
}

/* 函数名：mouseReleaseEvent(QMouseEvent *event)
 * 函数名：mousePressEvent(QMouseEvent *event)
 * 函数名：mouseMoveEvent(QMouseEvent *event)
 * 功  能：实现鼠标拖动无边框窗口
 */
void chat_interface::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void chat_interface::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//判断左键是否按下
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

void chat_interface::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());//移动当前窗口
}

/* 函数名：minBtn_clicked()
 * 功  能：实现窗口最小化
 */
void chat_interface::minBtn_clicked()
{
    if( windowState() != Qt::WindowMinimized ){
        setWindowState( Qt::WindowMinimized );
    }
}
