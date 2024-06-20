#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H
#include<random>
#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "Obstacle.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	void generateFruit_Obstacle();

    static const int b_b = 5;
    static const int r_g_b = 15;
	static int ob_size;
	bool init_flag = false;
	std::vector<sf::Texture> textures;

private:
	Snake snake_;
	std::vector<Fruit> fruit1, fruit2;//分别放不同比例的水果
	std::vector<Obstacle> obstacles;
};
}

#endif