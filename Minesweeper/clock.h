#ifndef CLOCK_H
#define CLOCK_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class Clock : public QLCDNumber
{
public:
   Clock();
   QTimer *getTimer() const;
   QTime *getTime() const;
   void setTime(QTime *value);

public slots:
   void showTime();
   void restart();

private:
   QTimer *timer;
   QTime* time;
};

#endif // CLOCK_H
