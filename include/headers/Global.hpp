#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Global
{
    static const int gFPS;
    static const int gTimeStep;
    static int gFrameCounter;

    static const int gSCREEN_WIDTH;
    static const int gSCREEN_HEIGHT;

    static SDL_Window *gWindow;
    static SDL_Renderer *gRenderer;
    static const Uint8 *gCurrentKeyState;

    static int gCellAmount;
    static int gCellSize;
};

#endif