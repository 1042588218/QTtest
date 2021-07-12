#ifndef LOGIN_INTERFACE_H
#define LOGIN_INTERFACE_H
#pragma once
#include <QObject>
#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>

class login_interface : public QWidget
{
    Q_OBJECT

private:
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
    explicit login_interface(QWidget *parent = nullptr);
    ~login_interface();
    //声明三个鼠标事件函数
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:
    void minBtn_clicked();
};

#endif // LOGIN_INTERFACE_H
