#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H
#pragma once
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include <QtNetwork/QAbstractSocket>
#include<QtNetwork/QTcpSocket>
#include <QMessageBox>
#include<QList>
#include<QVBoxLayout>
#include <QSignalMapper>
#include<QtNetwork/QTcpSocket>

enum Direction {
    UP, DOWN, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE
};

class main_interface : public QWidget
{
    Q_OBJECT

private:
    QTcpSocket *tcpSocket;

    QString* userInf;
    QString* userName;
    QStringList* friendInf;
    QLabel* helloWord;
    //鼠标是否按下属性
    bool m_bPressed=false;
    //按下后当前鼠标位置属性
    QPoint m_point;

    QList<QPushButton*> friendBtnList;
    QPushButton* minBtn;
    QPushButton* searchBtn;
    QLineEdit* searchLine;
    QWidget *friendList;
    QWidget* searchResult;
    QPushButton* searchResultBtn;
    QPushButton* addBtn;
    QVBoxLayout* friendlayout;
    QSignalMapper * myMapper;

    QWidget* addFriendPatr;
    QPushButton* addFriendBtn;
    QLineEdit* addLine;
    QPushButton* closeAddBtn;

public:
    QPushButton* closeBtn;
    QPushButton* exitBtn;
    explicit main_interface(QWidget *parent = nullptr,QTcpSocket *tcpSocket=nullptr);
    ~main_interface()override;
    //声明三个鼠标事件函数
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

signals:
    void chatWithFriend(QString friendName);

public slots:
    void reciveUsername(QString userName,QString userInf);
    void minBtn_clicked();
    void setFriendBtn();
    void on_searchBtn_clicked();
    void on_addFriendBtn_clicked();
    void on_friendChatBtn_clicked(QString friendName);
    void mainMessages(QString mainMessage);
};

#endif // MAIN_INTERFACE_H
