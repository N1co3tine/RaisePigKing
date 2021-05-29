#include "querytable.h"
#include <pigsystem.h>
#include <pig.h>
#include <enclosure.h>
#include <qdebug.h>
#include <qbarseries.h>
#include <qbarset.h>
#include <qchart.h>
#include <qbarcategoryaxis.h>
#include <qchartview.h>
#include <qpushbutton.h>

using namespace QtCharts;

queryTable::queryTable(Pigsystem * ps, int type, int method)
{
    setWindowTitle("数据查询");
    setFixedSize(600,500);

    QPushButton * back = new QPushButton(this);
    back->setFixedSize(80,40);
    back->move(500,420);
    back->setText("有点东西");

    connect(back, &QPushButton::clicked, [=](){
      emit raiseback();
    });

    if (type == 0) currentType = Black;
    if (type == 1) currentType = SmallFlower;
    if (type == 2) currentType = BigFlowerWhite;

    if (method == 0){
        int weight[8]={0};
        for(int i=0;i<100;i++){
            Pig* cpig = ps->enclosure[i].firstpig;
            while(cpig){
                if(cpig->getType() != currentType) break;
                if(cpig->showWeight()>=20 && cpig->showWeight()<40) weight[0]+=1;
                else if(cpig->showWeight()>=40 && cpig->showWeight()<60) weight[1]+=1;
                else if(cpig->showWeight()>=60 && cpig->showWeight()<80) weight[2]+=1;
                else if(cpig->showWeight()>=80 && cpig->showWeight()<100) weight[3]+=1;
                else if(cpig->showWeight()>=100 && cpig->showWeight()<120) weight[4]+=1;
                else if(cpig->showWeight()>=120 && cpig->showWeight()<140) weight[5]+=1;
                else if(cpig->showWeight()>=140 && cpig->showWeight()<160) weight[6]+=1;
                else if(cpig->showWeight()>=160) weight[7]+=1;
                cpig = cpig->showNext();
            }
        }
        //数据获取

        QBarSeries * series = new QBarSeries();
        QString str;
        if (type == 0) str="黑猪";
        if (type == 1) str="小花猪";
        if (type == 2) str="大花白猪";
        QBarSet *set0 = new QBarSet(str);

        for(int i=0;i<8;i++)
            *set0 << weight[i];
        //查询集合的设置

        series->append(set0);

        QChart * chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("体重分布");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList categories;
        categories << "20-40" << "40-60"<< "60-80"<< "80-100"<< "100-120"<< "120-140"
                   << "140-160"<< "160+";

        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView = new QChartView(chart,this);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(600,400);
    }

    //体重的查询

    if (method == 1){
        int age[7]={0};
        for(int i=0;i<100;i++){
            Pig* cpig = ps->enclosure[i].firstpig;
            while(cpig){
                if(cpig->getType() != currentType) break;
                if(cpig->showAge()>=0 && cpig->showWeight()<60) age[0]+=1;
                else if(cpig->showWeight()>=60 && cpig->showWeight()<120) age[1]+=1;
                else if(cpig->showWeight()>=120 && cpig->showWeight()<180) age[2]+=1;
                else if(cpig->showWeight()>=180 && cpig->showWeight()<240) age[3]+=1;
                else if(cpig->showWeight()>=240 && cpig->showWeight()<300) age[4]+=1;
                else if(cpig->showWeight()>=300 && cpig->showWeight()<360) age[5]+=1;
                else if(cpig->showWeight()>=360) age[6]+=1;
                cpig = cpig->showNext();
            }
        }
        //数据获取

        QBarSeries * series = new QBarSeries();
        QString str;
        if (type == 0) str="黑猪";
        if (type == 1) str="小花猪";
        if (type == 2) str="大花白猪";
        QBarSet *set0 = new QBarSet(str);

        for(int i=0;i<7;i++)
            *set0 << age[i];
        //查询集合的设置

        series->append(set0);

        QChart * chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("饲养实际分布");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList categories;
        categories << "1-2月" << "3-4月"<< "5-6月"<< "7-8月"
                   << "9-10月"<< "10-11月"<< "12月以上";

        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView = new QChartView(chart,this);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(600,400);
    }
    //饲养时间的查询
}
