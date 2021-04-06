#include "flagcounter.h"

FlagCounter::FlagCounter(QWidget* parent) : QLCDNumber(parent) {
    setSegmentStyle(QLCDNumber::Flat);
    setStyleSheet("background-color: #3e432e; color: #a7d129;");
}

void FlagCounter::showBombs(int newValue)
{
    setValue(newValue);
    display(value);
}

int FlagCounter::getValue() const
{
    return value;
}

void FlagCounter::setValue(int newValue)
{
    this->value = newValue;
}
