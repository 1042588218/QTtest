#ifndef LOGIN_INTERFACE_H
#define LOGIN_INTERFACE_H
#pragma once
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include <QtNetwork/QAbstractSocket>
#include<QtNetwork/QTcpSocket>
#include <QMessageBox>

class login_interface : public QWidget
{
    Q_OBJECT

private:
    QTcpSocket *tcpSocket;

    //鼠标是否按下属性
    bool m_bPressed=false;
    //按下后当前鼠标位置属性
    QPoint m_point;

    QPushButton* closeBtn;
    QPushButton* minBtn;
    QLabel* Main;
    QLabel* idLab;
    QLineEdit* idEdit;
    QLabel* passwordLab;
    QLineEdit* passwordEdit;
    QPushButton* loginBtn;
    QPushButton* registeredBtn;
    QPushButton* findbaceBtn;

public:
    explicit login_interface(QWidget *parent = nullptr,QTcpSocket *tcpSocket=nullptr);
    ~login_interface();
    //声明三个鼠标事件函数
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    QString loginSuccess();
    QString loginUser(QString userInf,QString userName);

public slots:
    void minBtn_clicked();
    void on_registeredBtn_clicked();
    void on_loginBtn_clicked();
    void loginMessages(QString loginMessage);

};

#endif // LOGIN_INTERFACE_H
