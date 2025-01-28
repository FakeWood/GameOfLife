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
    int itemHeight = 200;
    int itemX = (Global::gSCREEN_WIDTH - itemWidth) / 2;
    int itemY = (Global::gSCREEN_HEIGHT - itemHeight) / 2;

    settingItem = new SettingItem(itemX, itemY, itemWidth, itemHeight);
    entities.emplace_back(settingItem);

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