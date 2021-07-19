#include "main_interface.h"
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
#include<QHBoxLayout>
#include<QVBoxLayout>

main_interface::main_interface(QWidget *parent,QTcpSocket *tcpSocket)
    : QWidget(parent)
{
    this->tcpSocket=tcpSocket;

        // 追踪鼠标
        this->setMouseTracking(true);

    //基本窗口设置
    this->setWindowTitle("主界面");
    setFixedWidth(400);
    setMinimumHeight(380);
    setMaximumHeight(900);
    resize(400,900);
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
    move(1500,50);
    this->close();
    friendlayout=new QVBoxLayout;
    myMapper = new QSignalMapper(this);

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
    closeBtn->setGeometry(325,0,75,35);
    closeBtn->show();
    minBtn->setGeometry(240,0,75,35);
    minBtn->show();

    userInf=new QString();
    userName=new QString();
    helloWord=new QLabel(this);
    helloWord->setGeometry(20,0,140,70);
    helloWord->setAlignment(Qt::AlignCenter);
    QPixmap pic(":/new/prefix1/src/welcome.png");
    helloWord->setPixmap(pic.scaled(140,70));
    helloWord->show();

    QPushButton *Line=new QPushButton("",this);
    Line->setFocusPolicy(Qt::NoFocus);
    Line->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(212,255,255,255);}\
                QPushButton{background:rgb(245,245,245);border:1px;border-radius:10px;padding:5px 5px;}");
    Line->setDisabled(true);
    Line->setGeometry(0,60,400,840);
    QPushButton* btnPart=new QPushButton("",this);
    btnPart->setFocusPolicy(Qt::NoFocus);
    btnPart->setDisabled(true);
    btnPart->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(212,255,255,255);}\
                QPushButton{background:rgb(43,43,43);border:1px;border-radius:10px;padding:5px 5px;}");
    btnPart->setGeometry(0,this->height()-80,400,80);

    searchLine=new QLineEdit(this);
    QFont *editFont=new QFont;
    editFont->setBold(true);
    editFont->setFamily("微软雅黑");
    editFont->setPixelSize(18);
    searchLine->setPlaceholderText( "请输入好友账号" );
    searchLine->setFont(*editFont);
    searchLine->setMaxLength(15);
    searchLine->setValidator( new  QIntValidator(searchLine));
    searchBtn=new QPushButton("搜索好友",this);
    searchBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:18px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:5px 5px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    connect(searchBtn,SIGNAL(clicked()),this,SLOT(on_searchBtn_clicked()));

    friendList=new QWidget(this);
    searchResult=new QWidget;
    searchResult->setFixedSize(400,100);
    searchResultBtn=new QPushButton(searchResult);

    addFriendPatr=new QWidget;
    addBtn=new QPushButton("添加好友",this);
    addBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:20px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    connect(addBtn,SIGNAL(clicked()),addFriendPatr,SLOT(show()));
    closeAddBtn=new QPushButton(addFriendPatr);
    addFriendPatr->setWindowTitle("添加好友");
    addFriendPatr->setFixedSize(400,150);
    QPalette pal1(addFriendPatr->palette());
    pal1.setColor(QPalette::Background,QColor(245,245,245));
    addFriendPatr->setAutoFillBackground(true);
    addFriendPatr->setPalette(pal1);
    addFriendPatr->setWindowFlags(Qt::FramelessWindowHint);
    QBitmap bmp1(addFriendPatr->size());
    bmp1.fill();
    QPainter p1(&bmp1);
    p1.setPen(Qt::NoPen);
    p1.setBrush(Qt::black);
    p1.drawRoundedRect(bmp1.rect(), 10, 10);
    addFriendPatr->setMask(bmp1);
    addFriendPatr->setWindowOpacity(0.98);
    addFriendPatr->close();
    closeAddBtn->setText("×");
    closeAddBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:30px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
            connect(closeAddBtn,SIGNAL(clicked()),addFriendPatr,SLOT(close()));
    closeAddBtn->setGeometry(325,0,75,35);
    closeAddBtn->show();
    addLine=new QLineEdit(addFriendPatr);
    addFriendBtn=new QPushButton(addFriendPatr);
    QFont *addFont=new QFont;
    addFont->setBold(true);
    addFont->setFamily("微软雅黑");
    addFont->setPixelSize(20);
    addLine->setPlaceholderText( "请输入账号" );
    addLine->setFont(*addFont);
    addLine->setMaxLength(12);
    addLine->setValidator( new  QIntValidator(addLine));
    addFriendBtn->setText("添加好友");
    addFriendBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:20px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    connect(addFriendBtn,SIGNAL(clicked()),this,SLOT(on_addFriendBtn_clicked()));
    QVBoxLayout *addlayout=new QVBoxLayout();
    QHBoxLayout *addFriendBtnlayout=new QHBoxLayout();
    addlayout->addWidget(addLine);
    addFriendBtnlayout->addWidget(addFriendBtn);
    addlayout->addLayout(addFriendBtnlayout);
    addlayout->setContentsMargins(40,40,50,20);
    addFriendPatr->setLayout(addlayout);
    connect(closeBtn,SIGNAL(clicked()),addFriendPatr,SLOT(close()));

    exitBtn=new QPushButton("退出程序",this);
    connect(exitBtn,SIGNAL(clicked()),this,SLOT(close()));
    exitBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:20px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
    QHBoxLayout *searchLayout=new QHBoxLayout;
    searchLayout->addWidget(searchLine);
    searchLayout->addWidget(searchBtn);
    QHBoxLayout *bottomLayout=new QHBoxLayout;
    bottomLayout->addWidget(addBtn);
    bottomLayout->addWidget(exitBtn);
    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(friendList);
    mainLayout->addLayout(bottomLayout);
    mainLayout->setContentsMargins(20,80,20,20);
    friendList->setLayout(friendlayout);
    setLayout(mainLayout);

}

