#include <SFML/Graphics.hpp>
#include<iostream>
#include "Obstacle.h"
#include "Game.h"

using namespace sfSnake;

const float Obstacle::edge_size = 10.f;

Obstacle::Obstacle(sf::Vector2f position,sf::Texture& texture)
{
    shape_.setTexture(texture);
    shape_.setPosition(position);
    shape_.setScale(3.f, 3.f);
}
	

void Obstacle::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Obstacle::getBounds() const
{
	return shape_.getGlobalBounds();
}


const sf::Vector2f& Obstacle::getPosition() const
{
	return shape_.getPosition();
}

bool Obstacle::SamePlace(const Obstacle& f)
{
	return getBounds().intersects(f.getBounds());
}
