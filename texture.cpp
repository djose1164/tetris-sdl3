#include "texture.h"
#include <SDL3_image/SDL_image.h>

#define checkPath()                                                        \
    do                                                                     \
    {                                                                      \
        if (path_.empty())                                                 \
        {                                                                  \
            SDL_Log("You need to set a path before loading the texture!"); \
            return false;                                                  \
        }                                                                  \
    } while (0)

#define checkRenderer()                                                        \
    do                                                                         \
    {                                                                          \
        if (not renderer_)                                                     \
        {                                                                      \
            SDL_Log("You need to set a renderer before loading the texture!"); \
            return false;                                                      \
        }                                                                      \
    } while (0)

Texture::Texture(const std::filesystem::path &newPath, SDL_Renderer *newRenderer)
    : width_{}
    , height_{}
    , path_{newPath}
    , texture_{}
    , renderer_{newRenderer}
{
}

Texture::~Texture()
{
    destroy();
}

bool Texture::load()
{
    checkPath();
    checkRenderer();

    destroy();

    if (texture_ = IMG_LoadTexture(renderer_, path_.c_str()); texture_)
    {
        width_ = texture_->w;
        height_ = texture_->h;
    }
    else
    {
        SDL_Log("Couldn't create texture for %s path! Error: %s", path_.c_str(), SDL_GetError());
    }

    return texture_;
}

bool Texture::load(const std::filesystem::path &filename)
{
    path_ = filename;
    return load();
}

void Texture::render(float x,
                     float y,
                     SDL_FRect *clip,
                     float width,
                     float height,
                     double degrees,
                     SDL_FPoint *center,
                     SDL_FlipMode flipMode)
{
    AbstractTexture::render(x, y, clip, width, height, degrees, center, flipMode);
}

void Texture::destroy()
{
    width_ = height_ = 0;
    if (texture_)
    {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

int Texture::width() const
{
    return width_;
}

int Texture::height() const
{
    return height_;
}

std::string Texture::path() const
{
    return path_;
}

void Texture::setPath(const std::string &newPath)
{
    path_ = newPath;
}

SDL_Renderer *Texture::renderer() const
{
    return renderer_;
}

void Texture::setRenderer(SDL_Renderer *newRenderer)
{
    renderer_ = newRenderer;
}

SDL_Texture *Texture::texture() const
{
    return texture_;
}
