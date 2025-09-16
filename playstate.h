#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include "texttexture.h"

class Component;
class Timer;
class BoardComponent;
class PlayState : public GameState
{
    // GameState interface
public:
    bool enter() override;
    bool exit() override;
    void handleEvent(SDL_Event &e) override;
    void update(float deltatime) override;
    void render() override;

    static PlayState *instance();

private:
    PlayState();

    int score_;
    Uint64 lastSecond_;
    TextTexture *scoreText_;
    TextTexture *timerText_;
    BoardComponent *board_;
    Timer *timer_;
};

#endif // PLAYSTATE_H
