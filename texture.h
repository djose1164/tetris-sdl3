#ifndef TEXTURE_H
#define TEXTURE_H

#include "abstracttexture.h"
#include <SDL3/SDL.h>
#include <filesystem>

class Texture : public AbstractTexture
{
public:
    explicit Texture(const std::filesystem::path &newPath, SDL_Renderer *newRenderer);
    ~Texture() override;

    bool load() override;
    bool load(const std::filesystem::path &filename);

    // AbstractTexture interface
    void render(float x,
                float y,
                SDL_FRect *clip,
                float width,
                float height,
                double degrees,
                SDL_FPoint *center,
                SDL_FlipMode flipMode) override;

    void destroy() override;

    int width() const override;

    int height() const override;

    std::string path() const;
    void setPath(const std::string &newPath);

    SDL_Renderer *renderer() const override;
    void setRenderer(SDL_Renderer *newRenderer) override;

protected:
    SDL_Texture *texture() const override;

private:
    int width_;
    int height_;
    std::filesystem::path path_;
    SDL_Texture *texture_;
    SDL_Renderer *renderer_;
};

#endif // TEXTURE_H
