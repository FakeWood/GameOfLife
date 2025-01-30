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

    bool pause = false;
    int mouseHold = 0; // 0 for none. 1 for left. 2 for right.

    int ***world;
    int curWorld = 0;

    int cellW = 0;
    int cellH = 0;
    int liveRange[2] = {2, 3};

    int player[2] = {0, 0};
};

#endif
