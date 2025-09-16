#include "appstate.h"
#include "exitstate.h"
#include "introstate.h"
#include "statemanager.h"
#include "timer.h"

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

using namespace std::string_literals;

constexpr int SCREEN_WIDTH{400};
constexpr int SCREEN_HEIGHT{640};
const std::string FONT_PATH{"roboto.ttf"s};
constexpr int POINT_SIZE{14};
constexpr int SCREEN_FPS{60};
constexpr Uint64 NS_PER_FRAME{1'000'000'000 / SCREEN_FPS};
Uint64 lastTicks{};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    SDL_Log("Initializing SDL...");
    if (not SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Could not initialize SDL!: Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (not TTF_Init())
    {
        SDL_Log("Could not initialize TTF!: Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    auto *state{&AppState::instance()};
    state->timer = new Timer;
    state->screenWidth = SCREEN_WIDTH;
    state->screenHeight = SCREEN_HEIGHT;
    state->fontSize = POINT_SIZE;
    if (not SDL_CreateWindowAndRenderer("Tetris Game", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &state->window, &state->renderer))
    {
        SDL_Log("Could not create window or renderer! Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    else
    {
        SDL_SetRenderVSync(state->renderer, 1);
    }

    if (TTF_Font *font{TTF_OpenFont(FONT_PATH.c_str(), POINT_SIZE)}; not font)
    {
        SDL_Log("Could not load font! Error: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    else
    {
        state->font = font;
    }

    *appstate = state;

    StateManager::instance()->setCurrentState(IntroState::instance());
    if (not StateManager::instance()->currentState()->enter())
    {
        StateManager::instance()->currentState()->exit();
        StateManager::instance()->setNextState(ExitState::instance());
    }

    state->timer->start();
    SDL_Log("Initializing SDL...Done");
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appsate)
{
    AppState *state{static_cast<AppState *>(appsate)};
    state->timer->start();
    if (StateManager::instance()->currentState() == ExitState::instance())
        return SDL_APP_SUCCESS;

    Uint64 currentTicks = SDL_GetTicksNS();
    Uint64 elapsedTicks = currentTicks - lastTicks;
    lastTicks = currentTicks;
    const float dt{elapsedTicks / 1'000'000'000.f};
    StateManager::instance()->currentState()->update(dt);
    if (not StateManager::instance()->changeState())
    {
        StateManager::instance()->currentState()->exit();
        StateManager::instance()->setNextState(ExitState::instance());
    }

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(state->renderer);

    // Drawing area
    StateManager::instance()->currentState()->render();

    SDL_RenderPresent(state->renderer);

    const auto renderingNS{state->timer->ticksNS()};
    if (renderingNS < NS_PER_FRAME)
    {
        SDL_DelayNS(NS_PER_FRAME - renderingNS);
    }
    SDL_Delay(16);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    StateManager::instance()->currentState()->handleEvent(*event);

    if (event->type == SDL_EVENT_QUIT)
        StateManager::instance()->setNextState(ExitState::instance());

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    auto *state{static_cast<AppState *>(appstate)};

    SDL_DestroyRenderer(state->renderer);
    state->renderer = nullptr;

    SDL_DestroyWindow(state->window);
    state->window = nullptr;

    TTF_CloseFont(state->font);
    state->font = nullptr;

    delete state->timer;
    //delete state;
}
