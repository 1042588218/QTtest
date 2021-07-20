#ifndef RECVFILE_H
#define RECVFILE_H

#include <QThread>
#include <QTcpSocket>

//文件接收线程

class RecvFile : public QThread
{
    Q_OBJECT
public:
    explicit RecvFile(QObject *parent = nullptr);
    void recv(QStringList data);


signals:
    void over();

};

#endif // RECVFILE_H
