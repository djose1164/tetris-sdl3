#ifndef APPSTATE_H
#define APPSTATE_H

class Timer;
class SDL_Window;
class SDL_Renderer;
class TTF_Font;
class TextTexture;
class AppState
{
public:
    static AppState &instance();

    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    Timer *timer;
    int screenWidth;
    int screenHeight;
    int fontSize;

private:
    AppState();
};

#endif // APPSTATE_H
