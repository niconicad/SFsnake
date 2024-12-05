#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "BackGround.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
{
	//设置主页文字
	font_.loadFromFile("Fonts/test.ttf");

	for(int i{0};i<3;i++)
	{
		text_.emplace_back();
		text_[i].setFont(font_);
		text_[i].setCharacterSize(70);
		if(!Game::adventure)
			text_[i].setFillColor(sf::Color(100,149,237));
		else
			text_[i].setFillColor(sf::Color(0,153,76));
	}

	text_[0].setString("Play");

	if(!Game::adventure)
		text_[1].setString("Adventure!!");
	else
		text_[1].setString("Relax~~");

	text_[2].setString("Quit");

	for(int i{0};i<3;i++)
	{
		sf::FloatRect textBounds = text_[i].getLocalBounds();
		text_[i].setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
		text_[i].setPosition(Game::Width / 2, Game::Height / 2 + i * 110);
	}

	if(Game::adventure)
	{
		text_.emplace_back();
		text_[3].setString("Snowfield");
		text_[3].setCharacterSize(30);
		text_[3].setFont(font_);
		text_[3].setFillColor(sf::Color(0,153,76));
		text_[3].setPosition(sf::Vector2f(SampleEdge/2,SampleEdge*5/3));
	}

	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setCharacterSize(200);
	snakeText_.setOutlineThickness(10.f);
	if(!Game::adventure)
	{
		snakeText_.setFillColor(sf::Color(100,149,237));
		snakeText_.setOutlineColor(sf::Color(176,224,230));
	}
	else
	{
		snakeText_.setFillColor(sf::Color(0,153,76));
		snakeText_.setOutlineColor(sf::Color(153,255,51));
	}
	//标题运动
	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);	

	//设置背景图片
	if (!Game::adventure)
		menuTex.loadFromFile("Image/menuback.png");
	else
		menuTex.loadFromFile("Image/menuback2.png");
	menuBack.setTexture(menuTex);
	menuBack.setScale(Game::Width / (float)menuTex.getSize().x, Game::Height / (float)menuTex.getSize().y);
	initSample();
}

