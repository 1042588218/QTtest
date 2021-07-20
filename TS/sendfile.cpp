#include "sendfile.h"
#include<QHostAddress>
#define ip "192.168.31.140"


sendFile::sendFile(QObject *parent) : QObject(parent)
{

}

void sendFile::connectServer(unsigned short port){
    S_tcp = new QTcpSocket;
    S_tcp->connectToHost(QHostAddress(ip), port);

    connect(S_tcp, SIGNAL(connected()), this, SLOT(connectOK()));
    connect(S_tcp, &QTcpSocket::disconnected, this, [=](){
        S_tcp->close();
        S_tcp->deleteLater();
        emit(over());
    });
}

void sendFile::SendFile(QString path)
{

    QFile file(path);
    QFileInfo info(path);
    int fileSize = info.size();

    file.open(QFile::ReadOnly);
    while(!file.atEnd())
    {
        static int num = 0;
        if(num == 0)
        {
            S_tcp->write((char*)&fileSize, 4);
        }
        QByteArray line = file.readLine();
        num += line.size();
        S_tcp->write(line);
    }
}
