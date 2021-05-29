#ifndef CHOOSELOADFILE_H
#define CHOOSELOADFILE_H

#include <QWidget>

class ChooseLoadFile : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseLoadFile(QWidget *parent = nullptr);
    QString currentStr,currentStr2;

signals:
    void toraise1();

};

#endif // CHOOSELOADFILE_H
