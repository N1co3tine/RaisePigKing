#include <pig.h>
#include <qdebug.h>
#include <qstring.h>
#include <enclosure.h>
#include <pigsystem.h>

void debugPig(Pig* pig1){
    QString str1 = QString("体重：%1").arg(pig1->showWeight());
    QString str2 = QString("饲养时间：%1").arg(pig1->showAge());
    qDebug() << str1 << str2 << pig1->showType();
}

void debugEnclosure(Enclosure e){
    Pig * c = e.firstpig;
    while(c){
        debugPig(c);
        c = c->showNext();
    }
}

void debugEnclosure(Enclosure *e){
    Pig * c = e->firstpig;
    while(c){
        debugPig(c);
        c = c->showNext();
    }
}

void debugPigsystem(Pigsystem p){
    for(int i=0;i<100;i++){
            QString str = QString("这是 %1 号卷：").arg(i);
            qDebug() << str;
            debugEnclosure(p.enclosure[i]);
    }
}

void debugPigsystem(Pigsystem *p){
    for(int i=0;i<100;i++){
            if (p->enclosure[i].num == 0) continue;
            QString str = QString("这是 %1 号卷：").arg(i);
            qDebug() << str;
            debugEnclosure(p->enclosure[i]);
    }
}
