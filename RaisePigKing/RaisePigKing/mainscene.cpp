#include "mainscene.h"
#include "ui_mainscene.h"
#include <pig.h>
#include <qdebug.h>
#include <qstring.h>
#include <qpushbutton.h>
#include <raisepig1.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <chooseloadfile.h>
#include <qpainter.h>
#include <qmediaplayer.h>
#include <qtimer.h>
#include <mybutton.h>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    this->setFixedSize(500,400);
    QFont font;
    font.setFamily("华文琥珀");
    font.setPointSize(15);

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);

    ui->setupUi(this);

    MyButton * but0 = new MyButton(":/res/button3.png",120,80,":/res/button2.png");
    but0->setParent(this);
    but0->move(180,50);

    QLabel * butText0 = new QLabel;
    butText0->setParent(but0);
    butText0->setFixedSize(120,80);
    butText0->setText("新的猪圈");
    butText0->setFont(font);
    butText0->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //butText0->setPalette(pe);
    butText0->setStyleSheet("color: white");

    butText0->setAttribute(Qt::WA_TransparentForMouseEvents);

    connect(but0,&QPushButton::clicked,[=](){

           Pigsystem * ps=new Pigsystem;
           for(int i=0;i<400;i++){
               ps->distribute(new Pig);
           }
           Raisepig1 * raise1 = new Raisepig1(ps);

           QTimer::singleShot(500,this,[=](){
               this->hide();
               raise1->show();
           });
    });

        QString applicationDirPath = QApplication::applicationDirPath();
        qDebug()<< "applicationDirPath:" << applicationDirPath;
        QMediaPlayer *player = new QMediaPlayer;
        //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
        player->setMedia(QUrl("qrc:/res/song.mp3"));
        player->setVolume(30);
        player->play();


    MyButton * but = new MyButton(":/res/button3.png",120,80,":/res/button2.png");
    but->setParent(this);
    but->move(180,150);

    QLabel * butText = new QLabel;
    butText->setParent(but);
    butText->setFixedSize(120,80);
    butText->setText("读取存档");
    butText->setFont(font);
    butText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //butText->setPalette(pe);
    butText->setStyleSheet("color: white");

    butText->setAttribute(Qt::WA_TransparentForMouseEvents);
    //读取存档按钮设置

    ChooseLoadFile *choosefile = new ChooseLoadFile();

    connect(but, &QPushButton::clicked, [=](){

        QTimer::singleShot(500,this,[=](){
            choosefile->show();
            this->hide();
        });

    });

    connect(choosefile, &ChooseLoadFile::toraise1, [=](){
        QString path = choosefile->currentStr;
        QString path2 = choosefile->currentStr2;
        try {
            if(path.isEmpty()) throw 1;
            QFile file(path);
            if(!file.open(QIODevice::ReadOnly)) throw 1;

            QDataStream stream(&file);
            stream.setByteOrder(QDataStream::LittleEndian);

            Pigsystem * ps = new Pigsystem;

            while(!stream.atEnd()){
                    int index;
                    int age;
                    type t;
                    float weight;
                    stream.readRawData((char *)&index,sizeof(int));
                    stream.readRawData((char *)&age,sizeof(int));
                    stream.readRawData((char *)&t,sizeof(type));
                    stream.readRawData((char *)&weight,sizeof(float));

                    ps->enclosure[index].addPig(new Pig(age,t,weight));

                    QString str = QString("%1  %2  %3  %4").arg(index).arg(age).arg(t).arg(weight);
                    //qDebug()<<str;

            }

            file.close();

            QListWidget * sellList = new QListWidget;
            if(path2.isEmpty()) throw 1;
            QFile file2(path2);
            if(!file2.open(QIODevice::ReadOnly)) throw 1;
            QTextStream in(&file2);
            in.setCodec("UTF-8");
                while(!in.atEnd())
                {
                    QString str = in.readLine();
                    //qDebug() << str;
                    QListWidgetItem * item = new QListWidgetItem(str);
                    sellList->addItem(item);
                }

            file2.close();

            QMessageBox mesg;
            mesg.information(this,"养猪之神","读取数据成功");

            Raisepig1 * raise1 = new Raisepig1(ps,sellList);
            this->hide();
            raise1->show();

        }
        catch (int) {
            QMessageBox mesg;
            mesg.warning(this,"养猪之神","读取失败！");
        }

    });

}

void MainScene::paintEvent(QPaintEvent *){
    //背景图片的设置
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}

