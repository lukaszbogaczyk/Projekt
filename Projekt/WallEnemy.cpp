#include "WallEnemy.h"
#include <iostream>
#include <algorithm>

WallEnemy::WallEnemy(float _x, float _y)
{
	x = _x;
	y = _y;
	texture.loadFromFile("Images/wallenemy.png");
	texture.setSmooth(true);
	sprite.setTexture(texture);
}

void WallEnemy::draw(sf::RenderWindow& _window)
{
	
	_window.draw(sprite);
}

void WallEnemy::update(Map& _map)
{
	sf::FloatRect rect = sf::FloatRect(x+1, y+1, CELL_SIZE-2, CELL_SIZE-2);

	if (_map.colision({Cell::Brick}, rect))
	{
		std::cout << "kolizjca";
		if (direction == 1)
		{
			direction = -1;
		}
		else
		{
			direction = 1;
		}
		y_velocity = 0;
	}
	
	rect = sf::FloatRect(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE + 1);
	if(_map.colision({ Cell::Brick }, rect))
	{
		y_velocity = 0;
	}
	else 
	{
		y_velocity = std::max<float>(y_velocity + gravity, max_gravity);
	}

	y += y_velocity;
	x += speed * direction;

	sprite.setPosition(x, y);
}
