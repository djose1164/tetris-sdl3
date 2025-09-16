#include "statemanager.h"

#include "exitstate.h"

GameState *StateManager::nextState() const
{
    return nextState_;
}

void StateManager::setNextState(GameState *newNextState)
{
    if (nextState_ != ExitState::instance())
        nextState_ = newNextState;
}

GameState *StateManager::currentState() const
{
    return currentState_;
}

void StateManager::setCurrentState(GameState *newCurrentState)
{
    currentState_ = newCurrentState;
}

bool StateManager::changeState()
{
    bool success{true};
    if (nextState_ != nullptr)
    {
        SDL_Log("Changing state from %p to %p.", currentState_, nextState_);
        success = currentState_->exit() and success;
        success = nextState_->enter() and success;

        currentState_ = nextState_;
        nextState_ = nullptr;
    }
    return success;
}

StateManager *StateManager::instance()
{
    static StateManager sm;
    return &sm;
}

StateManager::StateManager()
    : currentState_{}
    , nextState_{}
{
}
