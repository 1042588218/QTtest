#include "groupchat_interface.h"
#include<QGridLayout>
#include <windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#include<QObject>
#include <QBitmap>
#include <QPainter>
#include<QValidator>
#include<QRegExp>
#include<QRegExpValidator>
#include<QtNetwork/QTcpSocket>
#include<QDateTime>
#include <QFileDialog>
#include<QThread>

groupChat_interface::groupChat_interface(QWidget *parent,QTcpSocket *tcpSocket)
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

    //背景美化按钮
    backgroundBtn=new QPushButton(this);
    backgroundBtn->setFocusPolicy(Qt::NoFocus);
    backgroundBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(212,255,255,255);}\
                QPushButton{background:rgb(245,245,245);border:1px;border-radius:10px;padding:5px 5px;}");
    backgroundBtn->setDisabled(true);
    backgroundBtn->setGeometry(10,70,980,720);


    //聊天主体控件设计
    chatHistory=new QTextBrowser(this);
    //chatHistory->setStyleSheet("QTextBrowser{font-family:'微软雅黑';font-size:25px;color:rgb(55,55,55,200);}");
    connect(chatHistory, SIGNAL(cursorPositionChanged()),this, SLOT(autoScroll()));
    chatMessage=new QTextEdit(this);
    chatMessage->setStyleSheet("QTextEdit{font-family:'微软雅黑';font-size:25px;color:rgb(55,55,55,200);}");
    chatMessage->setFixedSize(960,150);
    groupFriend=new QPushButton("查看群聊天成员",this);
    groupFriend->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    quitGroup=new QPushButton("退出群聊",this);
    quitGroup->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    connect(quitGroup,SIGNAL(clicked()),this,SLOT(on_quitGroup_clicked()));
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


    //聊天主体部分布局设置
    QHBoxLayout* deletlayout=new QHBoxLayout;
    deletlayout->addStretch();
    deletlayout->addWidget(quitGroup);
    QHBoxLayout* filelayout=new QHBoxLayout;
    filelayout->addStretch();
    filelayout->addWidget(groupFriend);
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
    this->hide();


    //群成员信息界面
    management=new QWidget;
    management->setWindowTitle("成员信息");
    management->setFixedSize(400,300);
    QPalette pal2(this->palette());
    pal2.setColor(QPalette::Background,QColor(245,245,245));
    management->setAutoFillBackground(true);
    management->setPalette(pal2);
    management->setWindowFlags(Qt::FramelessWindowHint);
    QBitmap bmp2(management->size());
    bmp2.fill();
    QPainter p2(&bmp2);
    p2.setPen(Qt::NoPen);
    p2.setBrush(Qt::black);
    p2.drawRoundedRect(bmp2.rect(), 10, 10);
    management->setMask(bmp2);
    management->setWindowOpacity(0.98);
    management->close();
    manageCloseBtn=new QPushButton(management);
    manegeTextBrowser=new QTextBrowser(management);
    manegeTextBrowser->setStyleSheet("QTextBrowser{font-family:'微软雅黑';font-size:25px;color:rgb(55,55,55,200);}");
    manegeLineEdit=new QLineEdit(management);
    QFont *editFont=new QFont;
    editFont->setBold(true);
    editFont->setFamily("微软雅黑");
    editFont->setPixelSize(20);
    manegeLineEdit->setPlaceholderText( "请输入账号" );
    manegeLineEdit->setFont(*editFont);
    manegeLineEdit->setMaxLength(12);
    manegeLineEdit->setValidator( new  QIntValidator(manegeLineEdit));
    addBtn=new QPushButton("添加",management);
    deleteBtn=new QPushButton("删除",management);
    addBtn->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:20px;color:rgb(255,255,255,255);}\
            QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
            QPushButton:hover{background-color:rgb(253,114,109)}");
    deleteBtn->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:20px;color:rgb(255,255,255,255);}\
            QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
            QPushButton:hover{background-color:rgb(253,114,109)}");
    connect(addBtn,SIGNAL(clicked()),this,SLOT(on_addBtn_clicked()));
    connect(deleteBtn,SIGNAL(clicked()),this,SLOT(on_deletBtn_clicked()));
    manageCloseBtn->setText("×");
    manageCloseBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:30px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    connect(manageCloseBtn,SIGNAL(clicked()),management,SLOT(close()));
    connect(closeChatBtn,SIGNAL(clicked()),management,SLOT(close()));
    connect(closeBtn,SIGNAL(clicked()),management,SLOT(close()));
    manageCloseBtn->setGeometry(325,0,75,35);
    manageCloseBtn->show();


    //群成员信息布局设置
    QHBoxLayout* manegeBtnlayout=new QHBoxLayout;
    manegeBtnlayout->addWidget(manegeLineEdit);
    manegeBtnlayout->addWidget(addBtn);
    manegeBtnlayout->addWidget(deleteBtn);
    QVBoxLayout* manegelayout=new QVBoxLayout;
    manegelayout->addWidget(manegeTextBrowser);
    manegelayout->addLayout(manegeBtnlayout);
    manegelayout->setContentsMargins(20,50,20,20);
    management->setLayout(manegelayout);
    connect(groupFriend,SIGNAL(clicked()),this,SLOT(on_groupFriend_clicked()));
}


/* 函数名：~groupChat_interface()
 * 功  能：析构函数
 */
groupChat_interface::~groupChat_interface()
{

}


