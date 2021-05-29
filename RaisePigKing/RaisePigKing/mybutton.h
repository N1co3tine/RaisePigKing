#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <qpushbutton.h>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyButton(QWidget *parent = nullptr);

    MyButton(QString normalImg, int wid = 100, int het = 50, QString pressImg = "");

    QString normalImgPath;
    QString pressImgPath;

    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYBUTTON_H
