#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <qlistwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置单选按钮 男默认选中
    ui -> radioButton -> setChecked(true);

    //选中女后 打印信息
    connect(ui->radioButton_2, &QRadioButton::clicked, [=](){
        qDebug() << "选中了女！";
    });

    //多选按钮
    connect(ui->checkBox, &QCheckBox::stateChanged,[=](int state){
        qDebug() << state;
    });

    //利用listWidget写诗
//    QListWidgetItem * item = new QListWidgetItem("李宗泽是providence");
//    //将一行诗放入
//    ui -> listWidget -> addItem(item);
//    item -> setTextAlignment(Qt::AlignHCenter);

    //QstringList QList<QString>
    QStringList list;
    list << "李宗泽" << "真牛逼" << "他的弟弟" << "都帅气";
    ui -> listWidget -> addItems(list);
}

MainWindow::~MainWindow()
{
    delete ui;
}

