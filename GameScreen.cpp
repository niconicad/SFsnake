#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;
int GameScreen::ob_size = 4;

GameScreen::GameScreen() : snake_()
{
	for(int i = 0, j = Game::world*3; i < 3; i++, j++)
	{	
		sf::Texture texture;
		texture.loadFromFile(Game::obstacles[j]);
		textures.emplace_back(texture);
	}
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if(!init_flag)
	{
		if(Game::adventure)
			generateFruit_Obstacle();
		init_flag = true;
	}
	if(fruit1.size() < b_b || fruit2.size() < r_g_b)
		generateFruit_Obstacle();
	snake_.update(delta);
	snake_.checkFruitCollisions(fruit1);
	snake_.checkFruitCollisions(fruit2);
	if(Game::adventure)
		snake_.checkObstacleCollisions(obstacles);

	if (snake_.is_hit())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	Game::Back->display(window);

	snake_.render(window);

	for (auto fruit : fruit1)
		fruit.render(window);
	for (auto fruit : fruit2)
		fruit.render(window);
	if(Game::adventure)
		for (auto obstacle : obstacles)
			obstacle.render(window);
}

void GameScreen::generateFruit_Obstacle()
{
	static std::default_random_engine engine(std::time(NULL));
	static std::default_random_engine engine2(std::time(NULL));
	std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Radius * 2);
	std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Radius * 2);
	sf::Vector2f t{(float)xDistribution(engine),(float)yDistribution(engine)};
	std::uniform_int_distribution<int> color(0,1);
	std::uniform_int_distribution<int> color2(0,2);

	if(fruit1.size() < b_b)
	{
		fruit1.emplace_back(t,color(engine2));
	}
	else if(fruit2.size() < r_g_b)
	{
		fruit2.emplace_back(t,color2(engine2)+2);
	}
	if(Game::adventure && !init_flag)//用同一序列生成障碍物，保证不与水果重叠
	{
		for (size_t i = 0; i < ob_size; i++)
		{
			sf::Vector2f temp{(float)xDistribution(engine),(float)yDistribution(engine)};
			std::uniform_int_distribution<int> tex(0,2);
			obstacles.emplace_back(temp,textures[tex(engine2)]);
		}
	}
}
