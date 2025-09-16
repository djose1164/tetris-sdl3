#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "gamestate.h"

class TextTexture;
class IntroState : public GameState
{
public:
    // GameState interface
    bool enter() override;
    bool exit() override;
    void handleEvent(SDL_Event &e) override;
    void update(float deltatime) override;
    void render() override;

    static IntroState *instance();

private:
    IntroState();

    TextTexture *title_;
    TextTexture *message_;
};

#endif // INTROSTATE_H
