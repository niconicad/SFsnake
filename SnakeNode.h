#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(const sf::Vector2f& position,const sf::Texture& tex);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(const sf::Vector2f& direction);

	void render(sf::RenderWindow& window);

	void setTexture(sf::Texture& texture);

	void setScale(float x,float y);

	void setRotation(const float& angle);

	void setOrigin(const float& x,const float& y);

	float getRotation();

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	//float getDistance(const SnakeNode& node);
	// static const float Width;
	// static const float Height;
	static const float Radius;

	private:
	sf::Sprite shape_;
	sf::Vector2f position_ = sf::Vector2f(0,0);
};
}

#endif