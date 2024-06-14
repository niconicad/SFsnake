#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"

namespace sfSnake
{
class MenuScreen : public Screen
{
public:
	MenuScreen();
	void initSample();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	void changeColor();
	void changeTex();
	void changeHead();
	void changeBody();

	void changeStyle();
	
	static constexpr float SampleEdge = 100.f;
private:
	sf::Font font_;
	sf::Text snakeText_;
	std::vector<sf::Text> text_;
	sf::RectangleShape BackSample;
	sf::RectangleShape TexSample;
	int BackColor = 0;
	int BackTex = 0;//0无 1网格
	sf::Texture tex;
	sf::Texture menuTex;
	sf::Sprite menuBack;
	sf::Texture head;//0 green 1xiaoxin 2xiaoai 3monkeyking
	sf::Texture body;
	int h;
	sf::CircleShape headSample;
	sf::CircleShape bodySample;
	int style;
};
}

#endif