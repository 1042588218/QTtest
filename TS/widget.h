#ifndef WIDGET_H
#define WIDGET_H
#pragma once
#include <QObject>
#include <QWidget>
#include"chat_interface.h"
#include"main_interface.h"
#include"login_interface.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
    chat_interface* chatPart;
    login_interface* loginPart;
    main_interface* mainPart;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
};

#endif // WIDGET_H
