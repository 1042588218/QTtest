#ifndef LOGINTHREAD_H
#define LOGINTHREAD_H

#include <QObject>

class loginThread : public QObject
{
    Q_OBJECT
public:
    explicit loginThread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LOGINTHREAD_H