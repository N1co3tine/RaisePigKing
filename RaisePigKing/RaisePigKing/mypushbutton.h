#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <qpushbutton.h>
#include <QWidget>
#include <qlabel.h>
#include <qtooltip.h>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);

    void enterEvent(QEvent *e);

    void leaveEvent(QEvent *e);

   QToolTip * tip;

signals:

};

#endif // MYPUSHBUTTON_H
