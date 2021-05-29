#include "inenclosure.h"
#include <raisepig1.h>
#include <pigsystem.h>
#include <pig.h>
#include <inenclosure.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qpainter.h>
#include <QDebug>
#include <qtimer.h>
#include <qdialog.h>
#include <mybutton.h>

QString showType(type t){
    if (t == Black) return "黑猪";
    if (t == BigFlowerWhite) return "大花白猪";
    if (t == SmallFlower) return "小花猪";
    return "";
}

InEnclosure::InEnclosure(Enclosure *e)
{
    QFont font;
    font.setFamily("华文琥珀");
    font.setPointSize(15);

    this->setWindowTitle("欢迎来到猪圈");

    Pig * cpig = e->firstpig;
    for(int i=0;i<e->num;i++) {
        pigtype[i] = cpig->getType();
        pigage[i] = cpig->showAge();
        pigweight[i] = cpig->showWeight();
        cpig = cpig->showNext();
    }

    for(int i=0;i<e->num;i++){
        btn = new QPushButton(this);
        btn->setFixedSize(120,100);
        btn->move(i%5*150+20,i/5*120+20);
        QPixmap pix;

        if (pigtype[i] == Black)
            pix.load(":/res/blackpig.png");
        else if(pigtype[i] == SmallFlower)
            pix.load(":/res/smallflower.png");
        else if(pigtype[i] == BigFlowerWhite)
            pix.load(":/res/bigflower (1).png");

        btn->setStyleSheet("QPushButton{border:0px}");

        btn->setIcon(pix);

        btn->setIconSize(QSize(120,100));
        //可视化
        connect(btn,&QPushButton::clicked,[=](){
            QDialog *situation= new QDialog(this);
            situation->setFixedSize(200,200);
            situation->setAttribute(Qt::WA_DeleteOnClose);


            QLabel *label = new QLabel(situation);
            label->move(0,0);
            label->setFixedSize(100,100);
            QString str = QString("报告老板：\n这是%1\n体重%2公斤\n年龄%3天").arg(showType(pigtype[i]))
                    .arg(pigweight[i]).arg(pigage[i]);
            label->setText(str);
            situation->show();

            QPushButton *back2 = new QPushButton(situation);
            back2->setFixedSize(80,60);
            back2->move(100,100);
            back2->setText("朕知道了");
            back2->show();

            connect(back2,&QPushButton::clicked,[=](){
                situation->close();
            });
        });

        btn->installEventFilter(this);
        //安装事件过滤器

        //connect(btn, &QPushButton::)

//        QString str = QString("%1").arg(cpig->showType());
//        label->setText(str);
    }

    this->setFixedSize(800,600);

    MyButton* back = new MyButton(":/res/button3.png",120,80,":/res/button2.png");
    back->setParent(this);
    back->move(this->width()-160,this->height()-80);

    QLabel * backText = new QLabel;
    backText->setParent(back);
    backText->setFixedSize(120,80);
    backText->setText("我要回去");
    backText->setFont(font);
    backText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    backText->setStyleSheet("color: white");

    connect(back,&QPushButton::clicked,[=](){
       QTimer::singleShot(500,this,[=](){
            emit raise1back();
       });
    });
}

void InEnclosure::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/Background2.jfif");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
