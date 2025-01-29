#include "Entity\SettingItem.hpp"
#include "Global.hpp"
#include "Entity\Button.hpp"
#include "Entity\Text.hpp"

SettingItem::SettingItem(int *p_target, std::string p_title, int p_delta, int p_xPos, int p_yPos, int p_destWidth, int p_destHeight)
    : Entity("./res/white.png", 32, 32, p_xPos, p_yPos, p_destWidth, p_destHeight)
{
    pTarget = p_target;

    centerX = p_xPos + (p_destWidth / 2);
    centerY = p_yPos + (p_destHeight / 2);

    int amountYOffset = 12;
    amountCenterY = centerY + amountYOffset;

    // text
    tTitle = new Text();
    tTitle->loadFont("./res/font/karma.suture-regular.otf", 18);
    tTitle->setColor(0, 0, 0);
    tTitle->setText(p_title.c_str());
    tTitle->setPos(centerX - (tTitle->getW() / 2), centerY - amountYOffset - (tTitle->getH()));
    entities.emplace_back(tTitle);

    // amount number text
    tNum = new Text();
    tNum->loadFont("./res/font/karma.suture-regular.otf", 16);
    tNum->setColor(0, 0, 0);
    entities.emplace_back(tNum);

    // increase and decrease button
    int buttonXOffset = 24;
    int buttonSize = 26;
    int buttonY = amountCenterY - (buttonSize / 2);

    delta = p_delta;

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

    if (bDecrease->checkPressed() && *pTarget > 0)
    {
        *pTarget -= delta;
    }

    if (bIncrease->checkPressed())
    {
        *pTarget += delta;
    }
}

void SettingItem::update()
{
    Entity::update();

    tNum->setText((std::to_string(*pTarget)).c_str());
    tNum->setPos(centerX - (tNum->getW() / 2), amountCenterY - (tNum->getH() / 2));

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