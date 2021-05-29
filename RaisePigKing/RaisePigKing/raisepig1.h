#ifndef RAISEPIG1_H
#define RAISEPIG1_H

#include <QWidget>
#include <qlabel.h>
#include <qspinbox.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <inenclosure.h>
#include <qcombobox.h>
#include <querytable.h>
#include <qmenubar.h>
#include <choosesavefile.h>

class Raisepig1 : public QWidget
{
    Q_OBJECT
public:
    Raisepig1(Pigsystem * ps,QListWidget * selllist = new QListWidget);
    InEnclosure * inenclo;
    QTimer * timer;
    QTimer * sellTimer;
    void getFat();
    QLabel * label1;
    QLabel * label2;
    QSpinBox * spin;
    QSpinBox * blackSet,*smallSet,*bigSet;
    void paintEvent(QPaintEvent *event);
    bool isRandom;
    int blackNum,smallNum,bigNum;
    QComboBox *chooseType, *chooseTable;
    queryTable * query;
    QMenuBar * menubar;
    ChooseSaveFile * chooseFile;
    int illCount,allCount;

signals:
};

#endif // RAISEPIG1_H