/* 函数名：mouseReleaseEvent(QMouseEvent *event)
 * 函数名：mousePressEvent(QMouseEvent *event)
 * 函数名：mouseMoveEvent(QMouseEvent *event)
 * 功  能：实现鼠标拖动无边框窗口
 */
void groupChat_interface::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void groupChat_interface::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//判断左键是否按下
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

void groupChat_interface::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());//移动当前窗口
}


/* 函数名：minBtn_clicked()
 * 功  能：实现窗口最小化
 */
void groupChat_interface::minBtn_clicked()
{
    if( windowState() != Qt::WindowMinimized ){
        setWindowState( Qt::WindowMinimized );
    }
}


/* 函数名：groupChatMessages(QString groupChatMessage)
 * 功  能：用于处理widget部分传来的与groupChat部分相关的内容
 */
void groupChat_interface::groupChatMessages(QString groupChatMessage)
{
    QString data=groupChatMessage;
    qDebug()<<data;
    QStringList* list=new QStringList(data.split("#"));
    if((*list)[1]=="Jsuccess"){
        QMessageBox::information(this,"信息提示","退出成功!",QMessageBox::Ok);
        this->close();
        return;
    }
    else if((*list)[1]=="Jfail"){
        QMessageBox::information(this,"信息提示","退出失败!",QMessageBox::Ok);
        return;
    }
    if((*list)[0]=="k"||(*list)[0]=="m"||(*list)[0]=="n"){
        if((*list)[1]=="friendExist"){
            QMessageBox::information(this,"信息提示","已存在该成员",QMessageBox::Ok);
            return;
        }
        else if((*list)[1]=="noUser"){
            QMessageBox::information(this,"信息提示","不存在该用户",QMessageBox::Ok);
            return;
        }
        else if((*list)[1]=="success"){
            QMessageBox::information(this,"信息提示","添加成功",QMessageBox::Ok);
            list->removeFirst();
        }
        else if((*list)[1]=="Esuccess"){
            QMessageBox::information(this,"信息提示","删除成功",QMessageBox::Ok);
            list->removeFirst();
        }
        else if((*list)[1]=="Efail"){
            QMessageBox::information(this,"信息提示","删除失败",QMessageBox::Ok);
            return;
        }
        list->removeFirst();
        list->removeLast();
        manegeTextBrowser->clear();
        for(int i=0;i<list->size();i++){
            manegeTextBrowser->append(list->at(i));
        }
        if(list->at(0)==userName){
            addBtn->setEnabled(true);
            deleteBtn->setEnabled(true);
            manegeLineEdit->setEnabled(true);
        }
        else{
            addBtn->setEnabled(false);
            deleteBtn->setEnabled(false);
            manegeLineEdit->setEnabled(false);
        }
        management->setWindowFlags(Qt::Widget);
        management->show();
        manegeLineEdit->clear();
        return;
    }
    if((*list)[0]!="i"){
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


/* 函数名：autoScroll()
 * 功  能：使消息记录框实现自动滚动
 */
void groupChat_interface::autoScroll()
{
    chatHistory->moveCursor(QTextCursor::End);  //将接收文本框的滚动条滑到最下面

}


/* 函数名：on_sendBtn_clicked()
 * 功  能：实现发送消息功能
 */
void groupChat_interface::on_sendBtn_clicked()
{
    if(chatMessage->toPlainText()==""){
        QMessageBox::information(this,"警告","发送信息不可为空!",QMessageBox::Ok);
        return;
    }
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("MM.dd hh:mm:ss");
    QString fs="i";
    QString data=fs+"#"+chatFriendLab->text()+"#"+userName+"#"+current_date+"#"+chatMessage->toPlainText();
    chatMessage->clear();
    tcpSocket->write(data.toUtf8());
}


/* 函数名：on_quitGroup_clicked()
 * 功  能：实现退出群聊功能
 */
void groupChat_interface::on_quitGroup_clicked()
{
    QString js="j";
    QString data=js+"#"+userName+"#"+chatFriendLab->text();
    tcpSocket->write(data.toLatin1());
}


/* 函数名：on_groupFriend_clicked()
 * 功  能：实现查看群信息，若查看者为管理员，则可以对群成员进行删减
 */
void groupChat_interface::on_groupFriend_clicked()
{
    QString ks="k";
    QString data=ks+"#"+chatFriendLab->text();
    tcpSocket->write(data.toLatin1());
}


/* 函数名：on_addBtn_clicked()
 * 功  能：管理员添加群成员
 */
void groupChat_interface::on_addBtn_clicked()
{
    if(manegeLineEdit->text()==""){
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
        return;
    }
    if(manegeLineEdit->text()==userName){
        QMessageBox::information(this,"警告","不可对自己进行操作，若要退出该群聊，请点击聊天界面“退出群聊”按钮",QMessageBox::Ok);
        return;
    }
    QString ms="m";
    QString data=ms+"#"+manegeLineEdit->text()+"#"+chatFriendLab->text();
    tcpSocket->write(data.toLatin1());
}


/* 函数名：on_deletBtn_clicked()
 * 功  能：管理员删除群成员
 */
void groupChat_interface::on_deletBtn_clicked()
{
    if(manegeLineEdit->text()=="")
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    if(manegeLineEdit->text()==userName){
        QMessageBox::information(this,"警告","不可对自己进行操作，若要退出该群聊，请点击聊天界面“退出群聊”按钮",QMessageBox::Ok);
        return;
    }
    QString ns="n";
    QString data=ns+"#"+manegeLineEdit->text()+"#"+chatFriendLab->text();
    qDebug()<<data;
    tcpSocket->write(data.toLatin1());
}
