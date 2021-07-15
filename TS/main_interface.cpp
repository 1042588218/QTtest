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

main_interface::main_interface(QWidget *parent)
    : QWidget(parent)
{
    isLeftPressDown = false;
        dir = NONE;
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
    helloWord->setStyleSheet("QLabel{font-family:'宋体';font-size:22px;color:rgb(255,255,255,200);}");
    QFont* helloFont=new QFont();
    helloFont->setBold(true);
    helloWord->setFont(*helloFont);
    helloWord->setGeometry(10,10,220,35);
    helloWord->setAlignment(Qt::AlignCenter);

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
    friendList=new QWidget(this);
    addBtn=new QPushButton("添加好友",this);
    addBtn->setStyleSheet(
                "QPushButton{font-family:'微软雅黑';font-size:20px;color:rgb(255,255,255,255);}\
                QPushButton{background:rgb(236,65,65);border:1px;border-radius:10px;padding:10px 10px}\
                QPushButton:hover{background-color:rgb(253,114,109)}");
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
    setLayout(mainLayout);

}

main_interface::~main_interface()
{

}

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
    qDebug()<<*friendInf<<friendInf->size();
    qDebug()<<*(this->userName)<<"登录";
    helloWord->setText("Hello! "+*(this->userName)+"!");
    helloWord->show();
}

void main_interface::judgeRegionSetCursor(const QPoint& currentPoint)
{
    // 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = currentPoint.x();
    int y = currentPoint.y();

    if (tl.x() + Padding >= x && tl.x() <= x && tl.y() + Padding >= y && tl.y() <= y) {
        // 左上角
        dir = LEFTTOP;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
    }
    else if (x >= rb.x() - Padding && x <= rb.x() && y >= rb.y() - Padding && y <= rb.y()) {
        // 右下角
        dir = RIGHTBOTTOM;
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if (x <= tl.x() + Padding && x >= tl.x() && y >= rb.y() - Padding && y <= rb.y()) {
        //左下角
        dir = LEFTBOTTOM;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (x <= rb.x() && x >= rb.x() - Padding && y >= tl.y() && y <= tl.y() + Padding) {
        // 右上角
        dir = RIGHTTOP;
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if (x <= tl.x() + Padding && x >= tl.x()) {
        // 左边
        dir = LEFT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (x <= rb.x() && x >= rb.x() - Padding) {
        // 右边
        dir = RIGHT;
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if (y >= tl.y() && y <= tl.y() + Padding) {
        // 上边
        dir = UP;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else if (y <= rb.y() && y >= rb.y() - Padding) {
        // 下边
        dir = DOWN;
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else {
        // 默认
        dir = NONE;
        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void main_interface::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isLeftPressDown = false;
        if (dir != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}
void main_interface::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
        isLeftPressDown = true;
        if (dir != NONE) {
            this->mouseGrabber();
        }
        else {
            dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        }
        break;
    default:
        QWidget::mousePressEvent(event);
    }
}
void main_interface::mouseMoveEvent(QMouseEvent *event)
{
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if (!isLeftPressDown) {
        this->judgeRegionSetCursor(gloPoint);
    }
    else {

        if (dir != NONE) {
            QRect rMove(tl, rb);

            switch (dir) {
            case LEFT:
                if (rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                break;
            case RIGHT:
                rMove.setWidth(gloPoint.x() - tl.x());
                break;
            case UP:
                if (rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case DOWN:
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case LEFTTOP:
                if (rb.x() - gloPoint.x() <= this->minimumWidth())
                    rMove.setX(tl.x());
                else
                    rMove.setX(gloPoint.x());
                if (rb.y() - gloPoint.y() <= this->minimumHeight())
                    rMove.setY(tl.y());
                else
                    rMove.setY(gloPoint.y());
                break;
            case RIGHTTOP:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setY(gloPoint.y());
                break;
            case LEFTBOTTOM:
                rMove.setX(gloPoint.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            case RIGHTBOTTOM:
                rMove.setWidth(gloPoint.x() - tl.x());
                rMove.setHeight(gloPoint.y() - tl.y());
                break;
            default:
                break;
            }
            this->setGeometry(rMove);
        }
        else {
            move(event->globalPos() - dragPosition);
            event->accept();
        }
    }
    QWidget::mouseMoveEvent(event);
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
