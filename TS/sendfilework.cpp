#include "sendfilework.h"


#include <QFile>
#include <QFileInfo>
#include <QHostAddress>
#include <QDebug>
#include <QThread>

#define ip "192.168.31.140"
#define port 8000

sendFileWork::sendFileWork(QObject *parent) : QThread(parent)
{
    m_tcp = new QTcpSocket;
    m_tcp->connectToHost(QHostAddress(ip), port);
}

void sendFileWork::connectServer()
{

}

void sendFileWork::sendFile(QString path,QString data)
{
    m_tcp->write(data.toUtf8());
    QFile file(path);
    QFileInfo info(path);
    int fileSize = info.size();

    file.open(QFile::ReadOnly);

    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        m_tcp->write(line);
    }
    emit(over());
}
