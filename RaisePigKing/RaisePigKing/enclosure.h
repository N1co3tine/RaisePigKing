#ifndef ENCLOSURE_H
#define ENCLOSURE_H
#include<pig.h>

class Enclosure
{
public:
    Enclosure();
    //~Enclosure();
    Pig * firstpig = nullptr;
    Pig * lastpig = nullptr;
    int num;
    bool isBlack;  //黑猪圈判定
    void addPig(Pig * pig);
    void fatter();
    double findpig();
    double killpig(Pig * pig);
    double countMoney(Pig * pig);
};

#endif // ENCLOSURE_H
