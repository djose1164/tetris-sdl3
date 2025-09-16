#include "introstate.h"
#include "appstate.h"
#include "playstate.h"
#include "statemanager.h"
#include "texttexture.h"

IntroState::IntroState()
    : title_{}
    , message_{}
{
}

bool IntroState::enter()
{
    SDL_Log("Entering to IntroState...");
    title_ = new TextTexture("Tetris", AppState::instance().font);
    title_->setRenderer(AppState::instance().renderer);
    title_->load();

    message_ = new TextTexture("Press Enter to start!", AppState::instance().font);
    message_->setRenderer(AppState::instance().renderer);
    message_->load();
    SDL_Log("Entering to IntroState...Done");
    return true;
}

bool IntroState::exit()
{
    SDL_Log("Exiting from IntroState...");
    title_->destroy();
    message_->destroy();

    delete title_;
    delete message_;

    title_ = message_ = nullptr;
    SDL_Log("Exiting from IntroState...Donne");
    return true;
}

void IntroState::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_EVENT_KEY_DOWN)
    {
        if (e.key.key == SDLK_RETURN)
            StateManager::instance()->setNextState(PlayState::instance());
    }
}

void IntroState::update(float deltatime)
{
}

void IntroState::render()
{
    title_->render(50, 100);
    message_->render(50, 150);
    SDL_FRect rect{10, 10, 200, 200};
}

IntroState *IntroState::instance()
{
    static IntroState s;
    return &s;
}
