#include "Global.hpp"

int Global::gFPS = 10;
int Global::gTimeStep = 1000 / gFPS;
int Global::gFrameCounter = 0;

const int Global::gSCREEN_WIDTH = 800;
const int Global::gSCREEN_HEIGHT = 640;

SDL_Window *Global::gWindow = nullptr;
SDL_Renderer *Global::gRenderer = nullptr;
const Uint8 *Global::gCurrentKeyState = SDL_GetKeyboardState(NULL);

int Global::gCellAmount = 2000;
int Global::gRadius = 1;
int Global::gCellSize = 5;