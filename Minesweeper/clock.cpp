#include "clock.h"

Clock::Clock(QWidget* parent) : QLCDNumber(parent)
{
    setSegmentStyle(QLCDNumber::Flat);
    this->display("0");
    setStyleSheet("background-color: #3e432e; color: #a7d129;");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Clock::showTime);
    time=0;

}

void Clock::startTimer()
{
    timer->start(1000);
}

void Clock::stopTimer()
{
    timer->stop();
}

void Clock::showTime()
{
    display(++time);
}

void Clock::restart()
{
    time=0;
    display(time);
}

