#ifndef RAISEPIG2_H
#define RAISEPIG2_H

#include <QWidget>
#include <qlabel.h>
#include <qspinbox.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <inenclosure.h>
#include <qcombobox.h>
#include <querytable.h>
#include <qmenubar.h>

class Raisepig2 : public QWidget
{
    Q_OBJECT
public:
    explicit Raisepig2(QWidget *parent = nullptr);
    InEnclosure * inenclo;
    QTimer * timer;
    QTimer * sellTimer;
    void getFat();
    QLabel * label1;
    QLabel * label2;
    QSpinBox * spin;
    QSpinBox * blackSet,*smallSet,*bigSet;
    QPushButton * toEnclosure;
    QListWidget * sellList;
    void paintEvent(QPaintEvent *event);
    bool isRandom;
    int blackNum,smallNum,bigNum;
    QComboBox *chooseType, *chooseTable;
    QPushButton * toTable;
    queryTable * query;
    QMenuBar * menubar;

signals:

};

#endif // RAISEPIG2_H
