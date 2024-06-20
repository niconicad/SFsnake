#include <SFML/Graphics.hpp>
#include <cmath>
#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Radius = 20.f;

SnakeNode::SnakeNode(const sf::Vector2f& position,const sf::Texture& texture)
{
	position_ = position;
	shape_.setPosition(position_);
	shape_.setTexture(texture);
	shape_.setScale(0.15f,0.15f);
	auto x = shape_.getGlobalBounds().width/2;
	auto y = shape_.getGlobalBounds().height/2;
	shape_.setOrigin(x,y);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}

void SnakeNode::move(const sf::Vector2f& direction)
{
	sf::Vector2f newpos = position_ + direction;
	setPosition(newpos);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

void SnakeNode::setTexture(sf::Texture& texture)
{
	shape_.setTexture(texture);
}

void SnakeNode::setScale(float x, float y)
{
	shape_.setScale(x,y);
}

float SnakeNode::getRotation()
{
	return shape_.getRotation();
}

void SnakeNode::setRotation(const float& angle)
{
	shape_.setRotation(angle);
}

void SnakeNode::setOrigin(const float& x,const float& y)
{
	shape_.setOrigin(x,y);
}