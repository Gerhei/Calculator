#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onButton();
    void onEqually();
    void onClr();
    void onDel();

private:
    Ui::Widget *ui;
    QLabel *input;
    QLabel *output;
    Calculator calculator;

    //запихнуть в отдельный класс
    QVector<QString> numbers={"7","8","9","4","5","6","1","2","3","0"};
    QVector<QString> BinaryOperations={"/","*","-","+","^"};
    QVector<QString> UnaryOperations={"sin","cos","tg","sqrt"};
    //унарные оперции
    //постфиксные операции(факториал)
};
#endif // WIDGET_H
