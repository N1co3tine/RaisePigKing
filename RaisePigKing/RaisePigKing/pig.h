#ifndef PIG_H
#define PIG_H
#include <qstring.h>

enum type {Black = 0, SmallFlower, BigFlowerWhite};

class Pig
{
    type pigType;
    int age;
    float weight;
    Pig * next = nullptr;
public:
    Pig();
    Pig(type t);
    Pig(int a, type t, float w);
    QString showType();
    type getType();
    int showAge();
    float showWeight();
    void getNext(Pig * ptr);
    Pig* showNext();
    void fatter();
    bool isIll;
};

#endif // PIG_H