void MenuScreen::initSample()
{
	//设置地图材质样例
	BackSample.setSize(sf::Vector2f(SampleEdge,SampleEdge));
	BackSample.setFillColor(sf::Color::White);
	BackSample.setOutlineThickness(-10.f);
	BackSample.setOutlineColor(sf::Color(173,216,230));
	BackSample.setPosition(sf::Vector2f(SampleEdge/2,SampleEdge/2));

	TexSample.setSize(sf::Vector2f(SampleEdge,SampleEdge));
	TexSample.setFillColor(sf::Color::White);
	TexSample.setOutlineThickness(-10.f);
	TexSample.setOutlineColor(sf::Color(173,216,230));
	TexSample.setPosition(sf::Vector2f(SampleEdge*2,SampleEdge/2));

	
	BackColor = 0;
	BackTex = 0;
	style = 0;//冒险模式的材质信号
	if(!Game::adventure)//非冒险模式的初始设置
		tex.loadFromFile("Image/Grid.png");
	else//冒险模式的初始设置
	{
		tex.loadFromFile(Game::worlds[0]);
		BackSample.setTexture(&tex);
	}

	//设置头像和身体样例
	h=0;
	head.loadFromFile(Game::heads[0]);
	body.loadFromFile(Game::bodies[0]);
	headSample.setTexture(&head);
	bodySample.setTexture(&body);
	headSample.setRadius(SampleEdge/2);
	bodySample.setRadius(SampleEdge/2);
	headSample.setOutlineThickness(10.f);
	bodySample.setOutlineThickness(10.f);
	headSample.setOutlineColor(sf::Color(173,216,230));
	bodySample.setOutlineColor(sf::Color(173,216,230));
	headSample.setPosition(sf::Vector2f(Game::Width - 3 * SampleEdge,SampleEdge/2));
	bodySample.setPosition(sf::Vector2f(Game::Width - 3 * SampleEdge / 2,SampleEdge / 2));

}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	static int delay = 0;
	const int time = 5;

	auto p = sf::Mouse::getPosition(window);//相对于当前窗口
	for(int i=0;i<3;i++)
		if(text_[i].getGlobalBounds().contains(p.x,p.y))
		{
			text_[i].setScale(1.5,1.5);
			text_[i].setOutlineColor(sf::Color(255,255,255));
			text_[i].setOutlineThickness(5.f);
			
		}
		else
		{
			text_[i].setScale(1.0f,1.0f);
			text_[i].setOutlineThickness(0.f);
		}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//将按下与之前的放于上面状态区分开，防止数据过多
	{
		if(text_[0].getGlobalBounds().contains(p.x,p.y))
		{
			if(!Game::adventure)
			{
				Game::Back->setTexture(BackTex);
				Game::Back->setColor(BackColor);
			}	//先放纹理再上色
			else
			{
				Game::world = style;
				Game::Back->setColor(0);//清除颜色
				Game::Back->setTexture(style + 2);
			}
			Game::setBody(h);
			Game::setHead(h);
			Game::Screen = std::make_shared<GameScreen>();
		}
		else if(text_[1].getGlobalBounds().contains(p.x,p.y) && !delay)//防止切换过快
		{
			Game::adventure = !Game::adventure;
			delay = time;
			Game::Screen = std::make_shared<MenuScreen>();
		}
		else if(text_[2].getGlobalBounds().contains(p.x,p.y))
			window.close();
		else if(BackSample.getGlobalBounds().contains(p.x,p.y) && !delay)
		{
			if(!Game::adventure)
				changeColor();
			else
				changeStyle();
			delay = time;
		}
		else if(TexSample.getGlobalBounds().contains(p.x,p.y) && !delay)
		{
			if(!Game::adventure)
				changeTex();
			delay = time;
		}
		else if(headSample.getGlobalBounds().contains(p.x,p.y) && !delay)
		{
			changeHead();
			changeBody();
			delay = time;
		}
	}
	if(delay>0)
		--delay;
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(menuBack);
	for(const auto& i : text_)
		window.draw(i);
	window.draw(snakeText_);
	window.draw(BackSample);
	if(!Game::adventure)
		window.draw(TexSample);
	window.draw(headSample);
	window.draw(bodySample);
}

void MenuScreen::changeColor()
{
	BackColor = (BackColor + 1) % 3;
	switch(BackColor)
    {
    case 0:
        BackSample.setFillColor(sf::Color::White);
        break;
    case 1:
        BackSample.setFillColor(sf::Color(255,128,0));
        break;
    case 2:
        BackSample.setFillColor(sf::Color(255,192,203));
        break;
    default:
        break;
    }
}

void MenuScreen::changeTex()
{
	BackTex = (BackTex + 1) % 2;
	switch (BackTex)
	{
	case 0:
		TexSample.setTexture(nullptr);
		TexSample.setFillColor(sf::Color::White);
		break;
	case 1:
		TexSample.setTexture(&tex);
		break;
	default:
		break;
	}
}

void MenuScreen::changeHead()
{
	h = (h + 1) % 4;
	head.loadFromFile(Game::heads[h]);
}

void MenuScreen::changeBody()
{
	body.loadFromFile(Game::bodies[h]);
}

void sfSnake::MenuScreen::changeStyle()
{
	style = (style + 1) % 3;
	tex.loadFromFile(Game::worlds[style]);
	BackSample.setTexture(&tex);
	snakeText_.setString("Snake!");
	switch (style)
	{
	case 0:
		text_[3].setString("Snowfield");
		break;
	case 1:
		text_[3].setString("Cave");
		break;
	case 2:
		text_[3].setString("Grassland");
		break;
	default:
		break;
	}
}
