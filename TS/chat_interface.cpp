#include "chat_interface.h"

chat_interface::chat_interface(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("聊天界面");
    this->close();
}

chat_interface::~chat_interface()
{

}
