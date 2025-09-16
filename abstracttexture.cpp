#include "abstracttexture.h"

void AbstractTexture::render(float x,
                             float y,
                             SDL_FRect *clip,
                             float newWidth,
                             float newHeight,
                             double degrees,
                             SDL_FPoint *center,
                             SDL_FlipMode flipMode)
{
    SDL_FRect dstrect{x, y, static_cast<float>(width()), static_cast<float>(height())};
    if (newWidth > 0)
        dstrect.w = newWidth;
    if (newHeight > 0)
        dstrect.h = newHeight;

    if (clip)
    {
        dstrect.w = clip->w;
        dstrect.h = clip->h;
    }

    SDL_RenderTextureRotated(renderer(), texture(), clip, &dstrect, degrees, center, flipMode);
}
