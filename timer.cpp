#include "timer.h"

Timer::Timer()
    : startTicks_{}
    , pausedTicks_{}
    , paused_{}
    , started_{}
{
}

void Timer::start()
{
    started_ = true;
    paused_ = false;

    startTicks_ = SDL_GetTicksNS();
    pausedTicks_ = 0;
}

void Timer::stop()
{
    started_ = false;
    paused_ = true;

    startTicks_ = pausedTicks_ = 0;
}

void Timer::pause()
{
    if (started_ and not paused_)
    {
        paused_ = true;

        pausedTicks_ = SDL_GetTicksNS() - startTicks_;
        startTicks_ = 0;
    }
}

void Timer::resume()
{
    if (started_ and paused_)
    {
        paused_ = false;

        startTicks_ = SDL_GetTicksNS() - pausedTicks_;
        pausedTicks_ = 0;
    }
}

Uint64 Timer::ticksNS() const
{
    Uint64 time{};
    if (not started_)
        return time;

    if (paused_)
        time = pausedTicks_;
    else
        time = SDL_GetTicksNS() - startTicks_;

    return time;
}

bool Timer::started() const
{
    return started_;
}

bool Timer::paused() const
{
    return paused_;
}
