#include "recvfile.h"
#include <QFile>
#include <QDebug>
#include<QMessageBox>
RecvFile::RecvFile(QObject *parent) : QThread(parent)
{
}

void RecvFile::recv(QStringList data)
{
    QFile* file = new QFile("D:/QT/recv.txt");
    file->open(QIODevice::ReadWrite | QIODevice::Text);

    qDebug()<<data.last().toUtf8();
    file->write(data.last().toUtf8());
    file->close();
    emit(over());
}
