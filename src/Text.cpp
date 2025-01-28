#include "Entity\Text.hpp"

Text::Text()
{
    font = nullptr;
    color = {0, 0, 0};
    srcRect = {0, 0, 0, 0};
}

void Text::loadFont(const char *p_fontDir, int p_fontSize)
{
    font = TTF_OpenFont(p_fontDir, p_fontSize);
    if (font == nullptr)
    {
        printf("Failed to load font from \"%s\" !\nError: %s\n", p_fontDir, TTF_GetError());
    }
}

void Text::setColor(Uint8 r, Uint8 g, Uint8 b)
{
    color = {r, g, b};
}

bool Text::setText(const char *p_text)
{
    bool success = true;

    Entity::free();

    SDL_Surface *tmpSurface = TTF_RenderText_Solid(font, p_text, color);
    if (tmpSurface == nullptr)
    {
        printf("Failed to load text to surface!\nError: %s\n", TTF_GetError());
        success = false;
    }

    objTexture = SDL_CreateTextureFromSurface(Global::gRenderer, tmpSurface);
    if (objTexture == nullptr)
    {
        printf("Failed to create texture from text surface!\nError: %s\n", SDL_GetError());
        success = false;
    }

    width = tmpSurface->w;
    height = tmpSurface->h;

    SDL_FreeSurface(tmpSurface);

    return success;
}

void Text::setPos(double p_xPos, double p_yPos)
{
    xPos = p_xPos;
    yPos = p_yPos;
}

void Text::update()
{
    srcRect = {0, 0, width, height};
    Entity::update();
}

void Text::free()
{
    Entity::free();

    TTF_CloseFont(font);
}