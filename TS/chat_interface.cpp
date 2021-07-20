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
#include<QDateTime>

chat_interface::chat_interface(QWidget *parent,QTcpSocket *tcpSocket)
    : QWidget(parent)
{
    this->tcpSocket=tcpSocket;
    userName=new QString;
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
    chatFriendLab=new QLabel;

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
    //chatHistory->setStyleSheet("QTextBrowser{font-family:'微软雅黑';font-size:25px;color:rgb(55,55,55,200);}");
    connect(chatHistory, SIGNAL(cursorPositionChanged()),this, SLOT(autoScroll()));
    chatMessage=new QTextEdit(this);
    chatMessage->setStyleSheet("QTextEdit{font-family:'微软雅黑';font-size:25px;color:rgb(55,55,55,200);}");
    chatMessage->setFixedSize(960,150);
    sendFile=new QPushButton("",this);
    sendFile->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(245,245,245);border:1px;border-radius:10px;padding:10px 10px}");
    deletFriend=new QPushButton("删除好友",this);
    deletFriend->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    connect(deletFriend,SIGNAL(clicked()),this,SLOT(on_deletFriend_clicked()));
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
    connect(sendBtn,SIGNAL(clicked()),this,SLOT(on_sendBtn_clicked()));
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

/* 函数名：chatMessages(QString chatMessage)
 * 功  能：接收并处理widget与chat部分相关的信息
 */
void chat_interface::chatMessages(QString chatMessage)
{
    qDebug()<<chatMessage;
    QString data=chatMessage;
    QStringList* list=new QStringList(data.split("#"));
    if((*list)[1]=="Esuccess"){
        QMessageBox::information(this,"信息提示","删除成功!",QMessageBox::Ok);
        this->close();
        return;
    }
    else if((*list)[1]=="Efail"){
        QMessageBox::information(this,"信息提示","删除失败!",QMessageBox::Ok);
        return;
    }
    if((*list)[0]!="f"){
        *userName=list->at(1);
        delete chatFriendLab;
        chatFriendLab=new QLabel(this);
        chatFriendLab->show();
        chatFriendLab->setText(list->at(2));
        chatFriendLab->setGeometry(0,20,1000,40);
        QFont *labFont=new QFont;
        labFont->setBold(true);
        chatFriendLab->setFont(*labFont);
        chatFriendLab->setStyleSheet("QLabel{font-family:'微软雅黑';font-size:30px;color:rgb(255,255,255,255);}");
        chatFriendLab->setAlignment(Qt::AlignCenter);
        chatFriendLab->setAlignment(Qt::AlignHCenter);
        chatHistory->clear();
    }
    else{
        delete chatFriendLab;
        chatFriendLab=new QLabel(this);
        chatFriendLab->show();
        chatFriendLab->setGeometry(0,20,1000,40);
        QFont *labFont=new QFont;
        labFont->setBold(true);
        chatFriendLab->setFont(*labFont);
        chatFriendLab->setStyleSheet("QLabel{font-family:'微软雅黑';font-size:30px;color:rgb(255,255,255,255);}");
        chatFriendLab->setAlignment(Qt::AlignCenter);
        chatFriendLab->setAlignment(Qt::AlignHCenter);
        chatFriendLab->setText(list->at(1));
    }
    chatHistory->clear();
    if(list->size()>6){
        int i=3;
        while((*list)[i]!="root"){
            chatHistory->append("");
            QString  str;
            if((*list)[i]==userName){
                str= "<font color=\"#f173ac\" size=5>" +(*list)[i]+"    "+(*list)[i+1]+ "</font>";
            }
            else {
                str= "<font color=\"#007947\" size=5>" +(*list)[i]+"    "+(*list)[i+1]+ "</font>";
            }
            chatHistory->append(str);
            str= "<font color=\"#464547\" size=6>" +  (*list)[i+2] + "</font>";
            chatHistory->append(str);
            chatHistory->show();
            i+=3;
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

/* 函数名：on_deletFriend_clicked()
 * 功  能：实现好友的删除功能
 */
void chat_interface::on_deletFriend_clicked()
{
    QString es="e";
    QString data=es+"#"+userName+"#"+chatFriendLab->text();
    tcpSocket->write(data.toLatin1());
}

/* 函数名：on_sendBtn_clicked()
 * 功  能：实现发送消息功能
 */
void chat_interface::on_sendBtn_clicked()
{
    if(chatMessage->toPlainText()==""){
        QMessageBox::information(this,"警告","发送信息不可为空!",QMessageBox::Ok);
        return;
    }
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("MM.dd hh:mm:ss");
    qDebug()<<current_date;
    QString fs="f";
    QString data=fs+"#"+chatFriendLab->text()+"#"+userName+"#"+current_date+"#"+chatMessage->toPlainText();
    qDebug()<<current_date;
    chatMessage->clear();
    tcpSocket->write(data.toUtf8());
}

void chat_interface::autoScroll()
{
    chatHistory->moveCursor(QTextCursor::End);  //将接收文本框的滚动条滑到最下面

}

