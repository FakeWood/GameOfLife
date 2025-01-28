#ifndef EXITSTATE_HPP
#define EXITSTATE_HPP

#include "State/GameState.hpp"

class ExitState : public GameState
{
public:
    static ExitState *get();

    bool enter() override;
    bool exit() override;

    void handleEvent(SDL_Event &e) override;
    void update() override;
    void render() override;

private:
    static ExitState sExitState;

    ExitState();
};

#endif