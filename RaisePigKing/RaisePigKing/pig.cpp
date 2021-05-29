#include "pig.h"
#include <QTime>

Pig::Pig()
{
    age = 0;

    //体重，种类的随机实现
    static int seed = QTime(0,0,0).secsTo(QTime::currentTime());
    seed += 1;
    qsrand(seed);
    weight = qrand()%30 + 20;

    pigType = (type)(qrand()%3);
}

Pig::Pig(type t){
    age = 0;

    //体重，种类的随机实现
    static int seed = QTime(0,0,0).secsTo(QTime::currentTime());
    seed += 1;
    qsrand(seed);
    weight = qrand()%30 + 20;

    pigType = t;

}

Pig::Pig(int a, type t, float w){
    age = a;
    weight = w;
    pigType = t;
}

float Pig::showWeight(){
    return weight;
}

int Pig::showAge(){
    return age;
}

QString Pig::showType(){
    if (pigType == Black) return "黑猪";
    if (pigType == BigFlowerWhite) return "大花白猪";
    if (pigType == SmallFlower) return "小花猪";
    return "";
}

void Pig::getNext(Pig * ptr){
    next = ptr;
}

Pig* Pig::showNext(){
    return next;
}

type Pig::getType(){
    return pigType;
}

void Pig::fatter(){
    static int seed = QTime(0,0,0).secsTo(QTime::currentTime());
    seed += 1;
    qsrand(seed);

    weight += qrand () %13 * 0.1;

    age += 1;
}
