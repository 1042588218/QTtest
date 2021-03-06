#ifndef CHAT_INTERFACE_H
#define CHAT_INTERFACE_H
#pragma once
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include <QtNetwork/QAbstractSocket>
#include<QtNetwork/QTcpSocket>
#include <QMessageBox>
#include<QTextBrowser>
#include "sendfilework.h"
#include "recvfile.h"

//聊天界面

class chat_interface : public QWidget
{
    Q_OBJECT
private:
    QTcpSocket *tcpSocket;
    //鼠标是否按下属性
    bool m_bPressed=false;
    //按下后当前鼠标位置属性
    QPoint m_point;
    //主界面控件设置
    QPushButton* closeBtn;
    QPushButton* minBtn;
    QTextBrowser* chatHistory;
    QTextEdit* chatMessage;
    QPushButton* sendFile;
    QPushButton* deletFriend;
    QPushButton* closeChatBtn;
    QPushButton* sendBtn;
    QPushButton* backgroundBtn;
    QString* userName;
    QLabel* chatFriendLab;
    QLabel* chatPic;

public:
    explicit chat_interface(QWidget *parent = nullptr,QTcpSocket *tcpSocket=nullptr);
    ~chat_interface() override;
    //声明三个鼠标事件函数
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void sendFileSignal(QString,QString);
    void recvFileSignal(QStringList);
public slots:
    void chatMessages(QString chatMessage);
    void minBtn_clicked();
    void on_deletFriend_clicked();
    void on_sendBtn_clicked();
    void autoScroll();
    void on_sendFile_clicked();
};

#endif // CHAT_INTERFACE_H
