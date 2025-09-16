#include "texttexture.h"

TextTexture::TextTexture(std::string_view newText, TTF_Font *newFont)
    : text_{newText}
    , textColor_{SDL_Color{0xa2, 0xff, 0x00, 0xff}}
    , font_{newFont}
    , texture_{}
    , renderer_{}
    , width_{}
    , height_{}
{
}

TextTexture::TextTexture(TTF_Font *newFont, SDL_Renderer *newRenderer)
    : text_{}
    , textColor_{SDL_Color{0xa2, 0xff, 0x00, 0xff}}
    , font_{newFont}
    , texture_{}
    , renderer_{newRenderer}
    , width_{}
    , height_{}
{
}

bool TextTexture::load()
{
    if (text_.empty() or not renderer() or not font_)
    {
        SDL_Log("Could'nt load texture because text or renderer or font weren't set!");
        return false;
    }

    destroy();

    const auto surface = TTF_RenderText_Blended(font_, text_.c_str(), 0, textColor_);
    if (not surface)
    {
        SDL_Log("Could not create surface from text! Error: %s", SDL_GetError());
        return false;
    }

    if (texture_ = SDL_CreateTextureFromSurface(renderer(), surface); not texture_)
    {
        SDL_Log("Could not create texture from surface! Error: %s", SDL_GetError());
        SDL_DestroySurface(surface);
        return false;
    }

    width_ = surface->w;
    height_ = surface->h;

    SDL_DestroySurface(surface);
    return texture_ != nullptr;
}

void TextTexture::destroy()
{
    width_ = height_ = 0;
    if (texture_)
    {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

std::string TextTexture::text() const
{
    return text_;
}

void TextTexture::setText(const std::string &newText)
{
    text_ = newText;
}

SDL_Color TextTexture::textColor() const
{
    return textColor_;
}

void TextTexture::setTextColor(const SDL_Color &newTextColor)
{
    textColor_ = newTextColor;
}

TTF_Font *TextTexture::font() const
{
    return font_;
}

void TextTexture::setFont(TTF_Font *newFont)
{
    font_ = newFont;
}

SDL_Renderer *TextTexture::renderer() const
{
    return renderer_;
}

void TextTexture::setRenderer(SDL_Renderer *newRenderer)
{
    renderer_ = newRenderer;
}

int TextTexture::width() const
{
    return width_;
}

int TextTexture::height() const
{
    return height_;
}

SDL_Texture *TextTexture::texture() const
{
    return texture_;
}
