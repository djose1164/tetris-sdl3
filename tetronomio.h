#ifndef TETRONOMIO_H
#define TETRONOMIO_H

#include <array>

#include <SDL3/SDL.h>

class Timer;
class Tetronomio
{
public:
    enum class Letter { O = 1, I, S, Z, L, J, T, Invalid };

    static constexpr int ROWS{4};
    static constexpr int COLS{4};
    static constexpr int BLOCK_SIZE{24};

    using TetronomioShape = std::array<std::array<int, ROWS>, COLS>;

    explicit Tetronomio();
    Tetronomio(Letter newLetter);

    TetronomioShape shape() const;
    void setShape(const TetronomioShape &newShape);

    const SDL_Point &position() const;
    SDL_Point &position();
    void setPosition(int posX, int posY);
    void setPosition(const SDL_Point newPosition);

    Letter letter() const;
    void setLetter(Letter newLetter);

    SDL_Color color() const;
    void setColor(const SDL_Color &newColor);

    void decideColorOnLetter();

    void decideShapeOnLetter();

    void calculateBlockDimensions();

    void rotate();
    TetronomioShape rotated() const;

    int blockWidth() const;

    int blockHeight() const;

    static TetronomioShape rotateShapeClockwise(const TetronomioShape &shape, bool clockwise = true);
    static SDL_Point rotatePosClockwise(const SDL_Point &pos, bool clockwise = true);
    static SDL_Color letterToColor(Tetronomio::Letter l);

private:
    TetronomioShape shape_;
    Letter letter_;
    SDL_Color color_;
    int blockWidth_;
    int blockHeight_;
    SDL_Point position_;
};

#endif // TETRONOMIO_H
