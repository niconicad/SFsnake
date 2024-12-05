#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Obstacle
{
public:
	Obstacle(sf::Vector2f position,sf::Texture& texture);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	bool SamePlace(const Obstacle& f);

    void setTex(int x);

	const sf::Vector2f& getPosition() const;

	sf::Sprite shape_;
private:
    static const float edge_size;
    
};
}

#endif