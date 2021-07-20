#ifndef GROUPCHAT_INTERFACE_H
#define GROUPCHAT_INTERFACE_H
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

//群聊界面

class groupChat_interface : public QWidget
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
    QPushButton* groupFriend;
    QPushButton* quitGroup;
    QPushButton* closeChatBtn;
    QPushButton* sendBtn;
    QPushButton* backgroundBtn;
    QString* userName;
    QLabel* chatFriendLab;
    QLabel* chatPic;
    //群聊管理界面控件设置
    QWidget* management;
    QPushButton* manageCloseBtn;
    QPushButton* manegeMinBtn;
    QTextBrowser* manegeTextBrowser;
    QLineEdit* manegeLineEdit;
    QPushButton* addBtn;
    QPushButton* deleteBtn;

public:
    groupChat_interface(QWidget *parent = nullptr,QTcpSocket *tcpSocket=nullptr);
    ~groupChat_interface() override;
    //声明三个鼠标事件函数
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void groupChatMessages(QString chatMessage);
    void minBtn_clicked();
    void autoScroll();
    void on_sendBtn_clicked();
    void on_quitGroup_clicked();
    void on_groupFriend_clicked();
    void on_addBtn_clicked();
    void on_deletBtn_clicked();
};

#endif // GROUPCHAT_INTERFACE_H
