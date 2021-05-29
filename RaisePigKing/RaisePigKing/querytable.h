#ifndef QUERYTABLE_H
#define QUERYTABLE_H

#include <QWidget>
#include <pigsystem.h>

class queryTable : public QWidget
{
    Q_OBJECT
public:
    queryTable(Pigsystem * ps, int type, int method);
    type currentType;

signals:
    void raiseback();

};

#endif // QUERYTABLE_H
