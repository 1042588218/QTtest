#include "login_interface.h"
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



login_interface::login_interface(QWidget *parent,QTcpSocket *tcpSocket)
    : QWidget(parent)
{
    this->tcpSocket=tcpSocket;

    //基本窗口设置
    this->setWindowTitle("登陆界面");
    setFixedSize(540,380);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background,QColor(245,245,245));
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
    this->show();

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
    closeBtn->setGeometry(465,0,75,35);
    closeBtn->show();
    minBtn->setGeometry(380,0,75,35);
    minBtn->show();

    //标签插入项目图标
    Main=new QLabel(this);
    QString filename(":/new/prefix1/src/logo.png");
    QImage* img=new QImage;
    img->load(filename);
    Main->setGeometry(220,45,100,100);
    Main->setPixmap(QPixmap::fromImage(*img));
    Main->show();

    //实现账号和密码输入栏
    idLab=new QLabel("账号：",this);
    idLab->setStyleSheet("QLabel{font-family:'微软雅黑';font-size:25px;color:rgb(55,55,55,200);}");
    QFont *labFont=new QFont;
    labFont->setBold(true);
    idLab->setFont(*labFont);
    idEdit=new QLineEdit(this);
    QFont *editFont=new QFont;
    editFont->setBold(true);
    editFont->setFamily("微软雅黑");
    editFont->setPixelSize(20);
    idEdit->setPlaceholderText( "请输入账号" );
    idEdit->setFont(*editFont);
    idEdit->setMaxLength(12);
    idEdit->setValidator( new  QIntValidator(idEdit));
    passwordLab=new QLabel("密码：",this);
    passwordLab->setStyleSheet("QLabel{font-family:'微软雅黑';font-size:25px;color:rgb(55,55,55,200);}");
    passwordLab->setFont(*labFont);
    passwordEdit=new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setFont(*editFont);
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setMaxLength(16);
    QRegExp regx("[a-zA-Z0-9]+$");
    passwordEdit->setValidator(new QRegExpValidator(regx, this));
    QGridLayout* inLayout=new QGridLayout();
    inLayout->addWidget(idLab,0,0);
    inLayout->addWidget(idEdit,0,1);
    inLayout->addWidget(passwordLab,1,0);
    inLayout->addWidget(passwordEdit,1,1);
    inLayout->setContentsMargins(100,145,100,100);
    setLayout(inLayout);

    //实现登录、注册、找回按钮
    loginBtn=new QPushButton("登录",this);
    registeredBtn=new QPushButton("注册",this);
    loginBtn->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:25px;color:rgb(255,255,255,255);}\
    QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
    QPushButton:hover{background-color:rgb(253,114,109)}");
    QFont* btnFont=new QFont;
    btnFont->setBold(true);
    loginBtn->setFont(*btnFont);
    loginBtn->setGeometry(100,280,130,50);
    loginBtn->show();
    registeredBtn->setStyleSheet("QPushButton{font-family:'微软雅黑';font-size:25px;color:rgb(255,255,255,255);}\
    QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
    QPushButton:hover{background-color:rgb(253,114,109)}");
    registeredBtn->setFont(*btnFont);
    registeredBtn->setGeometry(310,280,130,50);
    registeredBtn->show();
    connect(loginBtn,SIGNAL(clicked()),this,SLOT(on_loginBtn_clicked()));
    connect(registeredBtn,SIGNAL(clicked()),this,SLOT(on_registeredBtn_clicked()));

}

login_interface::~login_interface()
{

}

/* 函数名：mouseReleaseEvent(QMouseEvent *event)
 * 函数名：mousePressEvent(QMouseEvent *event)
 * 函数名：mouseMoveEvent(QMouseEvent *event)
 * 功  能：实现鼠标拖动无边框窗口
 */
void login_interface::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void login_interface::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//判断左键是否按下
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

void login_interface::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());//移动当前窗口
}


/* 函数名：minBtn_clicked()
 * 功  能：实现窗口最小化
 */
void login_interface::minBtn_clicked()
{
    if( windowState() != Qt::WindowMinimized ){
        setWindowState( Qt::WindowMinimized );
    }
}

/* 函数名：on_loginBtn_clicked()
 * 功  能：实现登录操作
 */
void login_interface::on_loginBtn_clicked()
{
    QString userName=idEdit->text();
    QString passward=passwordEdit->text();
    if(userName=="" || passward==""){
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
        return;
    }
    QString bs="b";
    QString data=bs+"#"+userName+"#"+passward;
    tcpSocket->write(data.toLatin1());
}

/* 函数名：on_registeredBtn_clicked()
 * 功  能：实现注册操作
 */
void login_interface::on_registeredBtn_clicked()
{
    QString userName=idEdit->text();
    QString passward=passwordEdit->text();
    if(userName=="" || passward=="")
        QMessageBox::information(this,"警告","输入不能为空",QMessageBox::Ok);
    QString as="a";
    QString data=as+"#"+userName+"#"+passward;
    tcpSocket->write(data.toLatin1());
}

/* 函数名：on_registeredBtn_clicked()
 * 功  能：接受注册、登陆的信息，并对登录的结果进行判断
 */
void login_interface::loginMessages(QString loginMessage)
{
    QString data=loginMessage;
    QStringList list=data.split("#");
    if(list[0]=="a" && list[1]=="true")
        QMessageBox::information(this,"信息提示","注册成功!",QMessageBox::Ok);
    else if(list[0]=="a" && list[1]=="false")
        QMessageBox::information(this,"信息提示","注册失败,用户名已经被注册!",QMessageBox::Ok);
    else if(list[0]=="b" && list[1]=="true"){
        QString userName=idEdit->text();
        emit(loginUser(data,userName));
        emit(loginSuccess());
        this->close();
    }
    else if(list[0]=="b" && list[1]=="false")
            QMessageBox::information(this,"信息提示","登录失败,用户名或密码错误!",QMessageBox::Ok);
    else
        return;
}
