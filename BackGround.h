#ifndef BACK_GROUND_H
#define BACK_GROUND_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class BackGround
{
public:
    BackGround();

    void setTexture(int x);
    void setColor(int x);
    void display(sf::RenderWindow&);
private:
    sf::Sprite shape_;
    sf::Texture texture_;
    int color;//0白 1橙 2粉 ：为了和果实区分
    int tex;//0空白 1网格
};

}

#endif