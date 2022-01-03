#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QString>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QVBoxLayout *VerticalGrid=new QVBoxLayout(this);//главное окно
    QHBoxLayout *HorizontalGrid=new QHBoxLayout();//окно для кнопок

    QFont font("Times", 16);

    input=new QLabel("",this);//окно вывода результата
    input->setFont(font);
    input->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    input->setFrameShape(QFrame::Panel);


    VerticalGrid->addWidget(input);

    output=new QLabel("",this);//окно вывода результата
    output->setFont(font);
    output->setAlignment(Qt::AlignLeft | Qt::AlignCenter);
    output->setFrameShape(QFrame::Panel);


    VerticalGrid->addWidget(output);

    QGridLayout *numberGrid=new QGridLayout();//окно с цифрами

    for(int i=0;i<numbers.size();i++)
    {
        QPushButton *numberButton=new QPushButton(numbers[i],this);
        numberButton->setFont(font);
        numberGrid->addWidget(numberButton,i/3,i%3);
        connect(numberButton, &QPushButton::clicked, this, &Widget::onButton);
    }

    QPushButton *FractionalButton=new QPushButton(".",this);
    FractionalButton->setFont(font);
    numberGrid->addWidget(FractionalButton);
    connect(FractionalButton, &QPushButton::clicked, this, &Widget::onButton);

    QPushButton *equallyButton=new QPushButton("=",this);
    equallyButton->setFont(font);
    numberGrid->addWidget(equallyButton);
    connect(equallyButton, &QPushButton::clicked, this, &Widget::onEqually);

    HorizontalGrid->addLayout(numberGrid);

    QGridLayout *MathGrid=new QGridLayout();//окно с математическими операциями
    for(int i=0;i<BinaryOperations.size();i++)
    {
        QPushButton *BinaryButton=new QPushButton(BinaryOperations[i],this);
        BinaryButton->setFont(font);
        MathGrid->addWidget(BinaryButton,i/4,i%4);
        connect(BinaryButton, &QPushButton::clicked, this, &Widget::onButton);
    }
    QPushButton *BracketLButton=new QPushButton("(",this);
    BracketLButton->setFont(font);
    MathGrid->addWidget(BracketLButton);
    connect(BracketLButton, &QPushButton::clicked, this, &Widget::onButton);

    QPushButton *BracketRButton=new QPushButton(")",this);
    BracketRButton->setFont(font);
    MathGrid->addWidget(BracketRButton);
    connect(BracketRButton, &QPushButton::clicked, this, &Widget::onButton);

    for(int i=0;i<UnaryOperations.size();i++)
    {
        QPushButton *UnaryButton=new QPushButton(UnaryOperations[i],this);
        UnaryButton->setFont(font);
        MathGrid->addWidget(UnaryButton,3+i/4,i%4);
        connect(UnaryButton, &QPushButton::clicked, this, &Widget::onButton);
    }
    QPushButton *ClrButton=new QPushButton("clr",this);
    ClrButton->setFont(font);
    MathGrid->addWidget(ClrButton);
    connect(ClrButton, &QPushButton::clicked, this, &Widget::onClr);

    QPushButton *DelButton=new QPushButton("del",this);
    DelButton->setFont(font);
    MathGrid->addWidget(DelButton);
    connect(DelButton, &QPushButton::clicked, this, &Widget::onDel);

    HorizontalGrid->addLayout(MathGrid);

    VerticalGrid->addLayout(HorizontalGrid);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onButton()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());//узнаем, какую кнопку нажали
    input->setText(input->text()+clickedButton->text());
}

void Widget::onEqually()
{
    calculator.warning="";
    std::string result=calculator.calculated(input->text().toStdString());
    if(calculator.warning=="")
    output->setText(QString::fromUtf8(result.c_str()));
    else output->setText(QString::fromUtf8(calculator.warning.c_str()));
}

void Widget::onClr()
{
    input->setText("");
    output->setText("");
}

void Widget::onDel()
{
    output->setText("");
    QString s=input->text().left(input->text().length()-1);
    input->setText(s);
}
