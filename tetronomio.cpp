#include "tetronomio.h"

#include <unordered_map>
#include <vector>

const std::vector<Tetronomio::TetronomioShape> SHAPE_LIST = {
    {{ // O
        {{1, 1, 0, 0}},
        {{1, 1, 0, 0}},
        {{0, 0, 0, 0}},
        {{0, 0, 0, 0}}
    }},
    {{ // I
        {{0, 1, 0, 0}},
        {{0, 1, 0, 0}},
        {{0, 1, 0, 0}},
        {{0, 1, 0, 0}}
    }},
    {{ // S
        {{0, 1, 1, 0}},
        {{1, 1, 0, 0}},
        {{0, 0, 0, 0}},
        {{0, 0, 0, 0}}
    }},
    {{ // Z
        {{1, 1, 0, 0}},
        {{0, 1, 1, 0}},
        {{0, 0, 0, 0}},
        {{0, 0, 0, 0}}
    }},
    {{ // L
        {{1, 0, 0, 0}},
        {{1, 0, 0, 0}},
        {{1, 1, 0, 0}},
        {{0, 0, 0, 0}}
    }},
    {{ // J
        {{0, 1, 0, 0}},
        {{0, 1, 0, 0}},
        {{1, 1, 0, 0}},
        {{0, 0, 0, 0}}
    }},
    {{ // T
        {{1, 1, 1, 0}},
        {{0, 1, 0, 0}},
        {{0, 0, 0, 0}},
        {{0, 0, 0, 0}}
    }},
};

Tetronomio::Tetronomio()
    : Tetronomio(Letter::Invalid)
{
}

Tetronomio::Tetronomio(Letter newLetter)
    : shape_{}
    , letter_{newLetter}
    , blockWidth_{}
    , blockHeight_{}
    , position_{}
{
    if (letter_ == Letter::Invalid)
        return;
    decideShapeOnLetter();
    decideColorOnLetter();
    calculateBlockDimensions();
}

void Tetronomio::setShape(const TetronomioShape &newShape)
{
    shape_ = newShape;
}

const SDL_Point &Tetronomio::position() const
{
    return position_;
}

SDL_Point &Tetronomio::position()
{
    return position_;
}

Tetronomio::TetronomioShape Tetronomio::shape() const
{
    return shape_;
}

void Tetronomio::setPosition(int posX, int posY)
{
    position_.x = posX;
    position_.y = posY;
}

void Tetronomio::setPosition(const SDL_Point newPosition)
{
    setPosition(newPosition.x, newPosition.y);
}

Tetronomio::Letter Tetronomio::letter() const
{
    return letter_;
}

void Tetronomio::setLetter(Letter newLetter)
{
    SDL_assert(newLetter != Letter::Invalid);
    letter_ = newLetter;
    decideShapeOnLetter();
}

void Tetronomio::decideShapeOnLetter()
{
    SDL_assert(letter_ != Letter::Invalid);
    if (letter_ != Letter::Invalid)
    {
        setShape(SHAPE_LIST[int(letter_) - 1]);
    }
}

void Tetronomio::calculateBlockDimensions()
{
    std::unordered_map<int, std::vector<std::pair<int, int>>> xMap;
    std::unordered_map<int, std::vector<std::pair<int, int>>> yMap;
    for (int row{}; row < ROWS; ++row)
    {
        for (int col{}; col < COLS; ++col)
        {
            if (shape_[row][col])
            {
                const std::pair<int, int> pair{row, col};
                xMap[row].push_back(pair);
                yMap[col].push_back(pair);
            }
        }
    }

    int xMaxBlock{};
    for (const auto &pair : xMap)
    {
        if (pair.second.size() > xMaxBlock)
            xMaxBlock = pair.second.size();
    }

    int yMaxBlock{};
    for (const auto &pair : yMap)
    {
        if (pair.second.size() > yMaxBlock)
            yMaxBlock = pair.second.size();
    }

    blockWidth_ = xMaxBlock;
    blockHeight_ = yMaxBlock;

    SDL_assert(blockWidth_ > 0);
    SDL_assert(blockHeight_ > 0);
    SDL_Log("block: wxh=%dx%d", blockWidth_, blockHeight_);
}

void Tetronomio::rotate()
{
    shape_ = rotated();
}

Tetronomio::TetronomioShape Tetronomio::rotated() const
{
    return rotateShapeClockwise(shape_);
}

SDL_Point Tetronomio::rotatePosClockwise(const SDL_Point &pos, bool clockwise)
{
    SDL_Point newPos;
    constexpr int distance{3};
    if (clockwise)
        newPos =  {pos.x + BLOCK_SIZE, pos.y};
    else
        newPos = {pos.x, pos.y + distance * BLOCK_SIZE};

    SDL_Log("newPos: (%d, %d)", newPos.x, newPos.y);
    return newPos;
}

SDL_Color Tetronomio::letterToColor(Letter l)
{
    SDL_Color c{};
    switch (l)
    {
    case Letter::O:
        c = SDL_Color{255, 255, 0, 255}; // Yellow
        break;
    case Letter::I:
        c = SDL_Color{0, 255, 255, 255}; // Cyan
        break;
    case Letter::S:
        c = SDL_Color{0, 255, 0, 255}; // Green
        break;
    case Letter::Z:
        c = SDL_Color{255, 0, 0, 255}; // Red
        break;
    case Letter::L:
        c = SDL_Color{255, 165, 0, 255}; // Orange
        break;
    case Letter::J:
        c = SDL_Color{0, 0, 255, 255}; // Blue
        break;
    case Letter::T:
        c = SDL_Color{128, 0, 128, 255}; // Purple
        break;
    case Letter::Invalid:
    default:
        c = SDL_Color{128, 128, 128, 255}; // Gray fallback
        break;
    }
    return c;
}

int Tetronomio::blockWidth() const
{
    return blockWidth_;
}

int Tetronomio::blockHeight() const
{
    return blockHeight_;
}

Tetronomio::TetronomioShape Tetronomio::rotateShapeClockwise(
    const TetronomioShape &shape, bool clockwise)
{
    TetronomioShape rotated{};
    constexpr int gridSize{4 - 1};
    for (int row{}; row < ROWS; ++row)
    {
        for (int col{}; col < COLS; ++col)
        {
            if (clockwise)
                rotated[col][gridSize - row] = shape[row][col];
            else
                rotated[gridSize - col][row] = shape[row][col];
        }
    }
    return rotated;
}

void Tetronomio::decideColorOnLetter()
{
    switch (letter_)
    {
    case Letter::O:
        color_ = SDL_Color{255, 255, 0, 255}; // Yellow
        break;
    case Letter::I:
        color_ = SDL_Color{0, 255, 255, 255}; // Cyan
        break;
    case Letter::S:
        color_ = SDL_Color{0, 255, 0, 255}; // Green
        break;
    case Letter::Z:
        color_ = SDL_Color{255, 0, 0, 255}; // Red
        break;
    case Letter::L:
        color_ = SDL_Color{255, 165, 0, 255}; // Orange
        break;
    case Letter::J:
        color_ = SDL_Color{0, 0, 255, 255}; // Blue
        break;
    case Letter::T:
        color_ = SDL_Color{128, 0, 128, 255}; // Purple
        break;
    case Letter::Invalid:
    default:
        color_ = SDL_Color{128, 128, 128, 255}; // Gray fallback
        break;
    }
}

SDL_Color Tetronomio::color() const
{
    return color_;
}

void Tetronomio::setColor(const SDL_Color &newColor)
{
    color_ = newColor;
}
