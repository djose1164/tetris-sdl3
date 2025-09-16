#ifndef ABSTRACTTEXTURE_H
#define ABSTRACTTEXTURE_H

#include <SDL3/SDL.h>

class AbstractTexture
{
public:
    virtual ~AbstractTexture() = default;

    virtual bool load() = 0;

    virtual void destroy() = 0;

    virtual void render(float x,
                        float y,
                        SDL_FRect *clip = nullptr,
                        float newWidth = 0,
                        float newHeight = 0,
                        double degrees = 0,
                        SDL_FPoint *center = nullptr,
                        SDL_FlipMode flipMode = SDL_FLIP_NONE);

    virtual SDL_Renderer *renderer() const = 0;
    virtual void setRenderer(SDL_Renderer *newRenderer) = 0;

    virtual int width() const = 0;

    virtual int height() const = 0;

protected:
    virtual SDL_Texture *texture() const = 0;
};

#endif // ABSTRACTTEXTURE_H
