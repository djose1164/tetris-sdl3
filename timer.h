#ifndef TIMER_H
#define TIMER_H

#include <SDL3/SDL.h>

class Timer
{
public:
    Timer();

    void start();
    void stop();
    void pause();
    void resume();

    Uint64 ticksNS() const;

    bool started() const;
    bool paused() const;

private:
    Uint64 startTicks_;
    Uint64 pausedTicks_;

    bool paused_;
    bool started_;
};

#endif // TIMER_H
