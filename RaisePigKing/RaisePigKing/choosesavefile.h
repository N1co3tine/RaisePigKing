#ifndef CHOOSESAVEFILE_H
#define CHOOSESAVEFILE_H

#include <QWidget>

class ChooseSaveFile : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseSaveFile(QWidget *parent = nullptr);
    QString currentStr,currentStr2;

signals:
    void raise1back();
};

#endif // CHOOSESAVEFILE_H
