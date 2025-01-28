#ifndef TEXT_HPP
#define TEXT_HPP
// texture for text

#include "Entity\Entity.hpp"

class Text : public Entity
{
public:
    Text();
    ~Text();

    void loadFont(const char *p_fontDir, int p_fontSize);
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    bool setText(const char *p_text);
    void setPos(double p_xPos, double p_yPos);
    void update() override;
    void free() override;

private:
    TTF_Font *font = nullptr;
    SDL_Color color = {0, 0, 0};
};

#endif