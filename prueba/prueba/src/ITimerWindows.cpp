#include "ITimerWindows.h"
#include <chrono>
ITimerWindows::ITimerWindows()
{
    //ctor
}

ITimerWindows::~ITimerWindows()
{
    //dtor
}
double ITimerWindows::GetTicks()
{
    typedef std::chrono::high_resolution_clock clock;
    typedef std::chrono::duration<double, std::milli> duration;

    static clock::time_point start = clock::now();
    duration elapsed = clock::now() - start;
    return elapsed.count();;
}
