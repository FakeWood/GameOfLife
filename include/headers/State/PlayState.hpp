#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State\GameState.hpp"

class PlayState : public GameState
{
public:
    static PlayState *get();

    bool enter() override;
    bool exit() override;

    void handleEvent(SDL_Event &p_e) override;
    void update() override;
    void render() override;

private:
    static PlayState sPlayState;

    PlayState();

    int ***world;
    int curWorld = 0;

    int cellW = 0;
    int cellH = 0;
    int radius = 1;
    int liveRange[2] = {2, 3};
};

#endif
