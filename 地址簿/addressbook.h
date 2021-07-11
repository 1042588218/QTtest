#ifndef __ADDRESSBOOK_H__
#define __ADDRESSBOOK_H__

// 地址簿
#include <QWidget>

class QLineEdit;
class QTextEdit;
class QPushButton;

class Address: public QWidget
{
public:
    Address(QWidget* parent=0);
public slots:
    void addContact();
    void submitContact();
    void cancel();

private:
    QPushButton* addButton;
    QPushButton* submitButton;
    QPushButton* cancelButton;
    QLineEdit *nameLine;
    QTextEdit *addressText;
};
#endif // __ADDRESSBOOK_H__
