#include "pigsystem.h"
Pigsystem::Pigsystem()
{
}

void Pigsystem::distribute(Pig *pig){
    static int index = 0;    //放猪的项数
    //enclosure[dnum].addPig(pig);
    //dnum++;
    //if (dnum > 99) dnum = 0;

    //黑猪圈体系：没有白猪才能进
    pig->isIll=0;
    if (pig->getType() == Black)
    {
        int times = 0;
        while ((enclosure[index].isBlack == 0 && enclosure[index].num)|| enclosure[index].num == 10){
            index++;
            times++;
            if(index == 100) index = 0;
            if(times > 100) return; //猪圈已满散了吧
        }
        enclosure[index].addPig(pig);
        //黑猪集中放到一个圈子，避免混杂
    }
    else
    {
        int times = 0;
        while (enclosure[index].isBlack == 1 || enclosure[index].num == 10){
            index++;
            if(index == 100) index = 0;
            if(times > 100) return ;
        }//找到白猪圈使其均匀分布
        enclosure[index].addPig(pig);
    }
    index++;
    if(index == 100) index = 0;
}

void Pigsystem:: fatter(){
    for(int i=0;i<100;i++){
        if (enclosure[i].num){
            enclosure[i].fatter();
        }
    }
}

double Pigsystem::earnMoney(){
    double ret = 0;
    for(int i=0;i<100;i++){
        if (enclosure[i].num)
            ret += enclosure[i].findpig();
    }
    return ret;

}
