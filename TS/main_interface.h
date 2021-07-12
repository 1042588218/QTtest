#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H
#pragma once
#include <QObject>
#include <QWidget>

class main_interface : public QWidget
{
    Q_OBJECT
public:
    explicit main_interface(QWidget *parent = nullptr);
    ~main_interface();
signals:

public slots:
};

#endif // MAIN_INTERFACE_H
