#include "calculator.h"
#include "ui_calculator.h"
#include<math.h>
#include<ostream>
#include<QMessageBox>

Calculator::Calculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calculator)
{
    setFixedSize(540,380);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background,QColor("#9b95c9"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    setWindowOpacity(0.98);//设置窗口透明度
    tmp=new QString("");
    formula=new QString("");
    ui->setupUi(this);
    setFixedSize(470,800);
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    ui->textEdit_2->setAlignment(Qt::AlignRight);
    QPalette pl = ui->textEdit_1->palette();
    pl.setBrush(QPalette::Base,QBrush(QColor("#e6f0fa")));
    ui->textEdit_1->setPalette(pl);
    QPalette pl1 = ui->textEdit_2->palette();
    pl1.setBrush(QPalette::Base,QBrush(QColor("#e6f0fa")));
    ui->textEdit_2->setPalette(pl1);
    ui->pushButton_0->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_1->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_2->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_3->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_4->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_5->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_6->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_7->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_8->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_9->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_plus->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_root->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_spot->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_equal->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_delete->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_devide->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_rstart->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_reduce->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_square->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_persent->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_multiply->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_negative->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_restart1->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");
    ui->pushButton_reciprocal->setStyleSheet(
                "QPushButton{background:#e6f0fa;border:2px;border-radius:10px;padding:10px 10px}"\
                "QPushButton:hover{background:#e6f0fa;border:2px groove gray;border-radius:20px;padding:20px 20px}");

}

Calculator::~Calculator()
{
    delete ui;
}

/* 函数名：Calculate()
 * 功  能：计算当前运算操作
 */
void Calculator::Calculate(){
    if(tmpOperator==NULL)return;
    double a=formula->toDouble();
    double b=tmp->toDouble();
    switch (tmpOperator) {
    case '/':
        tmp->setNum(a/b);
        break;
    case '*':
        tmp->setNum(a*b);
        break;
    case '+':
        tmp->setNum(a+b);
        break;
    case '-':
        tmp->setNum(a-b);
        break;
    }
}

/* 函数名：on_pushButton_X_clicked()
 * 功  能:实现各个数字的操作
 */
void Calculator::on_pushButton_0_clicked()
{
    if(tmp->size()==0)return;
    tmp->append('0');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);

}

