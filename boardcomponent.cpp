#include "boardcomponent.h"
#include "appstate.h"
#include "gameoverstate.h"
#include "statemanager.h"
#include "texttexture.h"

constexpr Uint64 TARGET_FPS{725'000'000};

BoardComponent::BoardComponent(AppState *state)
    : Component(state)
    , playfield_{ROWS, std::vector<int>(COLUMNS, 0)}
    , currentTetronomio_{generateTetronomio()}
    , next_{generateTetronomio()}
    , timer_{new Timer}
    , score_{}
    , nextFigureText_{new TextTexture(appState()->font, appState()->renderer)}
    , dropFast_{false}
{
    SDL_assert(appState());
    timer_->start();
    nextFigureText_->setText("Next:");
    nextFigureText_->load();
}

BoardComponent::~BoardComponent()
{
    delete timer_;
}

void BoardComponent::handleEvent(SDL_Event *e)
{
    if (e->type == SDL_EVENT_KEY_DOWN)
    {
        if (e->key.key == SDLK_D)
        {
            Tetronomio moved = currentTetronomio_;
            moved.position().x += 1;
            if (not collides(moved))
                currentTetronomio_ = moved;
        }
        else if (e->key.key == SDLK_A)
        {
            Tetronomio moved = currentTetronomio_;
            moved.position().x -= 1;
            if (not collides(moved))
                currentTetronomio_ = moved;
        }
        else if (e->key.key == SDLK_W)
        {
            Tetronomio rotated = currentTetronomio_;
            rotated.rotate();
            if (not collides(rotated))
                currentTetronomio_ = rotated;
        }
        else if (e->key.key == SDLK_S)
        {
            dropFast_ = true;
        }
    }
    else if (e->type == SDL_EVENT_KEY_UP and not e->key.repeat)
    {
        if (e->key.key == SDLK_S)
        {
            dropFast_ = false;
        }
    }
}

void BoardComponent::update(float dt)
{
    const auto delay{dropFast_ ? TARGET_FPS /4 : TARGET_FPS};
    if (timer_->ticksNS() >= delay)
    {
        timer_->start();

        Tetronomio moved = currentTetronomio_;
        moved.position().y += 1;
        if (not collides(moved))
        {
            currentTetronomio_ = moved;
        }
        else
        {
            placeTetronomio(currentTetronomio_);
            // If we hit top in our next tetronomio.
            if (collides(next_))
            {
                StateManager::instance()->setNextState(GameOverState::instance());
            }
            else
            {
                currentTetronomio_ = next_;
                next_ = generateTetronomio();
            }
        }
    }

    int lines = clearLines();
    score_ += lines * COLUMNS;
}

void BoardComponent::render()
{
    drawGrid();

    drawPieces();

    drawCurrentTetronomio();

    drawNextTetronomio();
}

bool BoardComponent::collides(const Tetronomio &piece) const
{
    const SDL_Point pos{piece.position()};
    const auto shape{piece.shape()};

    for (int row{}; row < Tetronomio::ROWS; ++row)
    {
        for (int col{}; col < Tetronomio::COLS; ++col)
        {
            if (shape[row][col])
            {
                const int boardX{pos.x + col};
                const int boardY{pos.y + row};
                if (boardX < 0 or boardX >= COLUMNS or boardY >= ROWS)
                    return true;
                if (boardY >= 0 and playfield_[boardY][boardX])
                    return true;
            }
        }
    }
    return false;
}

bool BoardComponent::collidesWithBoard(const Tetronomio &piece) const
{
    const SDL_Point pos{piece.position()};
    const auto shape{piece.shape()};

    for (int row{}; row < Tetronomio::ROWS; ++row)
    {
        for (int col{}; col < Tetronomio::COLS; ++col)
        {
            if (shape[row][col])
            {
                const int boardX{pos.x + row};
                const int boardY{pos.y + col};
                if (boardX < 0 or boardX >= COLUMNS or boardY >= ROWS)
                    return true;
            }
        }
    }
    return false;
}

void BoardComponent::placeTetronomio(const Tetronomio &piece)
{
    const auto shape{piece.shape()};
    const SDL_Point pos{piece.position()};
    for (int row{}; row < Tetronomio::ROWS; ++row)
    {
        for (int col{}; col < Tetronomio::COLS; ++col)
        {
            if (not shape[row][col])
                continue;
            const int gridX{pos.x + col};
            const int gridY{pos.y + row};
            if (gridX >= 0 and gridX < COLUMNS and gridY >= 0 and gridY < ROWS)
            {
                SDL_Log("coordinates (%d,%d)", gridX, gridY);
                playfield_[gridY][gridX] = int(piece.letter());
            }
            else
                SDL_Log("Invalid coordinates! (%d,%d)", gridX, gridY);
        }
    }
}

