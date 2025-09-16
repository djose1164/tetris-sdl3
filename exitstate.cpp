#include "exitstate.h"

ExitState::ExitState()
{
}

bool ExitState::enter()
{
    return true;
}

bool ExitState::exit()
{
    return true;
}

void ExitState::handleEvent(SDL_Event &e)
{
}

void ExitState::update(float deltatime)
{
}

void ExitState::render()
{
}

ExitState *ExitState::instance()
{
    static ExitState s;
    return &s;
}
