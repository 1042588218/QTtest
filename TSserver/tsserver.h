#ifndef TSSERVER_H
#define TSSERVER_H

#include <QWidget>
#include <QMainWindow>
#include <QtNetwork/QAbstractSocket>
#include<QtNetwork/QTcpSocket>
#include<QtNetwork/QTcpServer>
#include <QTimer>

namespace Ui {
class TSserver;
}

class TSserver : public QMainWindow
{
    Q_OBJECT

public:
    explicit TSserver(QMainWindow *parent = nullptr);
    ~TSserver();


    //服务器端与数据库相连接的函数
    bool checkSignIn(QString name,QString passward);
    bool checkSignUp(QString name,QString passward);
    int addFriendInf(QString userId, QString friendId);
    bool deletFriend(QString userId, QString friendId);
    bool updateMessages(QString reciverId,QString senderId,QString timeInf,QString messageInf);
    bool updateGroupMessages(QString reciverId,QString senderId,QString timeInf,QString messageInf);
    bool setGroup(QString setUser,QString groupName);
    QString beginChatGroup(QString userId,QString friendId);
    QString beginChat(QString userId,QString friendId);
    QString getFriendInf(QString name);


protected:
    void init();

private slots:
    void on_startBtn_clicked();

    void receiveData();

    void displayError(QAbstractSocket::SocketError);

    void NewConnectionSlot();

    void disconnectedSlot();

private:
    Ui::TSserver *ui;
    QList<QTcpSocket*> tcpClient;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QTimer *timer;
    QMap<QString, QTcpSocket*> map;
};

#endif // TSSERVER_H
