#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));//设置窗口背景为白色
    // 该函数用于设置当窗口作为被包含窗口时, 是否需要绘制背景。
    setAutoFillBackground(true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    // 创建绘图对象
    QPainter painer(this);
    painer.setRenderHint(QPainter::Antialiasing); //绘图抗锯齿
    painer.setRenderHint(QPainter::TextAntialiasing);//绘制的字体抗锯齿

    int W = this->width(); // 绘图区宽度
    int H = this->height(); // 绘图区高度

    QRect rect(W/4, H/4, W/2, H/2); //中间区域矩形框

    //设置画笔
    QPen pen;
    pen.setWidth(3); // 线宽
    pen.setColor(Qt::red); //划线的颜色
    pen.setStyle(Qt::SolidLine); //线样式
    pen.setCapStyle(Qt::FlatCap); //线端点样式
    pen.setJoinStyle(Qt::BevelJoin); //线连接点样式
    painer.setPen(pen);

    //画刷设置
    QBrush brush;
    brush.setColor(Qt::yellow); // 画刷颜色
    brush.setStyle(Qt::SolidPattern); //画刷填充样式
    painer.setBrush(brush);
    painer.drawRect(rect);






}
