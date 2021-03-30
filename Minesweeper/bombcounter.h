#ifndef BOMBCOUNTER_H
#define BOMBCOUNTER_H

#include <QLCDNumber>

class BombCounter : public QLCDNumber
{
public:
    BombCounter(int);

public slots:
    void showBombs(int);

signals:

};

#endif // BOMBCOUNTER_H
