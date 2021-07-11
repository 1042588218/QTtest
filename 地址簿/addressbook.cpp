#include <QtGui>
#include<QLabel>
#include<QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QTextEdit>
#include<QBoxLayout>
#include<QGridLayout>

#include "addressbook.h"

Address::Address(QWidget* parent):QWidget(parent)
{
    QLabel *nameLabel= new QLabel( "Name:");
    nameLine= new QLineEdit();

    QLabel *addressLabel= new QLabel( "Address:");
    addressText= new QTextEdit;

    addButton= new QPushButton( "&Add");
    addButton->show();

    submitButton= new QPushButton( "&Submit");
    submitButton->show();

    connect(addButton,SIGNAL(clicked()), this,SLOT(addContact()));


    cancelButton= new QPushButton( "&Cancel");
    cancelButton->show();

    QVBoxLayout* btnLayout= new QVBoxLayout();
    btnLayout->addWidget(addButton);
    btnLayout->addWidget(submitButton);
    btnLayout->addWidget(cancelButton);

    QGridLayout *mainLayout= new QGridLayout;
    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(nameLine,0,1);
    mainLayout->addWidget(addressLabel,1,0,Qt::AlignTop);
    mainLayout->addWidget(addressText,1,1);
    mainLayout->addLayout(btnLayout,1,2,Qt::AlignTop);

    setLayout(mainLayout);
    setWindowTitle( "Simple Address Book");
}
