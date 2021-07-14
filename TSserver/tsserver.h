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

    bool checkSignIn(QString name,QString passward);
    bool checkSignUp(QString name,QString passward);

protected:
    void init();

private slots:
    void on_startBtn_clicked();

    void acceptConnection();

    void receiveData();

    void displayError(QAbstractSocket::SocketError);

private:
    Ui::TSserver *ui;
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    QTimer *timer;
};

#endif // TSSERVER_H
