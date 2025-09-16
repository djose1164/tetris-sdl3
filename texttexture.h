#ifndef TEXTTEXTURE_H
#define TEXTTEXTURE_H

#include "abstracttexture.h"
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

class TextTexture : public AbstractTexture
{
public:
    TextTexture(std::string_view newText, TTF_Font *newFont);
    TextTexture(TTF_Font *newFont, SDL_Renderer *newRenderer);

    bool load() override;

    void destroy() override;

    std::string text() const;
    void setText(const std::string &newText);

    SDL_Color textColor() const;
    void setTextColor(const SDL_Color &newTextColor);

    TTF_Font *font() const;
    void setFont(TTF_Font *newFont);

    // AbstractTexture interface
    SDL_Renderer *renderer() const override;
    void setRenderer(SDL_Renderer *newRenderer) override;

    int width() const override;
    int height() const override;

protected:
    SDL_Texture *texture() const override;

private:
    std::string text_;
    SDL_Color textColor_;
    TTF_Font *font_;
    SDL_Texture *texture_;
    SDL_Renderer *renderer_;
    int width_;
    int height_;
};

#endif // TEXTTEXTURE_H
