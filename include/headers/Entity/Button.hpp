#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Entity\Entity.hpp"

class Button : public Entity
{
public:
    Button(SDL_KeyCode p_key, const char *p_textureSheetDir, int p_clipWidth, int p_clipHeight, int p_xPos, int p_yPos, int p_destWidth, int p_destHeight, bool p_active = true, TransformInfo p_transformInfo = TransformInfo{});
    ~Button();

    void handleEvent(SDL_Event &p_event) override;
    void update() override;
    void render() override;

    bool checkPressed();
    bool active;

private:
    SDL_KeyCode key;

    enum buttonSprite : int;
    buttonSprite currentSprite;

    SDL_Rect spriteClips[3];
    int clipWidth;
    int clipHeight;
    bool pressed;
};

#endif