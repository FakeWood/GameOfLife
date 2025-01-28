#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Global.hpp"

struct TransformInfo
{
    double rotateAngle = 0;
    SDL_Point *rotateCenter = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
};

class Entity
{

public:
    Entity();
    Entity(const char *p_textureDir, int p_srcWidth, int p_srcHeight, int p_xPos, int p_yPos, int p_destWidth, int p_destHeight, TransformInfo p_transformInfo = TransformInfo{});
    ~Entity();

    virtual void handleEvent(SDL_Event &p_event);
    virtual void update();
    virtual void render();
    virtual void free();

    void setColorMod(Uint8 p_r, Uint8 p_g, Uint8 p_b);

    double getX() { return xPos; }
    double getY() { return yPos; }
    int getW() { return width; }
    int getH() { return height; }

protected:
    double xPos = 0;
    double yPos = 0;
    int width = 0;
    int height = 0;
    SDL_Texture *objTexture = nullptr;
    SDL_Rect srcRect, destRect;
    TransformInfo transformInfo;
};

#endif