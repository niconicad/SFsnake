#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <iostream>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(sf::Vector2f(0,-MoveDistance)), hit_(false)
{
	head.loadFromFile(Game::heads[Game::getHead()]);
	body.loadFromFile(Game::bodies[Game::getBody()]);
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Radius,
			Game::Height / 2 - (SnakeNode::Radius)),head));
	for (int i = 1; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::Radius,
			Game::Height / 2 - (SnakeNode::Radius) + (SnakeNode::Radius * 2 * i)),body));
	}
}

void Snake::handleInput(sf::RenderWindow &window)
{
	const float q = sqrt(2.f) / 2;
	//保持丝滑操作~
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			direction_ = sf::Vector2f(-MoveDistance * q,-MoveDistance * q);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			direction_ = sf::Vector2f(MoveDistance * q,-MoveDistance * q);
		else
			direction_ = sf::Vector2f(0,-MoveDistance);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			direction_ = sf::Vector2f(-MoveDistance * q,MoveDistance * q);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			direction_ = sf::Vector2f(MoveDistance * q,MoveDistance * q);
		else
			direction_ = sf::Vector2f(0,MoveDistance);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction_ = sf::Vector2f(-MoveDistance,0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction_ = sf::Vector2f(MoveDistance,0);
	else if (!posecount && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mpos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));//相对窗口的位置
		//if(mpos.x >= 0 && mpos.y >= 0 && mpos.x <= Game::Width && mpos.y <= Game::Height)
		//超出窗口不更新
		{
			sf::Vector2f rm = mpos -nodes_[0].getPosition();//相对蛇头的位置
			float dis = sqrt(double(rm.x * rm.x + rm.y * rm.y)); 
			if(dis)//重合不更新
				direction_ = sf::Vector2f(MoveDistance * rm.x / dis, MoveDistance * rm.y / dis);
		}
	}
	if(posecount)
	    posecount--;
	
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		switch (toRemove->getColor())
		{
		case 2:
			grow(3);
			break;
		case 3:
			grow(2);
			break;
		case 4:
			grow(1);
			break;
		default:
			break;
		}
		fruits.erase(toRemove);
	}
}

void Snake::grow(int x)
{
	// switch (direction_)
	// {
	// case Direction::Up:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	// 		nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));
	// 	break;
	// case Direction::Down:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	// 		nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height)));
	// 	break;
	// case Direction::Left:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width,
	// 		nodes_[nodes_.size() - 1].getPosition().y)));
	// 	break;
	// case Direction::Right:
	// 	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width,
	// 		nodes_[nodes_.size() - 1].getPosition().y)));
	// 	break;
	// }
	SnakeNode last = nodes_[nodes_.size() - 1],
			  last_s = nodes_[nodes_.size() - 2];
	sf::Vector2f direc = last_s.getPosition() - last.getPosition();
	for(int i{0};i<x;++i)
		nodes_.push_back(SnakeNode(last.getPosition() - direc,body));
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::is_hit() const
{
	return hit_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];
	//考虑浮点计算的浮动，从第三个身体点开始检测碰撞（经过测试较为合理）
	for (decltype(nodes_.size()) i = 4; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hit_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];
	//边界检测
	//去除左上黑边
	if (headNode.getPosition().x < 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y < 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
		nodes_[i].setRotation(nodes_.at(i - 1).getRotation());
	}

	nodes_[0].move(direction_);
 
	float x = direction_.x;
	float y = direction_.y;
	nodes_[0].setRotation(atan2f(y,x) * 180.f / M_PI + 90.f);
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto node{nodes_.rbegin()};node != nodes_.rend();node++)
		node->render(window);
}

void Snake::checkObstacleCollisions(std::vector<Obstacle>& obstacles)
{
	SnakeNode& headNode = nodes_[0];
	for (decltype(obstacles.size()) i = 0; i < obstacles.size(); ++i)
	{
		if (headNode.getBounds().intersects(obstacles[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hit_ = true;
		}
	}
}
