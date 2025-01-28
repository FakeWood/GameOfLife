#include "Entity\SettingItem.hpp"
#include "Global.hpp"
#include "Entity\Button.hpp"
#include "Entity\Text.hpp"

SettingItem::SettingItem(int p_xPos, int p_yPos, int p_destWidth, int p_destHeight)
    : Entity("./res/white.png", 32, 32, p_xPos, p_yPos, p_destWidth, p_destHeight)
{
    centerX = p_xPos + (p_destWidth / 2);
    centerY = p_yPos + (p_destHeight / 2);

    int amountYOffset = 30;
    amountCenterY = centerY + amountYOffset;

    // amount number text
    tAmount = new Text();
    tAmount->loadFont("./res/font/karma.suture-regular.otf", 18);
    tAmount->setColor(0, 0, 0);
    entities.emplace_back(tAmount);

    // increase and decrease button
    int buttonXOffset = 24;
    int buttonSize = 32;
    int buttonY = amountCenterY - (buttonSize / 2);

    bIncrease = new Button(SDLK_PLUS, "./res/arrow.png", 18, 18, centerX + buttonXOffset, buttonY, buttonSize, buttonSize);
    entities.emplace_back(bIncrease);

    bDecrease = new Button(SDLK_PLUS, "./res/arrow.png", 18, 18, centerX - buttonXOffset - buttonSize, buttonY, buttonSize, buttonSize, true, TransformInfo{0, NULL, SDL_FLIP_HORIZONTAL});
    entities.emplace_back(bDecrease);
}

void SettingItem::handleEvent(SDL_Event &p_event)
{
    Entity::handleEvent(p_event);
    for (Entity *e : entities)
    {
        e->handleEvent(p_event);
    }

    if (bDecrease->checkPressed() && Global::gCellAmount > 0)
    {
        Global::gCellAmount -= 50;
    }

    if (bIncrease->checkPressed())
    {
        Global::gCellAmount += 50;
    }
}

void SettingItem::update()
{
    Entity::update();

    tAmount->setText((std::to_string(Global::gCellAmount)).c_str());
    tAmount->setPos(centerX - (tAmount->getW() / 2), amountCenterY - (tAmount->getH() / 2));

    for (Entity *e : entities)
    {
        e->update();
    }
}

void SettingItem::render()
{
    Entity::render();
    for (Entity *e : entities)
    {
        e->render();
    }
}

void SettingItem::free()
{
    Entity::free();
    for (Entity *e : entities)
    {
        e->free();
    }
}