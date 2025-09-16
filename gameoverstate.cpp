#include "gameoverstate.h"
#include "appstate.h"
#include "exitstate.h"
#include "playstate.h"
#include "statemanager.h"
#include "texttexture.h"

GameOverState::GameOverState(AppState *state)
    : GameState()
    , appState_{state}
    , title_{}
    , message_{}
{
}

bool GameOverState::enter()
{
    SDL_Log("Entering to GameOver...");
    title_ = new TextTexture(appState_->font, appState_->renderer);
    title_->setText("Game Over!");
    title_->load();

    message_ = new TextTexture(appState_->font, appState_->renderer);
    message_->setText("Enter to start over or Esc to exit!");
    TTF_SetFontSize(appState_->font, 10);
    message_->load();
    TTF_SetFontSize(appState_->font, appState_->fontSize);
    SDL_Log("Entering to GameOver...Done!");
    return true;
}

bool GameOverState::exit()
{
    SDL_Log("Exiting from GameOver...");
    delete title_;
    delete message_;

    title_ = message_ = nullptr;
    SDL_Log("Exiting from GameOver...Done!");
    return true;
}

void GameOverState::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_EVENT_KEY_DOWN)
    {
        if (e.key.key == SDLK_ESCAPE)
            StateManager::instance()->setNextState(ExitState::instance());
        else if (e.key.key == SDLK_RETURN)
            StateManager::instance()->setNextState(PlayState::instance());
    }
}

void GameOverState::update(float deltatime)
{
}

void GameOverState::render()
{
    const int xTitle{(appState_->screenWidth - title_->width()) / 2};
    const int xMessage{(appState_->screenWidth - message_->width()) / 2};
    title_->render(xTitle, (appState_->screenHeight / 2) - 15);
    message_->render(xMessage, (appState_->screenHeight / 2) + 15);
}

GameOverState *GameOverState::instance()
{
    static GameOverState go{&AppState::instance()};
    return &go;
}
