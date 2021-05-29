#include "raisepig1.h"
#include <qtimer.h>
#include <test.cpp>
#include <QLabel>
#include <qpainter.h>
#include <qdialog.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <querytable.h>
#include <QMenuBar>
#include <QVBoxLayout>
#include <qlist.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <choosesavefile.h>
#include <QTime>
#include <mybutton.h>


Raisepig1::Raisepig1(Pigsystem * ps, QListWidget *sellList)
{
    this->setWindowTitle("养猪之神");
    this->setAutoFillBackground(true);

    QFont font;
    font.setFamily("华文琥珀");
    font.setPointSize(15);

    //1.养猪系统的创立

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);

    QLabel *numText = new QLabel(this);
    numText -> move(350,40);
    numText->setFixedSize(180,50);
    numText->setText("下一次要什么猪？");
    numText->setFont(font);
    numText->setPalette(pe);

    MyButton *chooseRandom = new MyButton(":/res/red1.png",100,80,":/res/red2.png");
    chooseRandom->setParent(this);
    chooseRandom->move(440,220);

    QLabel * randomText = new QLabel;
    randomText->setParent(chooseRandom);
    randomText->setFixedSize(100,80);
    randomText->setText("随机生成");
    randomText->setFont(font);
    randomText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    randomText->setStyleSheet("color: white");

    MyButton *chooseSet = new MyButton(":/res/blue1.png",100,80,":/res/blue2.png");
    chooseSet->move(340,220);
    chooseSet->setParent(this);

    QLabel * setText = new QLabel;
    setText->setParent(chooseSet);
    setText->setFixedSize(100,80);
    setText->setText("手动生成");
    setText->setFont(font);
    setText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setText->setStyleSheet("color: white");

    QLabel *blackNumText = new QLabel(this);
    blackNumText->move(350,90);
    blackNumText->setFixedSize(80,30);
    blackNumText->setText("黑猪：");
    blackNumText->setFont(font);
    blackNumText->setPalette(pe);

    QLabel *smallNumText = new QLabel(this);
    smallNumText->move(350,140);
    smallNumText->setFixedSize(80,30);
    smallNumText->setText("小花猪：");
    smallNumText->setFont(font);
    smallNumText->setPalette(pe);

    QLabel *bigNumText = new QLabel(this);
    bigNumText->move(350,190);
    bigNumText->setFixedSize(80,30);
    bigNumText->setText("大白花猪：");
    bigNumText->setFont(font);
    bigNumText->setPalette(pe);

    blackSet = new QSpinBox(this);
    blackSet->move(460,100);

    smallSet = new QSpinBox(this);
    smallSet->move(460,150);

    bigSet = new QSpinBox(this);
    bigSet->move(460,200);

    isRandom = 1;
    smallNum = 0;
    bigNum = 0;
    blackNum = 0;

    connect(chooseRandom, &QPushButton::clicked, [=](){
        this->isRandom = 1;
        QTimer::singleShot(500,this,[=](){
            QMessageBox mesg;
            mesg.information(this,"养猪之神","已设置为随机，下次生效");
        });

    });

    connect(chooseSet, &QPushButton::clicked, [=](){
        this->isRandom = 0;
        this->blackNum = blackSet->value();
        this->bigNum = bigSet->value();
        this->smallNum = smallSet->value();
        QTimer::singleShot(500,this,[=](){
            QMessageBox mesg;
            mesg.information(this,"养猪之神","已设置为手动，下次生效");
        });
    });

    //2.随机，手动选猪系统

    timer = new QTimer(this);
    sellTimer = new QTimer(this);

    timer->start(1000);
    //sellTimer->start(5000);
    //计时器：增肥计时器，卖猪计时器

    sellList->setParent(this);
    sellList ->move(50,100);

    connect(timer, &QTimer::timeout,[=](){
        static int sec =0;
        sec++;
        ps->fatter();
        if (sec == 90){
            sec = 0;
            QString str = QString("本次售出%1元").arg(ps->earnMoney());
            QListWidgetItem * item = new QListWidgetItem(str);
            sellList->addItem(item);

            if (isRandom == 1){
                for(int i=0;i<50;i++)
                    ps->distribute(new Pig);
                QString str = QString("随机购入50头猪");
                QListWidgetItem * item = new QListWidgetItem(str);
                sellList->addItem(item);

            }
            else{
                for(int i=0;i<blackNum;i++)
                    ps->distribute(new Pig(Black));
                for(int i=0;i<bigNum;i++)
                    ps->distribute(new Pig(BigFlowerWhite));
                for(int i=0;i<smallNum;i++)
                    ps->distribute(new Pig(SmallFlower));

                QString str = QString("购入黑猪%1头，小花猪%2头，大白花柱%3头").arg(this->blackNum).arg(this->smallNum).arg(this->bigNum);
                QListWidgetItem * item = new QListWidgetItem(str);
                sellList->addItem(item);
            }
        }
    });

    label2 = new QLabel(this);
    label2 -> move(50,40);
    label2->setFixedSize(100,80);
    label2->setText("买卖记录");
    label2->setFont(font);
    label2->setPalette(pe);

    //3.增肥,买卖功能




    this->setFixedSize(600,500);

    label1 = new QLabel;
    label1->setParent(this);
    label1->move(width()*0.6,height()*0.6);
    label1->setText("输入圈号：");
    label1->setFont(font);
    label1->setPalette(pe);

    spin = new QSpinBox;
    spin->setParent(this);
    spin->move(width()*0.75,height()*0.6);

    MyButton* toEnclosure = new MyButton(":/res/button3.png",160,80,":/res/button2.png");
    toEnclosure->setParent(this);
    toEnclosure->move(width()*0.75, height()*0.7);

    QLabel * encText = new QLabel;
    encText->setParent(toEnclosure);
    encText->setFixedSize(160,80);
    encText->setText("我要进去康康");
    encText->setFont(font);
    encText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    encText->setStyleSheet("color: white");

    connect(toEnclosure,&QPushButton::clicked,[=](){
        Enclosure ce = ps->enclosure[spin->value()];
        inenclo = new InEnclosure(&ce);
        QTimer::singleShot(500,this,[=](){
            this->hide();
            inenclo->show();
        });

        connect(inenclo,&InEnclosure::raise1back,[=](){
            this->show();
            delete inenclo;
        });
    });
    //4.到猪圈看看系统

    chooseType = new QComboBox(this);
    chooseType->move(40,330);
    QStringList list;
    list <<"黑猪"<<"小花猪"<<"大花白猪";
    chooseType->addItems(list);

    chooseTable = new QComboBox(this);
    QStringList list2;
    list2 <<"体重"<<"饲养时间";
    chooseTable->addItems(list2);
    chooseTable->move(140,330);

    MyButton * toTable = new MyButton(":/res/button.png",120,80,":/res/button1.png");
    toTable->setParent(this);
    toTable->move(220,300);
    toTable->setFixedSize(120,80);

    QLabel * tableText = new QLabel;
    tableText->setParent(toTable);
    tableText->setFixedSize(120,80);
    tableText->setText("查询");
    tableText->setFont(font);
    tableText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    tableText->setStyleSheet("color: white");

    connect(toTable,&QPushButton::clicked,[=](){
        QString str = QString("%1 %2").arg(chooseType->currentIndex()).arg(chooseTable->currentIndex());
        //qDebug() << str;
        query = new queryTable(ps,chooseType->currentIndex(), chooseTable->currentIndex());

        QTimer::singleShot(500,this,[=](){
            query ->show();
            this ->hide();
        });

        connect(query, &queryTable::raiseback, [=](){
            this->show();
            query->~queryTable();
        });
    });

    //5.查询系统

    MyButton * saveRecord = new MyButton(":/res/button3.png",100,80,":/res/button2.png");
    saveRecord->setParent(this);
    saveRecord->move(220,40);
    saveRecord->setFixedSize(100,80);

    QLabel * recordText = new QLabel;
    recordText->setParent(saveRecord);
    recordText->setFixedSize(100,80);
    recordText->setText("保存记录");
    recordText->setFont(font);
    recordText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    recordText->setStyleSheet("color: white");

    connect(saveRecord, &QPushButton::clicked, [=](){
            QString path = QFileDialog::getSaveFileName(this,"保存记录文件","D:\\qt");
            try {
                if(path.isEmpty()) throw 1;
                QFile file(path);
                if(!file.open(QIODevice::Append)) throw 1;
                QString str ="";
                for(int i=0;i<sellList->count();i++){
                    str += sellList->item(i)->text()+'\n';
                }

                file.write(str.toUtf8());

                file.close();
                QMessageBox mesg;
                mesg.information(this,"养猪之神","保存记录文件成功");

            }
            catch (int) {
                QMessageBox mesg;
                mesg.warning(this,"养猪之神","保存失败！");
            }


    });

    //6.保存买卖记录

    MyButton * saveData = new MyButton(":/res/button3.png",100,80,":/res/button2.png");
    saveData->setParent(this);
    saveData->move(0,0);
    saveData->setFixedSize(100,80);

    QLabel * saveText = new QLabel;
    saveText->setParent(saveData);
    saveText->setFixedSize(100,80);
    saveText->setText("保存数据");
    saveText->setFont(font);
    saveText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //butText->setPalette(pe);
    saveText->setStyleSheet("color: white");


    chooseFile = new ChooseSaveFile();

    connect(saveData, &QPushButton::clicked,[=](){
            QTimer::singleShot(500,this,[=](){
                chooseFile->show();
                this->hide();
            });
    });

    connect(chooseFile,&ChooseSaveFile::raise1back, [=](){
        this->show();
        QString path = chooseFile->currentStr;
        QString path2 = chooseFile->currentStr2;

        try {
            if(path.isEmpty()) throw 1;
            QFile file(path);
            if(!file.open(QIODevice::WriteOnly)) throw 2;

            QDataStream stream(&file);
            stream.setByteOrder(QDataStream::LittleEndian);

            for(int i=0;i<100;i++){
                Pig * cpig = ps->enclosure[i].firstpig;


                while(cpig){
                    int age = cpig->showAge();
                    type t = cpig->getType();
                    float weight = cpig->showWeight();
                    stream.writeRawData((char *)&i,sizeof(int));
                    stream.writeRawData((char *)&age,sizeof(int));
                    stream.writeRawData((char *)&t,sizeof(type));
                    stream.writeRawData((char *)&weight,sizeof(float));
                    cpig = cpig->showNext();
                }
            }

            file.close();

            if(path2.isEmpty()) throw 3;
            QFile file2(path2);
            if(!file2.open(QIODevice::WriteOnly)) throw 4;
            QString str ="";
            for(int i=0;i<sellList->count();i++){
                str += sellList->item(i)->text()+'\n';
            }

            file2.write(str.toUtf8());

            file2.close();


            QMessageBox mesg;
            mesg.information(this,"养猪之神","保存数据成功");

        }
        catch (int i) {
            QMessageBox mesg;
            mesg.warning(this,"养猪之神","保存失败！");
            qDebug()<<QString("%1").arg(i);
        }

    });
    //7.保存当前数据

    MyButton *startIll = new MyButton(":/res/button3.png",140,80,":/res/button2.png");
    startIll->setParent(this);
    startIll->move(0.05*this->width(), 0.85*this->height());

    QLabel * illLabel = new QLabel(startIll);
    illLabel->setFixedSize(140,80);
    illLabel->setText("开始模拟瘟疫");
    illLabel->setFont(font);
    illLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    illLabel->setStyleSheet("color: white");



    MyButton *startAnti = new MyButton(":/res/button3.png",100,80,":/res/button2.png");
    startAnti->setParent(this);
    startAnti->move(0.8*width(), 0.85*this->height());
    startAnti->setFixedSize(100,80);
    startAnti->hide();

    QLabel * antiLabel = new QLabel(startAnti);
    antiLabel->setFixedSize(100,80);
    antiLabel->setText("开始隔离");
    antiLabel->setFont(font);
    antiLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    antiLabel->setStyleSheet("color: white");

    QLabel * illText = new QLabel(this);
    illText->move(0.3*this->width(), 0.9*this->height());
    illText->setFixedSize(250,30);
    illText->setText("没有发生瘟疫");
    illText->setFont(font);
    pe.setColor(QPalette::WindowText,QColor(135,206,235));
    illText->setPalette(pe);

    QTimer *illTimer = new QTimer(this);

    connect(startIll, &QPushButton::clicked, [=](){
//        QTimer::singleShot(500,this,[=](){
//                        startAnti->show();
//        });

        startAnti->show();

        illTimer->start(1000);
        for(int i=0;i<100;i++){
            Pig * cpig =ps->enclosure[i].firstpig;
            while(cpig){
                cpig->isIll = 0;
                cpig = cpig->showNext();
            }
        }
        int seed = QTime(0,0,0).secsTo(QTime::currentTime());
        qsrand(seed);
        while(ps->enclosure[qrand()%100].firstpig){
            qDebug()<<QString("%1").arg(qrand()%100);
            ps->enclosure[qrand()%100].firstpig->isIll=1;
            break;
        }
        //瘟疫初始化

        connect(startAnti, &QPushButton::clicked, [=](){
            illCount = 0;
            allCount = 0;
            illTimer->stop();

            int saveCount;

            for(int i=0;i<100;i++){
                Pig * cpig = ps->enclosure[i].firstpig;

                while(cpig){
                    if(cpig->isIll) illCount++;
                    allCount++;
                    cpig=cpig->showNext();
                }
            }

            saveCount = allCount-illCount;
            if(allCount>970){
                int maxCount =  (100-(illCount-1)/10)*10;
                //计算出隔离病猪后猪圈能承受的健康猪
                if(saveCount > maxCount)
                    saveCount = maxCount;
            }

            QDialog *situation= new QDialog(this);
            situation->setFixedSize(200,200);
            situation->setAttribute(Qt::WA_DeleteOnClose);


            QLabel *label = new QLabel(situation);
            label->move(0,0);
            label->setFixedSize(180,150);
            QString str = QString("你保住了%1只猪\n,这次疫情存活率为%2%").arg(saveCount).arg(float(saveCount)/allCount*100);
            label->setText(str);
            situation->show();

            QPushButton *back2 = new QPushButton(situation);
            back2->setFixedSize(80,60);
            back2->move(100,100);
            back2->setText("朕知道了");
            back2->show();

            connect(back2,&QPushButton::clicked,[=](){
                situation->close();
            });


            illText->setText("隔离成功！");
            QTimer::singleShot(500,this,[=](){
                startAnti->hide();
            });
            //隔离操作
        });

        connect(illTimer,&QTimer::timeout, [=](){
            int illedEclo = 0;
            int isIll[100]{0};
            bool die = 1;

            for(int i=0;i<100;i++){
                Pig * cpig = ps->enclosure[i].firstpig;
                bool flag = 0;

                while(cpig){
                    if(cpig->isIll==1) {
                        flag = 1; isIll[i]=1;
                        illedEclo ++;
                        break;
                    }
                    else
                        die = 0;
                    cpig=cpig->showNext();
                }
                if(!flag) isIll[i]=0;
            }
            //寻找有毒猪圈
            QString str = QString("现在有%1个猪圈被感染了！").arg(illedEclo);
            illText->setText(str);

            if (die){
                str = QString("模拟情况下猪死光了！");
                startAnti->hide();
                illText->setText(str);
                illTimer->stop();
            }

            for(int i=0;i<100;i++){
                if(isIll[i] == 1){
                    Pig * cpig = ps->enclosure[i].firstpig;
                    while(cpig){
                        if(cpig->isIll==0){
                            int seed = QTime(0,0,0).secsTo(QTime::currentTime());
                            qsrand(seed);
                            if(qrand()%100<50)
                                cpig->isIll=1;
                        }
                        cpig=cpig->showNext();
                    }
                }
                else if(i==0 && isIll[1]==1){
                    Pig * cpig = ps->enclosure[i].firstpig;
                    while(cpig){
                        if(cpig->isIll==0){
                            int seed = QTime(0,0,0).secsTo(QTime::currentTime());
                            qsrand(seed);
                            if(qrand()%100<15)
                                cpig->isIll=1;
                        }
                        cpig=cpig->showNext();
                    }
                }
                else if(i==99 && isIll[98]==1){
                    Pig * cpig = ps->enclosure[i].firstpig;
                    while(cpig){
                        if(cpig->isIll==0){
                            int seed = QTime(0,0,0).secsTo(QTime::currentTime());
                            qsrand(seed);
                            if(qrand()%100<15)
                                cpig->isIll=1;
                        }
                        cpig=cpig->showNext();
                    }
                }
                else if(isIll[i+1]==1 || isIll[i-1]==1){
                    Pig * cpig = ps->enclosure[i].firstpig;
                    //qDebug()<<"thhte";
                    while(cpig){
                        if(cpig->isIll==0){
                            int seed = QTime(0,0,0).secsTo(QTime::currentTime());
                            qsrand(seed);
                            if(qrand()%100<15)
                                cpig->isIll=1;
                        }
                        cpig=cpig->showNext();
                    }
                }

            }

        });

    });

    //8.疫情模拟
}

void Raisepig1::paintEvent(QPaintEvent *){
    //背景图片的设置
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background1.jfif");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/blank1.jpg");
    painter.drawPixmap(0,0.85*this->height(),this->width(),0.3*this->height(),pix);

}