main_interface::~main_interface()
{

}

/* 函数名：reciveUsername(QString userInf,QString userName)
 * 功  能：得到登录账号的好友信息
 */
void main_interface::reciveUsername(QString userInf,QString userName)
{
    *(this->userName)=userName;
    *(this->userInf)=userInf;
    QStringList list=userInf.split("#");
    list.removeFirst();
    list.removeFirst();
    list.removeLast();
    friendInf=new QStringList;
    *friendInf=list;
    //qDebug()<<*friendInf<<friendInf->size();
    //qDebug()<<*(this->userName)<<"登录";
}

/* 函数名：mouseReleaseEvent(QMouseEvent *event)
 * 函数名：mousePressEvent(QMouseEvent *event)
 * 函数名：mouseMoveEvent(QMouseEvent *event)
 * 功  能：实现鼠标拖动无边框窗口
 */
void main_interface::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void main_interface::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//判断左键是否按下
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

void main_interface::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());//移动当前窗口
}

/* 函数名：on_searchBtn_clicked()
 * 功  能：完成好友的搜索功能
 */
void main_interface::on_searchBtn_clicked()
{
    if(searchLine->text()==""){
        QMessageBox::information(this,"信息提示","搜索栏不可为空！",QMessageBox::Ok);
        return;
    }
    for(int i=0;i<friendBtnList.size();i++){
        if(friendBtnList.at(i)->text()==searchLine->text()){
            searchResultBtn->setText(friendBtnList.at(i)->text());
            searchResultBtn->setIcon(QIcon(":/new/prefix1/src/Friend.png"));
            searchResultBtn->setIconSize(QSize(50, 50));
            searchResultBtn->setStyleSheet(
                        "QPushButton{font-family:'微软雅黑';font-size:30px;color:rgb(255,255,255,255);}\
                        QPushButton{background:rgb(236,65,65);border:1px;padding:10px 10px}\
                        QPushButton:hover{background-color:rgb(253,114,109)}");
            searchResultBtn->setGeometry(0,0,400,100);
            connect(searchResultBtn,SIGNAL(clicked()),myMapper,SLOT(map()));
            myMapper->setMapping(searchResultBtn,searchResultBtn->text());
            connect(myMapper, SIGNAL(mapped(QString)), this, SLOT(on_friendChatBtn_clicked(QString)));
            searchResult->show();
            return;
        }
    }
    QMessageBox::information(this,"信息提示","查无此人",QMessageBox::Ok);
}

/* 函数名：on_addFriendBtn_clicked()
 * 功  能：完成添加好友功能
 */
