#include <SFML/Graphics.hpp>
#include<iostream>
#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 10.f;

Fruit::Fruit(sf::Vector2f position,int color)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	setColor(color);
	switch(color)
	{
		case 0:shape_.setFillColor(sf::Color::Black);break;
		case 1:shape_.setFillColor(sf::Color(139,69,19));break;//棕色
		case 2:shape_.setFillColor(sf::Color::Red);break;
		case 3:shape_.setFillColor(sf::Color::Blue);break;
		case 4:shape_.setFillColor(sf::Color::Green);break;
		default:shape_.setFillColor(sf::Color::Red);break;
	}
}
	

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

const int& Fruit::getColor()
{
	return color;
}

void Fruit::setColor(int x)
{
	color = x % 5;
}

const sf::Vector2f& Fruit::getPosition() const
{
	return shape_.getPosition();
}
bool Fruit::SamePlace(const Fruit& f)
{
	//std::cout<< getBounds().intersects(f.getBounds());
	return getBounds().intersects(f.getBounds());
}