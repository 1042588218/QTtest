#include "recvfile.h"
#include <QFile>
#include <QDebug>
#include<QMessageBox>
RecvFile::RecvFile(QObject *parent) : QThread(parent)
{
}


/* 函数名：recv(QStringList data)
 * 功  能：用于完成文件接收
 */
void RecvFile::recv(QStringList data)
{
    QFile* file = new QFile("D:/QT/recv.txt");
    file->open(QIODevice::ReadWrite | QIODevice::Text);

    qDebug()<<data.last().toUtf8();
    file->write(data.last().toUtf8());
    file->close();
    emit(over());
}
