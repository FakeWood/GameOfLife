#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "Global.hpp"

class GameState
{
public:
    virtual bool enter() = 0;
    virtual bool exit() = 0;

    virtual void handleEvent(SDL_Event &e) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    // Make sure to call child destructors(?)
    virtual ~GameState(){};
};

#endif