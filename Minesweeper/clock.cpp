#include "clock.h"

Clock::Clock()
{
    setSegmentStyle(Filled);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Clock::showTime);
    timer->start(20);
    time=new QTime(0,0,0,0);

    showTime();
}
void Clock::showTime()
{
   QString text = time->toString("mm:ss");
   display(text);
   *time = time->addMSecs(25);
}

void Clock::restart()
{
    time=new QTime(0,0,0,0);
    timer->start();
}

void Clock::setTime(QTime *value)
{
    time = value;
}

QTime *Clock::getTime() const
{
    return time;
}

QTimer *Clock::getTimer() const
{
    return timer;
}
