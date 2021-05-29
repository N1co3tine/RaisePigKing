#ifndef PIGSYSTEM_H
#define PIGSYSTEM_H
#include <enclosure.h>

class Pigsystem
{
public:
    Pigsystem();
    Enclosure enclosure[100];
    void distribute(Pig * pig);
    void fatter();
    double earnMoney();
};

#endif // PIGSYSTEM_H
