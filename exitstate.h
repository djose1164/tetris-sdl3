#ifndef EXITSTATE_H
#define EXITSTATE_H

#include "gamestate.h"

class ExitState : public GameState
{
    // GameState interface
public:
    bool enter() override;
    bool exit() override;
    void handleEvent(SDL_Event &e) override;
    void update(float deltatime) override;
    void render() override;

    static ExitState *instance();

private:
    ExitState();
};

#endif // EXITSTATE_H
