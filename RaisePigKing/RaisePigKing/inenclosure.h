#ifndef INENCLOSURE_H
#define INENCLOSURE_H

#include <QWidget>
#include <qpushbutton.h>
#include <qlabel.h>
#include <enclosure.h>
#include <pig.h>

class InEnclosure : public QWidget
{
    Q_OBJECT
public:
    //explicit InEnclosure(QWidget *parent = nullptr);

    InEnclosure(Enclosure *e);
    QPushButton * btn;
    void paintEvent(QPaintEvent *event);
    type pigtype[10];
    int pigage[10];
    float pigweight[10];
signals:
    void raise1back();
};

#endif // INENCLOSURE_H
