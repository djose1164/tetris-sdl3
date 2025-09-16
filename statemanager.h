#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class GameState;
class StateManager
{
public:
    GameState *nextState() const;
    void setNextState(GameState *newNextState);

    GameState *currentState() const;
    void setCurrentState(GameState *newCurrentState);

    bool changeState();

    static StateManager *instance();

private:
    StateManager();

    GameState *currentState_;
    GameState *nextState_;
};

#endif // STATEMANAGER_H
