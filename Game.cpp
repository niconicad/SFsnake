#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "MenuScreen.h"
#include "Game.h"
#include "BackGround.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 15.f);
int Game::head = 0;
int Game::body = 0;
bool Game::adventure = false;
int Game::world = 0;

const std::string Game::heads[] = {"Image/greenhead.png","Image/xiaoxin.png",
"Image/xiaoai.png","Image/monkeyking.png"};
const std::string Game::bodies[] = {"Image/greenbody.png","Image/xiaobai.png",
"Image/zhennan.png","Image/monkey.png"};
const std::string Game::obstacles[] = 
{	
	"Image/obstacle/ob1.png","Image/obstacle/ob2.png","Image/obstacle/ob3.png",
	"Image/obstacle/ob4.png","Image/obstacle/ob5.png","Image/obstacle/ob6.png",
	"Image/obstacle/ob7.png","Image/obstacle/ob8.png","Image/obstacle/ob9.png"
};
const std::string Game::worlds[] = 
{
	"Image/world/w1.png","Image/world/w2.png","Image/world/w3.png"
};

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();
std::shared_ptr<BackGround> Game::Back = std::make_shared<BackGround>();

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	bgMusic_.openFromFile("Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window_.clear();
	Game::Screen->render(window_);
	window_.display();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}

void Game::setBody(int x)
{
	body = x;
}

void Game::setHead(int x)
{
	head = x;
}

int Game::getBody()
{
	return body;
}

int Game::getHead()
{
	return head;
}