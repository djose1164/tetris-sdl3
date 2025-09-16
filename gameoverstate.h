#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "gamestate.h"

class TextTexture;
class AppState;
class GameOverState : public GameState
{
    // GameState interface
public:
    bool enter() override;
    bool exit() override;
    void handleEvent(SDL_Event &e) override;
    void update(float deltatime) override;
    void render() override;

    static GameOverState *instance();

private:
    GameOverState(AppState *state);

    AppState *appState_;
    TextTexture *title_;
    TextTexture *message_;
};

#endif // GAMEOVERSTATE_H