constexpr int BoardComponent::boardWidth() const
{
    return COLUMNS * BLOCK_SIZE;
}

constexpr int BoardComponent::boardHeight() const
{
    return ROWS * BLOCK_SIZE;
}

Tetronomio BoardComponent::generateTetronomio()
{
    SDL_Log("Generating tetronomio...");
    Tetronomio tetronomio{};
    const auto letter{static_cast<Tetronomio::Letter>(SDL_rand(7) + 1)};
    tetronomio.setLetter(letter);
    tetronomio.setPosition(COLUMNS/2, 0);
    tetronomio.decideColorOnLetter();
    tetronomio.calculateBlockDimensions();
    SDL_Log("Generating tetronomio...Done!");
    return tetronomio;
}

size_t BoardComponent::clearLines()
{
    size_t linesCompleted{};
    for (int row{}; row < ROWS; ++row)
    {
        bool isLineCompleted{true};
        for (int col{}; col < COLUMNS; ++col)
        {
            isLineCompleted = playfield_[row][col];
            if (not isLineCompleted)
                break;
        }
        if (isLineCompleted)
        {
            ++linesCompleted;
            const auto it{playfield_.begin()};
            playfield_.erase(it + row);
            playfield_.insert(it, std::vector<int>(COLUMNS, 0));
        }
    }
    return linesCompleted;
}

void BoardComponent::drawBlock(const SDL_Point &pos, Tetronomio::Letter letter)
{
    SDL_assert(letter != Tetronomio::Letter::Invalid);
    SDL_Color color{Tetronomio::letterToColor(letter)};
    SDL_SetRenderDrawColor(appState()->renderer,color.r, color.g, color.b, color.a);
    SDL_FRect rect{
        static_cast<float>(pos.x * BLOCK_SIZE) + 10.f,
        static_cast<float>(pos.y * BLOCK_SIZE) + 10.f,
        BLOCK_SIZE-1,
        BLOCK_SIZE-1
    };
    SDL_RenderFillRect(appState()->renderer, &rect);
}

void BoardComponent::drawPieces()
{
    for (int row{}; row < ROWS; ++row)
    {
        for (int col{}; col < COLUMNS; ++col)
        {
            if (const int letter = playfield_[row][col]; letter)
            {
                drawBlock({col, row}, static_cast<Tetronomio::Letter>(letter));
            }
        }
    }
}

void BoardComponent::drawCurrentTetronomio()
{
    for (int row{}; row < Tetronomio::ROWS; ++row)
    {
        for (int col{}; col < Tetronomio::COLS; ++col)
        {
            if (currentTetronomio_.shape()[row][col])
            {
                const int boardX{currentTetronomio_.position().x + col};
                const int boardY{currentTetronomio_.position().y + row};
                if (boardY >= 0)
                    drawBlock({boardX, boardY}, currentTetronomio_.letter());
            }
        }
    }
}

void BoardComponent::drawNextTetronomio()
{
    const int midX{(appState()->screenWidth - 10 - boardWidth() - nextFigureText_->width()) / 2};
    const int xOffset{10 + boardWidth()};
    nextFigureText_->render(xOffset + midX, ((ROWS*BLOCK_SIZE) / 2) -10);

    for (int row{}; row < Tetronomio::ROWS; ++row)
    {
        for (int col{}; col < Tetronomio::COLS; ++col)
        {
            if (next_.shape()[row][col])
            {
                drawBlock({col + COLUMNS + 2, row + ROWS /2}, next_.letter());
            }
        }
    }
}

Uint16 BoardComponent::score() const
{
    return score_;
}

void BoardComponent::setScore(Uint16 newScore)
{
    score_ = newScore;
}

void BoardComponent::drawGrid()
{
    SDL_Renderer *renderer{appState()->renderer};

    SDL_SetRenderDrawColor(renderer, 0xc8, 0xc8, 0xff, 0x96);
    SDL_FRect rect{10, 10, (COLUMNS * BLOCK_SIZE), (ROWS * BLOCK_SIZE)};
    SDL_RenderRect(renderer, &rect);

    for (int i{}; i < ROWS; ++i)
    {
        const int x1{10};
        const int y1{10 + (BLOCK_SIZE * i)};
        const int x2{10 + (COLUMNS * BLOCK_SIZE)};
        const int y2{y1};
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }
    for (int i{}; i < COLUMNS; ++i)
    {
        const int x1{10 + (BLOCK_SIZE * i)};
        const int y1{10};
        const int x2{x1};
        const int y2{10 + (ROWS * BLOCK_SIZE)};
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }
}
