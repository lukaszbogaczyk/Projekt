#include "WallEnemy.h"
#include "UnkillableEnemy.h"
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
	sf::FloatRect characterRect = _character.sprite.getGlobalBounds();
	characterRect.top += 40;
	characterRect.height = 20;
	characterRect.left += 10;
	characterRect.width -= 20;


	if (alive)
	{

		if (sprite.getGlobalBounds().intersects(characterRect))
		{
			alive = false;
			sprite.setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
			sprite.setRotation(180);
		}
		else if (sprite.getGlobalBounds().intersects(_character.sprite.getGlobalBounds()))
		{
			_character.change_lives(-1);
		}

		for (int i = 0; i < _map.Enemies.size(); i++)
		{
			if (WallEnemy* enemy = dynamic_cast<WallEnemy*>(_map.Enemies[i].get()))
			{
				if (this != enemy && sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds()))
				{
					direction *= -1;
				}
			}
			else if (UnkillableEnemy* enemy = dynamic_cast<UnkillableEnemy*>(_map.Enemies[i].get()))
			{
				if (sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds()))
				{
					direction *= -1;
				}
			}
		}

		sf::FloatRect rect = sf::FloatRect(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE + 2);
		if (_map.colision({ Cell::Brick, Cell::Spike}, rect))
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
