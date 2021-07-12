#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    loginPart=new login_interface;

    mainPart=new main_interface;

    chatPart=new chat_interface;


}

Widget::~Widget()
{

}
