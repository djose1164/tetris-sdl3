#include "appstate.h"

AppState &AppState::instance()
{
    static AppState as;
    return as;
}

AppState::AppState()
    : window{}
    , renderer{}
    , font{}
    , timer{}
    , screenWidth{}
    , screenHeight{}
    , fontSize{}
{
}
