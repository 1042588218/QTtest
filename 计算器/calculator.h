#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

namespace Ui {
class Calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT
private:
    //两个变量记录输入数据以及结果
    QString* tmp;
    QString* formula;
    //用于判断是否已有小数点
    bool spot=1;
    //记录输入的上一个运算符
    char tmpOperator;

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();
    void Calculate();

private:
    Ui::Calculator *ui;
private slots:
    //定义实现各个功能的函数
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_spot_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_negative_clicked();
    void on_pushButton_restart1_clicked();
    void on_pushButton_rstart_clicked();
    void on_pushButton_reciprocal_clicked();
    void on_pushButton_square_clicked();
    void on_pushButton_persent_clicked();
    void on_pushButton_root_clicked();
    void on_pushButton_devide_clicked();
    void on_pushButton_multiply_clicked();
    void on_pushButton_reduce_clicked();
    void on_pushButton_plus_clicked();
    void on_pushButton_equal_clicked();
};

#endif // CALCULATOR_H
