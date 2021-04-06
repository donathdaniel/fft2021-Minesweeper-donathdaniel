#ifndef CLOCK_H
#define CLOCK_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class Clock : public QLCDNumber
{
public:
   Clock(QWidget* parent=nullptr);
   void startTimer();
   void stoptTimer();
   QTime *getTime() const;

public slots:
   void showTime();
   void restart();

private:
   QTimer *timer;
   QTime* time;
};

#endif // CLOCK_H
