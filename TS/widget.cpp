#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    loginPart=new login_interface;

    mainPart=new main_interface;

    chatPart=new chat_interface;

    connect(loginPart,SIGNAL(loginSuccess()),mainPart,SLOT(show()));
    connect(loginPart,SIGNAL(loginUser(QString,QString)),mainPart,SLOT(reciveUsername(QString,QString)));
}

Widget::~Widget()
{

}
