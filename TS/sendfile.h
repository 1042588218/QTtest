#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include<QFile>
#include<QThread>
#include<QFileInfo>
#include <QTcpSocket>

class sendFile : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* S_tcp;

public:
    explicit sendFile(QObject *parent = nullptr);


    // 连接服务器
    void connectServer(unsigned short port);


signals:
    void over();
    void connectOK();

public slots:
    // 发送文件
    void SendFile(QString path);
};

#endif // SENDFILE_H
