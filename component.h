#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL3/SDL.h>

class AppState;
class Component
{
public:
    explicit Component(AppState *state = nullptr)
        : appState_{state} {};

    virtual ~Component() = default;

    virtual void handleEvent(SDL_Event *e) = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;

    AppState *appState() const;
    void setAppState(AppState *newAppState);

private:
    AppState *appState_;
};

inline AppState *Component::appState() const
{
    return appState_;
}

inline void Component::setAppState(AppState *newAppState)
{
    appState_ = newAppState;
}

#endif // COMPONENT_H
