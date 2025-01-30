#include "State\PlayState.hpp"
#include "State\StateMachine.hpp"
#include "State\ExitState.hpp"
#include <omp.h>

PlayState PlayState::sPlayState;

PlayState::PlayState()
{
}

PlayState *PlayState::get()
{
    return &sPlayState;
}

bool PlayState::enter()
{
    Global::gTimeStep = 1000 / Global::gFPS;

    cellH = Global::gSCREEN_HEIGHT / Global::gCellSize;
    cellW = Global::gSCREEN_WIDTH / Global::gCellSize;

    pause = false;
    mouseHold = false;
    player[0] = cellW / 2; // x
    player[1] = cellH / 2; // y

    // 3D array
    world = new int **[2];
    for (int i = 0; i < 2; i++)
    {
        world[i] = new int *[Global::gSCREEN_HEIGHT / Global::gCellSize];
        for (int y = 0; y < Global::gSCREEN_HEIGHT / Global::gCellSize; y++)
        {
            world[i][y] = new int[Global::gSCREEN_WIDTH / Global::gCellSize]{0};
        }
    }

    srand(time(NULL));

    for (int i = 0; i < Global::gCellAmount; i++)
    {
        int y = rand() % cellH;
        int x = rand() % cellW;

        if (world[curWorld][y][x] == 0)
        {
            world[curWorld][y][x] = 1;
        }
        else
        {
            i -= 1;
        }
    }

    return true;
}

bool PlayState::exit()
{
    // for ( Entity* E : entities )
    // {
    //     E->free();
    // }

    return true;
}

void PlayState::handleEvent(SDL_Event &p_e)
{
    if (p_e.type == SDL_KEYDOWN)
    {
        switch (p_e.key.keysym.scancode)
        {
        case SDL_SCANCODE_SPACE:
            pause = !pause;
            break;
        case SDL_SCANCODE_LEFT:
            if (player[0] > 0)
            {
                player[0] -= 1;
            }
            break;
        case SDL_SCANCODE_RIGHT:
            if (player[0] < cellW)
            {
                player[0] += 1;
            }
            break;

        case SDL_SCANCODE_UP:
            if (player[1] > 0)
            {
                player[1] -= 1;
            }
            break;
        case SDL_SCANCODE_DOWN:
            if (player[1] < cellH)
            {
                player[1] += 1;
            }
            break;
        case SDL_SCANCODE_E:
            world[curWorld][player[1]][player[0]] = world[curWorld][player[1]][player[0]] == 0 ? 1 : 0;
            break;
        default:
            break;
        }
    }
    else if (p_e.type == SDL_MOUSEBUTTONDOWN)
    {
        switch (p_e.button.button)
        {
        case SDL_BUTTON_LEFT:
            mouseHold = 1;
            break;
        case SDL_BUTTON_RIGHT:
            mouseHold = 2;
            break;
        default:
            mouseHold = 0;
            break;
        }
    }
    else if (p_e.type == SDL_MOUSEBUTTONUP)
    {
        mouseHold = 0;
    }

    if (mouseHold != 0)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        y = y / Global::gCellSize;
        x = x / Global::gCellSize;
        if (y >= 0 && y < cellH && x >= 0 && x < cellW)
        {
            world[curWorld][y][x] = mouseHold == 1 ? 1 : 0;
        }
    }
}

void PlayState::update()
{
    if (pause)
        return;
    // switch cur and next
    int cur = curWorld;
    int next = (cur + 1) % 2;
    curWorld = next;

#pragma omp parallel for collapse(2)
    for (int y = 0; y < cellH; y++)
    {
        for (int x = 0; x < cellW; x++)
        {
            // count neghboring cell
            int count = 0;
            for (int curY = y - Global::gRadius; curY <= y + Global::gRadius; curY++)
            {
                if (curY < 0 || curY >= cellH)
                    continue;
                for (int curX = x - Global::gRadius; curX <= x + Global::gRadius; curX++)
                {
                    if (curX < 0 || curX >= cellW || (curY == y && curX == x))
                        continue;
                    if (world[cur][curY][curX] == 1)
                    {
                        count++;
                    }
                }
            }

            // dead
            if (world[cur][y][x] == 0)
            {
                // Propagate
                if (count == liveRange[1])
                {
                    world[next][y][x] = 1;
                }
                else
                {
                    world[next][y][x] = 0;
                }
            }
            // alive
            else if (world[cur][y][x] == 1)
            {
                // die
                if (count < liveRange[0] || count > liveRange[1])
                {
                    world[next][y][x] = 0;
                }
                else
                {
                    world[next][y][x] = 1;
                }
            }
        }
    }
}

void PlayState::render()
{
    // render cells
    SDL_Rect rect = {0, 0, Global::gCellSize, Global::gCellSize};
    for (int y = 0; y < cellH; y++)
    {
        for (int x = 0; x < cellW; x++)
        {
            if (world[curWorld][y][x] == 1)
            {
                rect.y = y * Global::gCellSize;
                rect.x = x * Global::gCellSize;
                SDL_SetRenderDrawColor(Global::gRenderer, 0x00, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(Global::gRenderer, &rect);
            }
        }
    }

    // render player
    rect.y = player[1] * Global::gCellSize;
    rect.x = player[0] * Global::gCellSize;
    SDL_SetRenderDrawColor(Global::gRenderer, 0xFC, 0x11, 0x11, 0x80);
    SDL_RenderFillRect(Global::gRenderer, &rect);
}