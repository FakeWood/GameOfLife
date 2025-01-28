#include "GameLoop.hpp"
#include "Global.hpp"
#include "State\StateMachine.hpp"
#include "State\ExitState.hpp"

int GameLoop::gameLoop()
{

    Uint32 frameStart;
    int frameTime;

    if (!StateMachine::init())
    {
        printf("Failed to initialize the game!\n");
        return 1;
    }

    SDL_Event e;

    while (StateMachine::currentState != ExitState::get())
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e))
        {
            StateMachine::currentState->handleEvent(e);

            if (e.type == SDL_QUIT)
                StateMachine::setNextState(ExitState::get());
        }

        StateMachine::currentState->update();

        StateMachine::changeState();

        /* render */
        SDL_SetRenderDrawColor(Global::gRenderer, 200, 220, 250, 255);
        SDL_RenderClear(Global::gRenderer);

        StateMachine::currentState->render();

        SDL_RenderPresent(Global::gRenderer);
        /* render */

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < Global::gTimeStep)
            SDL_Delay(Global::gTimeStep - frameTime);
        else
            printf("Lag %d milliSeconds!\n ", frameTime - Global::gTimeStep);

        if (++Global::gFrameCounter > Global::gFPS)
            Global::gFrameCounter = 0;
    }

    StateMachine::close();

    return 0;
}