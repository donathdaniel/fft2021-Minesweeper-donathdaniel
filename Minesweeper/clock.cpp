#include "clock.h"

Clock::Clock(QWidget* parent) : QLCDNumber(parent)
{
    setSegmentStyle(QLCDNumber::Flat);
    this->display("000");
    setStyleSheet("background-color: #3e432e; color: #a7d129;");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Clock::showTime);
    time=new QTime(0,0,0,0);

}

void Clock::startTimer()
{
    timer->start(1000);
}

void Clock::stoptTimer()
{
    timer->stop();
}

void Clock::showTime()
{
    QString text = time->toString("ss");
    display(text);
    *time = time->addMSecs(1000);
}

void Clock::restart()
{
    time=new QTime(0,0,0,0);
    startTimer();
}

QTime *Clock::getTime() const
{
    return time;
}

