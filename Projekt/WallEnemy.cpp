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
	sprite.setPosition(x, y);
}

void WallEnemy::draw(sf::RenderWindow& _window)
{
	
	_window.draw(sprite);
}

void WallEnemy::update(Map& _map, Character& _character)
{
	if (sprite.getGlobalBounds().intersects(_character.sprite.getGlobalBounds()) && _character.y_velocity != 0)
	{
		alive = false;
		//sprite.setRotation(180);
		//std::cout << "alive:false";
	}
	else if (sprite.getGlobalBounds().intersects(_character.sprite.getGlobalBounds()))
	{
		_character.change_lives(-1);
	}

	if (alive)
	{
		sf::FloatRect rect = sf::FloatRect(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE + 2);

		bool colision_with_oder_enemy = false;
		for (int i = 0; i < _map.Enemies.size(); i++)
		{
			WallEnemy* enemy = dynamic_cast<WallEnemy*>(_map.Enemies[i].get());
			if (this != enemy && sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds()))
			{
				direction *= -1;
			}
		}

		if (_map.colision({ Cell::Brick, Cell::Spike }, rect))
		{
			y_velocity = 0;
			rect = sf::FloatRect(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE - 2);
			if (_map.colision({ Cell::Brick, Cell::Spike }, rect))
			{
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
		}
		else
		{
			y_velocity = std::min<float>(y_velocity + gravity, max_gravity);
		}

		y += y_velocity;
		x += speed * direction;

		sprite.setPosition(x, y);
	}
	else
	{
		if (y >= SCREEN_HEIGHT + 50)
		{
			on_map = false;
		}
		else
		{
			y += 1;
			sprite.setPosition(x, y);
		}
	}
	
}

bool WallEnemy::onMap()
{
	return on_map;
}
