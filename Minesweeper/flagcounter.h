#ifndef FLAGCOUNTER_H
#define FLAGCOUNTER_H

#include <QLCDNumber>

class FlagCounter : public QLCDNumber
{
    //making a ponel which shows that how many flag you can use
public:
    FlagCounter(QWidget* parent=nullptr);
    void setValue(int value);
    int getValue() const;

public slots:
    void showBombs(int);

signals:

private:
    int value;
};

#endif // FLAGCOUNTER_H
