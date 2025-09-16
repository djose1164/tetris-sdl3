#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL3/SDL.h>

class GameState
{
public:
    virtual ~GameState() = default;

    // State transitions
    virtual bool enter() = 0;
    virtual bool exit() = 0;

    // Main loop functions
    virtual void handleEvent(SDL_Event &e) = 0;
    virtual void update(float deltatime) = 0;
    virtual void render() = 0;
};

#endif // GAMESTATE_H
