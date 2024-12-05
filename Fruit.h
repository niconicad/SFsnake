#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0), int color = 0);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	const int& getColor();

	void setColor(int x);

	bool SamePlace(const Fruit& f);

	const sf::Vector2f& getPosition() const;

	
private:
	static const float Radius;
	sf::CircleShape shape_;
	int color;//0黑 1褐 2红 3蓝 4绿
};
}

#endif