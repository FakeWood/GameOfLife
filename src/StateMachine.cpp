#include "State\StateMachine.hpp"
#include "Global.hpp"
#include "State\GameState.hpp"
#include "State\HomeState.hpp"
#include "State\PlayState.hpp"
#include "State\ExitState.hpp"

GameState *StateMachine::currentState = nullptr;
GameState *StateMachine::nextState = nullptr;

void StateMachine::setNextState(GameState *p_nextState)
{
    // make it impossible to go next state after trigger exit state
    if (nextState != ExitState::get())
    {
        nextState = p_nextState;
    }
}

void StateMachine::changeState()
{
    if (nextState != nullptr)
    {
        currentState->exit();
        nextState->enter();

        currentState = nextState;
        nextState = nullptr;
    }
}

bool StateMachine::init()
{
    bool success = true;
    Global::gFrameCounter = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL!\nError: %s\n", SDL_GetError());
        success = false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("Failed to initialize SDL_image!\nError: %s\n", IMG_GetError());
        success = false;
    }

    if (TTF_Init() == -1)
    {
        printf("Failed to initialize SDL_ttf!\nError: %s\n", TTF_GetError());
        success = false;
    }

    Global::gWindow = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Global::gSCREEN_WIDTH, Global::gSCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (Global::gWindow == nullptr)
    {
        printf("Failed to create window!\nError: %s", SDL_GetError());
        success = false;
    }

    Global::gRenderer = SDL_CreateRenderer(Global::gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (Global::gRenderer == nullptr)
    {
        printf("Failed to create renderer!\nError: %s", SDL_GetError());
        success = false;
    }
    SDL_SetRenderDrawColor(Global::gRenderer, 255, 255, 255, 255);
    SDL_SetRenderDrawBlendMode(Global::gRenderer, SDL_BLENDMODE_BLEND);

    currentState = HomeState::get();
    currentState->enter();

    nextState = nullptr;

    return success;
}

bool StateMachine::close()
{
    SDL_DestroyWindow(Global::gWindow);
    Global::gWindow = nullptr;

    SDL_DestroyRenderer(Global::gRenderer);
    Global::gRenderer = nullptr;

    TTF_Quit();
    SDL_Quit();

    printf("Game cleaned!");

    return true;
}
