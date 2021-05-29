#include "mybutton.h"
#include <qpushbutton.h>
#include <qdebug.h>

MyButton::MyButton(QString normalImg, int wid, int het, QString pressImg)
{
    this->normalImgPath = normalImg;

    this->pressImgPath = pressImg;
    QPixmap pix;
    pix.load(normalImg);
    bool ret = pix.load(normalImg);
    if(!ret)
    {
        qDebug() << "图片加载失败";
        return;
    }
    this->setFixedSize(wid,het);

    this->setStyleSheet("QPushButton{border:0px;}");

    this->setIcon(pix);

    this->setIconSize(QSize(wid,het));

}

void MyButton::mousePressEvent(QMouseEvent *e){
        if(this->pressImgPath != ""){
        QPixmap pix;
        bool ret = pix.load(pressImgPath);
        if(!ret){
            qDebug() << "图片加载失败";
            return;
        }

        //qDebug() << "图片加载成功";
        //设置图片固定大小
        this->setFixedSize( this->width(), this->height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(this->width(), this->height()));
    }

    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImgPath != ""){
        QPixmap pix;
        bool ret = pix.load(normalImgPath);
        if(!ret){
            qDebug() << "图片加载失败";
            return;
        }

        //设置图片固定大小
        this->setFixedSize( this->width(), this->height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(this->width(), this->height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
