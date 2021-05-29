#include "setnumberscene.h"
#include <qpushbutton.h>
#include <qlabel.h>
#include <qspinbox.h>


SetNumberScene::SetNumberScene(QWidget *parent) : QWidget(parent)
{
    setFixedSize(400,300);
    QPushButton *chooseRandom = new QPushButton(this);
    chooseRandom->move(170,220);
    chooseRandom->setFixedSize(80,30);
    chooseRandom->setText("随机生成");

    QPushButton *chooseSet = new QPushButton(this);
    chooseSet->move(70,220);
    chooseSet->setFixedSize(80,30);
    chooseSet->setText("手动生成");

    QLabel *blackNum = new QLabel(this);
    blackNum->move(50,20);
    blackNum->setFixedSize(80,30);
    blackNum->setText("黑猪：");

    QLabel *smallNum = new QLabel(this);
    smallNum->move(50,70);
    smallNum->setFixedSize(80,30);
    smallNum->setText("小花猪：");

    QLabel *bigNum = new QLabel(this);
    bigNum->move(50,120);
    bigNum->setFixedSize(80,30);
    bigNum->setText("大白花猪：");

    blackSet = new QSpinBox(this);
    blackSet->move(150,20);

    smallSet = new QSpinBox(this);
    smallSet->move(150,70);

    bigSet = new QSpinBox(this);
    bigSet->move(150,120);

    connect(chooseRandom, &QPushButton::clicked, [=](){
        //emit setRandom();
        //返回随机信号，让养猪场景随机生成猪
        emit exit();

    });

    connect(chooseSet, &QPushButton::clicked, [=](){
        emit exit();
    });

}
