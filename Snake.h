#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"
#include "Obstacle.h"

namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down
	};

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow &window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

    void checkObstacleCollisions(std::vector<Obstacle> &obstacles);

    void checkFruitCollisions(std::vector<Fruit>& fruits);

	bool is_hit() const;

	unsigned getSize() const;

	const float MoveDistance = 50.f;

	int posecount = 2;//用于保护开始游戏时的鼠标点击事件
private:
	void move();
	void grow(int x);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hit_;

	sf::Vector2f position_;//？没有用到
	sf::Vector2f direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;
	sf::Texture head;
	sf::Texture body;
	
	static const int InitialSize;
};
}

#endif