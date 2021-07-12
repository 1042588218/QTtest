#ifndef CHAT_INTERFACE_H
#define CHAT_INTERFACE_H

#include <QObject>
#include <QWidget>

class chat_interface : public QWidget
{
    Q_OBJECT
public:
    explicit chat_interface(QWidget *parent = nullptr);
    ~chat_interface();
signals:

public slots:
};

#endif // CHAT_INTERFACE_H