void Calculator::on_pushButton_1_clicked()
{
    tmp->append('1');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

void Calculator::on_pushButton_2_clicked()
{
    tmp->append('2');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

void Calculator::on_pushButton_3_clicked()
{
    tmp->append('3');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

void Calculator::on_pushButton_4_clicked()
{
    tmp->append('4');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

void Calculator::on_pushButton_5_clicked()
{
    tmp->append('5');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

void Calculator::on_pushButton_6_clicked()
{
    tmp->append('6');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

void Calculator::on_pushButton_7_clicked()
{
    tmp->append('7');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

void Calculator::on_pushButton_8_clicked()
{
    tmp->append('8');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

void Calculator::on_pushButton_9_clicked()
{
    tmp->append('9');
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

/* 函数名：on_pushButton_spot_clicked()
 * 功  能:实现小数点操作
 */
void Calculator::on_pushButton_spot_clicked()
{
    if(spot==1){
        if(tmp->size()==0){
            tmp->append("0.");
        }
        else{
            tmp->append('.');
        }
        spot=0;
    }
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}

/* 函数名：on_pushButton_delete_clicked()
 * 功  能:实现删除键操作
 */
void Calculator::on_pushButton_delete_clicked()
{
    if(*tmp=="")return;
    if(*tmp=="0."){
        spot=1;
        *tmp="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
        return;
    }
    if(*tmp!=""&&tmp->at(tmp->size()-1)==".")spot=1;
    if(*tmp!=""){
        tmp->remove(tmp->size()-1,1);
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
    }
    if(*tmp=="-"){
        *tmp="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
        return;
    }
}

/* 函数名：on_pushButton_negative_clicked()
 * 功  能:实现正负号键操作
 */
void Calculator::on_pushButton_negative_clicked()
{
    if(*tmp=="")return;
    if(tmp->at(0)!='-'){
        tmp->insert(0,'-');
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
    }
    else {
        tmp->remove(0,1);
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
    }
}

/* 函数名：on_pushButton_restart1_clicked()
 * 功  能:实现CE键操作
 */
void Calculator::on_pushButton_restart1_clicked()
{
    spot=1;
    tmpOperator=NULL;
    *tmp="";
    *formula="";
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    ui->textEdit_2->setText(*formula);
    ui->textEdit_2->setAlignment(Qt::AlignRight);
}

/* 函数名：on_pushButton_restart_clicked()
 * 功  能:实现C键操作
 */
void Calculator::on_pushButton_rstart_clicked()
{
    spot=1;
    *tmp="";
    tmpOperator=NULL;
    *formula="";
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    ui->textEdit_2->setText(*formula);
    ui->textEdit_2->setAlignment(Qt::AlignRight);
}

/* 函数名：on_pushButton_reciprocal_clicked()
 * 功  能:实现倒数键操作
 */
void Calculator::on_pushButton_reciprocal_clicked()
{
    double T=tmp->toDouble();
    double t=1/T;
    tmp->setNum(t);
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    if(*tmp=="inf"){
        spot=1;
        *tmp="";
        tmpOperator=NULL;
        *formula="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
        ui->textEdit_2->setText(*formula);
        ui->textEdit_2->setAlignment(Qt::AlignRight);
        QMessageBox::information(this,tr("警告"),tr("不允许将0作为除数"));
    }
}

/* 函数名：on_pushButton_square_clicked()
 * 功  能:实现平方键操作
 */
void Calculator::on_pushButton_square_clicked()
{
    double T=tmp->toDouble();
    double t=T*T;
    tmp->setNum(t);
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    if(*tmp=="0"){
        spot=1;
        *tmp="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
    }
}

/* 函数名：on_pushButton_persent_clicked()
 * 功  能:实现百分键操作
 */
void Calculator::on_pushButton_persent_clicked()
{
    double T=tmp->toDouble();
    double t=T/100;
    tmp->setNum(t);
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    if(*tmp=="0"){
        spot=1;
        *tmp="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
    }
}

/* 函数名：on_pushButton_root_clicked()
 * 功  能:实现开方键操作
 */
void Calculator::on_pushButton_root_clicked()
{
    double T=tmp->toDouble();
    double t=sqrt(T);
    tmp->setNum(t);
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    if(*tmp=="0"){
        spot=1;
        *tmp="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
    }
}

/* 函数名：on_pushButton_devide_clicked()
 * 功  能:实现除号键操作
 */
void Calculator::on_pushButton_devide_clicked()
{
    if(*tmp==""){
        tmpOperator='/';
        return;
    }
    Calculate();
    if(*tmp=="inf"){
        spot=1;
        tmpOperator=NULL;
        *tmp="";
        *formula="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
        ui->textEdit_2->setText(*formula);
        ui->textEdit_2->setAlignment(Qt::AlignRight);
        QMessageBox::information(this,tr("警告"),tr("不允许将0作为除数"));
        return;
    }
    tmpOperator='/';
    *formula=*tmp;
    spot=1;
    *tmp="";
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    ui->textEdit_2->setText(*formula);
    ui->textEdit_2->setAlignment(Qt::AlignRight);
}

/* 函数名：on_pushButton_multiply_clicked()
 * 功  能:实现乘号键操作
 */
void Calculator::on_pushButton_multiply_clicked()
{
    if(*tmp==""){
        tmpOperator='*';
        return;
    }
    Calculate();
    if(*tmp=="inf"){
        spot=1;
        tmpOperator=NULL;
        *tmp="";
        *formula="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
        ui->textEdit_2->setText(*formula);
        ui->textEdit_2->setAlignment(Qt::AlignRight);
        QMessageBox::information(this,tr("警告"),tr("不允许将0作为除数"));
        return;
    }
    tmpOperator='*';
    *formula=*tmp;
    spot=1;
    *tmp="";
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    ui->textEdit_2->setText(*formula);
    ui->textEdit_2->setAlignment(Qt::AlignRight);
}

/* 函数名：on_pushButton_reduce_clicked()
 * 功  能:实现减号键操作
 */
void Calculator::on_pushButton_reduce_clicked()
{
    if(*tmp==""){
        tmpOperator='-';
        return;
    }
    Calculate();
    if(*tmp=="inf"){
        spot=1;
        tmpOperator=NULL;
        *tmp="";
        *formula="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
        ui->textEdit_2->setText(*formula);
        ui->textEdit_2->setAlignment(Qt::AlignRight);
        QMessageBox::information(this,tr("警告"),tr("不允许将0作为除数"));
        return;
    }
    tmpOperator='-';
    *formula=*tmp;
    spot=1;
    *tmp="";
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    ui->textEdit_2->setText(*formula);
    ui->textEdit_2->setAlignment(Qt::AlignRight);
}

/* 函数名：on_pushButton_plus_clicked()
 * 功  能:实现加号键操作
 */
void Calculator::on_pushButton_plus_clicked()
{
    if(*tmp==""){
        tmpOperator='+';
        return;
    }
    Calculate();
    if(*tmp=="inf"){
        spot=1;
        tmpOperator=NULL;
        *tmp="";
        *formula="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
        ui->textEdit_2->setText(*formula);
        ui->textEdit_2->setAlignment(Qt::AlignRight);
        QMessageBox::information(this,tr("警告"),tr("不允许将0作为除数"));
        return;
    }
    tmpOperator='+';
    *formula=*tmp;
    spot=1;
    *tmp="";
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
    ui->textEdit_2->setText(*formula);
    ui->textEdit_2->setAlignment(Qt::AlignRight);
}

/* 函数名：on_pushButton_equal_clicked()
 * 功  能:实现等号键操作
 */
void Calculator::on_pushButton_equal_clicked()
{
    Calculate();
    if(*tmp=="inf"){
        spot=1;
        tmpOperator=NULL;
        *tmp="";
        *formula="";
        ui->textEdit_1->setText(*tmp);
        ui->textEdit_1->setAlignment(Qt::AlignRight);
        ui->textEdit_2->setText(*formula);
        ui->textEdit_2->setAlignment(Qt::AlignRight);
        QMessageBox::information(this,tr("警告"),tr("不允许将0作为除数"));
        return;
    }
    tmpOperator=NULL;
    *formula="";
    ui->textEdit_2->setText(*formula);
    ui->textEdit_2->setAlignment(Qt::AlignRight);
    if(tmp->contains("."))spot=0;
    ui->textEdit_1->setText(*tmp);
    ui->textEdit_1->setAlignment(Qt::AlignRight);
}
