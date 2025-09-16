#ifndef BOARDCOMPONENT_H
#define BOARDCOMPONENT_H

#include "component.h"
#include "tetronomio.h"
#include "timer.h"
#include <memory>
#include <vector>

class TextTexture;
class BoardComponent : public Component
{
public:
    using Grid = std::vector<std::vector<int>>;

    explicit BoardComponent(AppState *state);

    ~BoardComponent() override;

    // Component interface
    void handleEvent(SDL_Event *e) override;
    void update(float dt) override;
    void render() override;

    bool collides(const Tetronomio &piece) const;
    bool collidesWithBoard(const Tetronomio &piece) const;
    void placeTetronomio(const Tetronomio &piece);

    size_t clearLines();

    Uint16 score() const;
    void setScore(Uint16 newScore);

    constexpr int boardWidth() const;
    constexpr int boardHeight() const;

    static Tetronomio generateTetronomio();
    static constexpr int BLOCK_SIZE{24};
    static constexpr int ROWS{20};
    static constexpr int COLUMNS{10};

private:
    void drawGrid();
    void drawBlock(const SDL_Point &pos, Tetronomio::Letter letter);
    void drawPieces();
    void drawCurrentTetronomio();
    void drawNextTetronomio();

private:
    Grid playfield_;
    Tetronomio currentTetronomio_;
    Tetronomio next_;
    Timer *timer_;
    Uint32 lastTick_;
    Uint16 score_;
    TextTexture *nextFigureText_;
    bool dropFast_;
};

#endif // BOARDCOMPONENT_H
