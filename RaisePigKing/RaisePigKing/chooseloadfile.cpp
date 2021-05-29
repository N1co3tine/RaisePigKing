#include "chooseloadfile.h"
#include <qpushbutton.h>
#include <qfileinfo.h>
#include <qdatetime.h>

ChooseLoadFile::ChooseLoadFile(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("读取存档");
    this->setFixedSize(400,600);

    for(int i=1;i<5;i++){
        QPushButton * but1 = new QPushButton(this);
        but1->setFixedSize(300,60);
        but1->move(50,100*i-50);

        QString path =QString("../%1.dat").arg(i);
        QFileInfo fileinfo(path);
        QDateTime time = fileinfo.lastModified();
        QString timestr = time.toString();
        QString str = QString("存档%1              ").arg(i) + timestr;
        but1->setText(str);
        connect(but1, &QPushButton::clicked, [=](){
            currentStr = path;
            currentStr2 = QString("../%1.txt").arg(i);
            emit toraise1();
            this->hide();
        });

    }
}
