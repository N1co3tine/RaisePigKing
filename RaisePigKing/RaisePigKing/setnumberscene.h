#ifndef SETNUMBERSCENE_H
#define SETNUMBERSCENE_H

#include <QWidget>
#include <qspinbox.h>

class SetNumberScene : public QWidget
{
    Q_OBJECT
public:
    explicit SetNumberScene(QWidget *parent = nullptr);

    QSpinBox *smallSet,*blackSet,*bigSet;

signals:
    void exit();
    void setRandom();
};

#endif // SETNUMBERSCENE_H
