#ifndef SENDFILEWORK_H
#define SENDFILEWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>

class sendFileWork : public QThread
{
    Q_OBJECT
public:
    explicit sendFileWork(QObject *parent = nullptr);

    // 连接服务器
    void connectServer();

    // 发送文件
    void sendFile(QString path,QString data);

signals:
    void connectOK();
    void over();

private:
    QTcpSocket* m_tcp;
};

#endif // SENDFILEWORK_H
