#include "State\HomeState.hpp"
#include "Entity\Entity.hpp"
#include "Entity\SettingItem.hpp"
#include "State\StateMachine.hpp"
#include "State\PlayState.hpp"

HomeState::HomeState()
{
}

HomeState HomeState::sHomeState;

HomeState *HomeState::get()
{
    return &sHomeState;
}

bool HomeState::enter()
{
    // create setting items
    int itemWidth = 300;
    int itemHeight = 120;
    int itemX = (Global::gSCREEN_WIDTH - itemWidth) / 2;
    int itemY = (Global::gSCREEN_HEIGHT - itemHeight * 4) / 2;

    setFPS = new SettingItem(&Global::gFPS, "FPS", 1, itemX, itemY, itemWidth, itemHeight);
    entities.emplace_back(setFPS);

    itemY += itemHeight;
    setAmount = new SettingItem(&Global::gCellAmount, "Cell Amount", 50, itemX, itemY, itemWidth, itemHeight);
    entities.emplace_back(setAmount);

    itemY += itemHeight;
    setRadius = new SettingItem(&Global::gRadius, "Field Size", 1, itemX, itemY, itemWidth, itemHeight);
    entities.emplace_back(setRadius);

    itemY += itemHeight;
    setCellSize = new SettingItem(&Global::gCellSize, "Cell Size", 1, itemX, itemY, itemWidth, itemHeight);
    entities.emplace_back(setCellSize);

    return true;
}

bool HomeState::exit()
{
    for (Entity *e : entities)
    {
        e->free();
    }

    return true;
}

void HomeState::handleEvent(SDL_Event &p_e)
{
    for (Entity *e : entities)
    {
        e->handleEvent(p_e);
    }

    if (p_e.type == SDL_KEYDOWN && p_e.key.keysym.scancode == SDL_SCANCODE_RETURN)
    {
        StateMachine::setNextState(PlayState::get());
    }
}

void HomeState::update()
{
    for (Entity *e : entities)
    {
        e->update();
    }
}

void HomeState::render()
{
    for (Entity *e : entities)
    {
        e->render();
    }
}