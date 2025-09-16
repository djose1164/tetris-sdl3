#include "playstate.h"
#include "appstate.h"
#include "boardcomponent.h"
#include "timer.h"

#include <sstream>

constexpr Uint64 SECOND_NS{1'000'000'000};

PlayState::PlayState()
    : score_{}
    , lastSecond_{}
    , scoreText_{}
    , timerText_{}
    , board_{}
    , timer_{}
{
}

bool PlayState::enter()
{
    SDL_Log("Entering to PlayState...");
    board_ = new BoardComponent(&AppState::instance());
    scoreText_ = new TextTexture(AppState::instance().font, AppState::instance().renderer);
    timerText_ = new TextTexture(AppState::instance().font, AppState::instance().renderer);

    scoreText_->setText("Score: 0");
    scoreText_->load();

    timerText_->setText("Timer: 0");
    timerText_->load();

    timer_ = new Timer;
    timer_->start();

    SDL_Log("Entering to PlayState...Done");
    return true;
}

bool PlayState::exit()
{
    SDL_Log("Exiting from PlayState...");
    scoreText_->destroy();
    timerText_->destroy();

    delete timerText_;
    delete scoreText_;
    delete board_;
    delete timer_;
    SDL_Log("Exiting from PlayState...Done");
    return true;
}

void PlayState::handleEvent(SDL_Event &e)
{
    board_->handleEvent(&e);
}

void PlayState::update(float deltatime)
{
    board_->update(deltatime);
    Uint64 elapsedTime = timer_->ticksNS();
    if (elapsedTime - lastSecond_ >= SECOND_NS)
    {
        lastSecond_ += SECOND_NS;

        scoreText_->setText("Score: " + std::to_string(board_->score()));
        scoreText_->load();

        std::ostringstream oss;
        const std::string numberStr{std::to_string(lastSecond_ / SECOND_NS)};
        oss << "Timer:" << (numberStr.size() > 3 ? "" : " ") << numberStr;
        timerText_->setText(oss.str());
        timerText_->load();
    }
}

void PlayState::render()
{
    board_->render();

    const float x{static_cast<float>(board_->boardWidth()+ 20)};
    timerText_->render(x, 20);
    scoreText_->render(x, 50);
}

PlayState *PlayState::instance()
{
    static PlayState s;
    return &s;
}
