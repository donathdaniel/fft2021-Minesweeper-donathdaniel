#ifndef CLOCK_H
#define CLOCK_H

#include <QLCDNumber>
#include <QTimer>

class Clock : public QLCDNumber
{
public:
   Clock(QWidget* parent=nullptr);
   void startTimer();
   void stopTimer();

public slots:
   void showTime();
   void restart();

private:
   QTimer *timer;
   int time;
};

#endif // CLOCK_H
