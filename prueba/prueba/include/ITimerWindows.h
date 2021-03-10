#ifndef ITIMERWINDOWS_H
#define ITIMERWINDOWS_H

#include <ITimer.h>


class ITimerWindows : public ITimer
{
public:
    ITimerWindows();
    double GetTicks();
    virtual ~ITimerWindows();

protected:

private:
};

#endif // ITIMERWINDOWS_H
