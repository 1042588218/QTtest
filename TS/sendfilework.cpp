#include "sendfilework.h"


#include <QFile>
#include <QFileInfo>
#include <QHostAddress>
#include <QDebug>
#include <QThread>

#define ip "192.168.136.1"
#define port 8000

sendFileWork::sendFileWork(QObject *parent) : QThread(parent)
{
    m_tcp = new QTcpSocket;
    m_tcp->connectToHost(QHostAddress(ip), port);
}



/* 函数名：sendFile(QString path,QString data)
 * 功  能：用于完成文件发送
 */
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
