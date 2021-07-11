#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    //重写绘图事件， Q_ECL_OVERRIDE表示对父类这个函数改写
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
