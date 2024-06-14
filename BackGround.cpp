#include <SFML/Graphics.hpp>
#include <iostream>
#include "BackGround.h"
#include "Game.h"

using namespace sfSnake;

BackGround::BackGround():color(0),tex(0)
{
    shape_ = sf::Sprite();
    shape_.setColor(sf::Color::White);
    shape_.setTextureRect(sf::IntRect(0,0,Game::Width,Game::Height));
    texture_.loadFromFile("Image/Grid.png");
    texture_.setRepeated(true);
}

void BackGround::setTexture(int tex)
{
    std::cout<<tex<<std::endl;
    switch(tex % 5)
    {
        case 0:
            shape_.setTexture(sf::Texture());
            shape_.setColor(sf::Color::White);
            tex = 0;
            break;
        case 1:
            texture_.setRepeated(true);
            texture_.loadFromFile("Image/Grid.png");
            shape_.setTexture(texture_);
            shape_.setScale(1,1);
            tex = 1;
            break;
        case 2:
            texture_.setRepeated(true);
            texture_.loadFromFile(Game::worlds[0]);
            shape_.setTexture(texture_);
            shape_.setTextureRect(sf::IntRect(0,0,Game::Width,Game::Height));
            tex = 2;
            shape_.setScale(4,4);
            break;
        case 3:
            texture_.setRepeated(true);
            texture_.loadFromFile(Game::worlds[1]);
            shape_.setTexture(texture_);
            tex = 3;
            shape_.setScale(4,4);
            break;
        case 4:
            texture_.setRepeated(true);
            texture_.loadFromFile(Game::worlds[2]);
            shape_.setTexture(texture_);
            tex = 4;
            shape_.setScale(4,4);
            break;
        default:break;
    }
}

void BackGround::setColor(int x)
{
    switch (x % 3)
    {
    case 0:
        shape_.setColor(sf::Color::White);
        color = 0;
        break;
    case 1:
        shape_.setColor(sf::Color(255,128,0));
        color = 1;
        break;
    case 2:
        shape_.setColor(sf::Color(255,192,203));
        color = 2;
        break;
    default:
        break;
    }
}

void BackGround::display(sf::RenderWindow& window)
{
    window.draw(shape_);
}