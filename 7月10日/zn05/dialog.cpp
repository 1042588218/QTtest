#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

//防止中文乱码宏
//#define z(s) (QString::fromLocal8Bit(s))

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    int i;
    QString str[] = {"苹果", "鸭梨", "西瓜"};
    for(i = 0; i < 3; i++)
        fruit.push_back(str[i]);
    model = new QStringListModel(this);
    model->setStringList(fruit);
    ui->listView->setModel(model);
}

Dialog::~Dialog()
{
    delete ui;
    if(model != nullptr)
        delete model;
}

void Dialog::on_btnGetNRow_clicked()
{
    //通过model获得数据模型，然后通过rowCount获取行数
    int row_num = ui->listView->model()->rowCount();
    QString str = "共有"+QString::number(row_num)+"行";
    QMessageBox::information(this,"note",str);
}

void Dialog::on_pushButton_2_clicked()
{
    // column_idx为该列索引序号,两者都以0开始
    int row_idx = 1,column_idx=0;
    QString str = ui->listView->model()->index(row_idx, column_idx).data().toString();
    QMessageBox::information(this,"note",str);
}

void Dialog::on_pushButton_3_clicked()
{
    fruit=model->stringList();//把当前列表视图控件中的数据项列表保存好，这样是为了同步
    fruit+="枇杷";
    model->setStringList(fruit);
}

void Dialog::on_pushButton_4_clicked()
{
    model->removeRow(0);//从第1行开始，删除1行
}

void Dialog::on_pushButton_5_clicked()
{
    model->removeRows(0,2);//从第1行开始，删除2行
}

void Dialog::on_pushButton_6_clicked()
{
    model->removeRows(0,model->rowCount());
         fruit.clear();
}

void Dialog::on_pushButton_7_clicked()
{
    QModelIndex index = model->index(1);
     ui->listView->setCurrentIndex(index);
}

void Dialog::on_pushButton_8_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    int row = index.row()+1;//索引号加1

     QString str = "你选中了第"+QString::number(row)+"行，内容是："+index.data().toString();
     QMessageBox::information(this,"note",str);
}
