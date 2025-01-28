#ifndef SETTING_ITEM_HPP
#define SETTING_ITEM_HPP

#include "Entity\Entity.hpp"

class Text;
class Button;

class SettingItem : public Entity
{
public:
    SettingItem(int p_xPos, int p_yPos, int p_destWidth, int p_destHeight);
    ~SettingItem();

    void handleEvent(SDL_Event &p_event) override;
    void update() override;
    void render() override;
    void free() override;

private:
    int centerX;
    int centerY;
    int amountCenterY;
    Button *bDecrease;
    Button *bIncrease;
    Text *tAmount;

    void decrease();
    void increase();

    std::vector<Entity *> entities;
};

#endif