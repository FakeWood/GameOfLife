#include "State/ExitState.hpp"

ExitState ExitState::sExitState;

ExitState::ExitState()
{
}

ExitState *ExitState::get()
{
    return &sExitState;
}

bool ExitState::enter()
{
    return true;
}

bool ExitState::exit()
{
    return true;
}

void ExitState::handleEvent(SDL_Event &e)
{
}

void ExitState::update()
{
}

void ExitState::render()
{
}