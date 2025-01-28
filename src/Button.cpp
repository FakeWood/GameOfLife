#include "Entity/Button.hpp"

enum Button::buttonSprite : int
{
    BUTTON_NORMAL = 0,
    BUTTON_HOVER = 1,
    BUTTON_DOWN = 2,
    BUTTON_TOTAL
};

Button::Button(SDL_KeyCode p_key, const char *p_textureSheetDir, int p_clipWidth, int p_clipHeight, int p_xPos, int p_yPos, int p_destWidth, int p_destHeight, bool p_active, TransformInfo p_transformInfo)
    : Entity(p_textureSheetDir, p_clipWidth * BUTTON_TOTAL, p_clipHeight * BUTTON_TOTAL, p_xPos, p_yPos, p_destWidth, p_destHeight, p_transformInfo)
{
    pressed = false;

    key = p_key;

    clipWidth = p_clipWidth;
    clipHeight = p_clipHeight;
    xPos = p_xPos;
    yPos = p_yPos;
    destRect = {(int)xPos, (int)yPos, p_destWidth, p_destHeight};

    for (int i = BUTTON_NORMAL; i < BUTTON_TOTAL; i++)
    {
        spriteClips[i] = {0, clipHeight * i, clipWidth, clipHeight};
        // printf( "%d srcClip: { 0, %d, %d, %d }\n", i, clipHeight * i, clipWidth, clipHeight );
    }

    currentSprite = BUTTON_NORMAL;

    active = p_active;
}

void Button::handleEvent(SDL_Event &p_event)
{
    if (!active)
        return;

    if (p_event.type == SDL_MOUSEMOTION ||
        p_event.type == SDL_MOUSEBUTTONDOWN ||
        p_event.type == SDL_MOUSEBUTTONUP ||
        p_event.key.keysym.sym == key)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool hover = false;

        if (x > xPos &&
            x < xPos + destRect.w &&
            y > yPos &&
            y < yPos + destRect.h)
        {
            hover = true;
        }

        // move
        if (p_event.type == SDL_MOUSEMOTION)
        {
            // only looked hovered when hovered
            if (hover)
            {
                currentSprite = BUTTON_HOVER;
            }
            else
            {
                currentSprite = BUTTON_NORMAL;
            }
        }
        // click
        else
        {
            if ((hover && p_event.type == SDL_MOUSEBUTTONDOWN) || p_event.type == SDL_KEYDOWN)
            {
                currentSprite = BUTTON_DOWN;
            }
            else if ((p_event.type == SDL_MOUSEBUTTONUP) || p_event.type == SDL_KEYUP)
            {
                currentSprite = hover ? BUTTON_HOVER : BUTTON_NORMAL;
                if (hover || p_event.type == SDL_KEYUP)
                    pressed = true;
            }
        }
    }
}

void Button::update()
{
    if (!active)
        return;

    Entity::update();
    srcRect = spriteClips[currentSprite];
}

bool Button::checkPressed()
{
    if (!active)
        return false;

    if (pressed)
    {
        pressed = false;
        return true;
    }
    else
    {
        return false;
    }
}

void Button::render()
{
    if (!active)
        return;
    Entity::render();
}