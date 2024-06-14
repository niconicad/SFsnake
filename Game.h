#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"
#include "BackGround.h"

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();

	void setBackTexture(sf::Texture const& tex);
	void setBackColor(int x);

	static const int Width = 1920;//ori:640
	static const int Height = 1200;//ori:480

	static std::shared_ptr<Screen> Screen;
	static std::shared_ptr<BackGround> Back;
	static const std::string heads[];
	static const std::string bodies[];
	static const std::string worlds[];
	static const std::string obstacles[];
	static void setBody(int x);
	static void setHead(int x);
	static int getBody();
	static int getHead();
	static bool adventure;
	static int world;

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	
	std::vector<sf::Texture> Obstacle;
	
	static const sf::Time TimePerFrame;

	static int body;
	static int head;
};
}


#endif