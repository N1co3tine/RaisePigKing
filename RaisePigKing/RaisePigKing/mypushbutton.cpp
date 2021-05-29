#include "mypushbutton.h"
#include <qpushbutton.h>
#include <qdebug.h>
#include <qlabel.h>
#include <qtooltip.h>

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

void MyPushButton::enterEvent(QEvent *){
    qDebug()<<"我进来了";
    tip = new QToolTip();

    tip->setFixedSize(100,100);
    tip->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    tip->show();
    tip->move(0,0);
}


void MyPushButton::leaveEvent(QEvent *){
    qDebug()<<"我出去了";
    delete  tip;

}
