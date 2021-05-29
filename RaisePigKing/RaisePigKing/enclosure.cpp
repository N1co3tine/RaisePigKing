#include "enclosure.h"
#include "pig.h"

Enclosure::Enclosure()
{
    num = 0;
    isBlack = 0;
}

void Enclosure:: addPig(Pig * pig){
    //黑猪进入，就是黑猪圈，白猪不能进
    if (pig->getType() == Black)
        isBlack = 1;

    if(firstpig == nullptr)
    {
        firstpig = pig;
        lastpig = firstpig;
    }
    else
    {
        Pig * newPig = pig;
        lastpig->getNext(newPig);
        lastpig = newPig;
    }
    num += 1;
}

void Enclosure:: fatter(){
    Pig * cpig = firstpig;
    while(cpig){
        cpig->fatter();
        cpig = cpig->showNext();
    }
}

double Enclosure:: findpig(){
    double ret = 0;
    Pig * cpig = firstpig, * npig;
    while(cpig){
        npig = cpig->showNext();
        if (cpig->showWeight()>150||cpig->showAge()>360)
            ret += killpig(cpig);
        cpig = npig;
    }
    return ret;
}

double Enclosure::countMoney(Pig *pig){
    if(pig->getType() == Black)
    {
        return pig->showWeight()*30;
    }
    else if(pig->getType() == SmallFlower){
        return pig->showWeight()*14;
    }
    else if(pig->getType() == BigFlowerWhite){
        return pig->showWeight()*12;
    }
    return 0;
}

double Enclosure:: killpig(Pig *pig){
    double ret;
    if (firstpig == pig)
    {
        Pig * kpig = firstpig;
        firstpig = kpig->showNext();
        ret = countMoney(kpig);
        kpig->~Pig();
        delete kpig;
    }
    else
    {
        Pig * fpig = firstpig;
        while(fpig->showNext() != pig){
            fpig = fpig->showNext();
        }
        fpig->getNext(pig->showNext());
        ret = countMoney(fpig);
        delete pig;
    }
    num--;
    return ret;
}
//Enclosure::~Enclosure(){
//    Pig * cpig = firstpig,*ccpig;
//    while(cpig->showNext()){
//        ccpig = cpig->showNext();
//        delete cpig;
//        cpig = ccpig;
//    }
//}
