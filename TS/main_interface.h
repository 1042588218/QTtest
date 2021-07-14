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

enum Direction {
    UP, DOWN, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE
};

class main_interface : public QWidget
{
    Q_OBJECT

private:
    QString* userName;
    QLabel* helloWord;
    void judgeRegionSetCursor(const QPoint&);
    const int Padding = 2;
    bool isLeftPressDown;  // 判断左键是否按下
    QPoint dragPosition;   // 窗口移动拖动时需要记住的点
    // 窗口大小改变时，记录改变方向
    Direction dir;

    QPushButton* closeBtn;
    QPushButton* minBtn;

public:
    explicit main_interface(QWidget *parent = nullptr);
    ~main_interface();
    //声明三个鼠标事件函数
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

signals:

public slots:
    void reciveUsername(QString userName);
    void minBtn_clicked();
};

#endif // MAIN_INTERFACE_H