void main_interface::on_addFriendBtn_clicked()
{
    QString friendName=addLine->text();
    if(friendName==""){
        QMessageBox::information(addFriendPatr,"警告","输入不能为空",QMessageBox::Ok);
        return;
    }
    else if(friendName==userName){
        QMessageBox::information(addFriendPatr,"警告","不能添加自己为好友",QMessageBox::Ok);
        return;
    }
    QString cs="c";
    QString data=cs+"#"+userName+"#"+friendName;
    //qDebug()<<data;
    tcpSocket->write(data.toLatin1());
}

/* 函数名：on_friendChatBtn_clicked(QString friendName)
 * 功  能：点击好友按钮，与好友开始聊天
 */
void main_interface::on_friendChatBtn_click(QString friendName)
{
    QString ds="d";
    QString data=ds+"#"+userName+"#"+friendName+"#";
    tcpSocket->write(data.toLatin1());
}

/* 函数名：mainMessages(QString mainMessage)
 * 功  能：从widget获得main部分信息并进行处理
 */
void main_interface::mainMessages(QString mainMessage)
{
    //qDebug()<<mainMessage;
    QString data=mainMessage;
    QStringList list=data.split("#");
    if(list[1]=="friendExist")
        QMessageBox::information(addFriendPatr,"信息提示","已存在该好友",QMessageBox::Ok);
    else if(list[1]=="noUser")
        QMessageBox::information(addFriendPatr,"信息提示","无法找到该用户",QMessageBox::Ok);
    else if(list[1]=="success"){
        addFriendPatr->close();
        list.removeFirst();
        list.removeFirst();
        list.removeLast();
        delete friendInf;
        friendInf=new QStringList;
        *friendInf=list;
        //qDebug()<<*friendInf<<friendInf->size();
        setFriendBtn();
        this->show();
    }
    else if(list[1]=="Esuccess"){
        list.removeFirst();
        list.removeFirst();
        list.removeLast();
        delete friendInf;
        friendInf=new QStringList;
        *friendInf=list;
        //qDebug()<<*friendInf<<friendInf->size();
        setFriendBtn();
        this->show();
    }
    else if(list[1]=="fail")
        QMessageBox::information(addFriendPatr,"信息提示","添加失败",QMessageBox::Ok);
    else return;
}

/* 函数名：setFriendBtn()
 * 功  能：对于传回的好友信息进行处理，并进行显示
 */
void main_interface::setFriendBtn()
{
    for(int i=0;i<friendBtnList.size();i++){
        friendBtnList.at(i)->hide();
        delete friendBtnList.at(i);
    }
    friendBtnList.clear();
    QLayoutItem *child;
    while ((child = friendlayout->itemAt(0)) != nullptr) {
            friendlayout->removeItem(child);
            delete child->widget();
            delete child;
            child = nullptr;
    }
    for(int i=0;i<friendInf->length();i++){
        QPushButton* friendBtn=new QPushButton(friendInf->at(i));
        friendBtn->setIcon(QIcon(":/new/prefix1/src/Friend.png"));
        friendBtn->setIconSize(QSize(30, 30));
        friendBtn->setStyleSheet(
                    "QPushButton{font-family:'微软雅黑';font-size:20px;color:rgb(50,50,50,250);}\
                    QPushButton{background:rgb(255,255,255);border:1px;border-radius:10px;padding:10px 10px}\
                    QPushButton:hover{background-color:rgb(253,114,109)}");
        friendBtnList.append(friendBtn);
        connect(friendBtn,SIGNAL(clicked()),myMapper,SLOT(map()));
        myMapper->setMapping(friendBtn,friendBtn->text());

        //connect(friendBtn, SIGNAL(mapped(QString)), this, [=](){on_friendChatBtn_clicked(friendBtn->text());});
    }
    connect(myMapper, SIGNAL(mapped(QString)), this, SLOT(on_friendChatBtn_click(QString)));


    for(int i=0;i<friendBtnList.size();i++){
        friendlayout->addWidget(friendBtnList.at(i));
    }
    friendlayout->addStretch();
}

/* 函数名：minBtn_clicked()
 * 功  能：实现窗口最小化
 */
void main_interface::minBtn_clicked()
{
    if( windowState() != Qt::WindowMinimized ){
        setWindowState( Qt::WindowMinimized );
    }
}
