#include "UnkillableEnemy.h"
#include <algorithm>

UnkillableEnemy::UnkillableEnemy(float _x, float _y)
{
	x = _x;
	y = _y;
	texture.loadFromFile("Images/unkillableenemy.png");
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}

void UnkillableEnemy::draw(sf::RenderWindow& _window)
{
	_window.draw(sprite);
}

void UnkillableEnemy::update(Map& _map, Character& _character)
{
	if (sprite.getGlobalBounds().intersects(_character.sprite.getGlobalBounds()))
	{
		_character.change_lives(-1);
	}


	for (int i = 0; i < _map.Enemies.size(); i++)
	{
		if (WallEnemy* enemy = dynamic_cast<WallEnemy*>(_map.Enemies[i].get()))
		{
			if (sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds()))
			{
				if (direction == 1)
				{
					direction = -1;
					sprite.setScale(1, 1);
					sprite.setOrigin(sprite.getLocalBounds().left, 0);
				}
				else
				{
					direction = 1;
					sprite.setScale(-1, 1);
					sprite.setOrigin(sprite.getLocalBounds().width, 0);
				}
			}
		}
		else if (UnkillableEnemy* enemy = dynamic_cast<UnkillableEnemy*>(_map.Enemies[i].get()))
		{
			if (this != enemy && sprite.getGlobalBounds().intersects(enemy->sprite.getGlobalBounds()))
			{
				if (direction == 1)
				{
					direction = -1;
					sprite.setScale(1, 1);
					sprite.setOrigin(sprite.getLocalBounds().left, 0);
				}
				else
				{
					direction = 1;
					sprite.setScale(-1, 1);
					sprite.setOrigin(sprite.getLocalBounds().width, 0);
				}
			}
		}
	}

	sf::FloatRect rect = sf::FloatRect(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE + 2);
	if (_map.colision({ Cell::Brick, Cell::Spike }, rect))
	{
		y_velocity = 0;
		rect = sf::FloatRect(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE - 2);
		if (_map.colision({ Cell::Brick, Cell::Spike }, rect))
		{
			if (direction == 1)
			{
				direction = -1;
				sprite.setScale(1, 1);
				sprite.setOrigin(sprite.getLocalBounds().left, 0);
			}
			else
			{
				direction = 1;
				sprite.setScale(-1, 1);
				sprite.setOrigin(sprite.getLocalBounds().width, 0);
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

bool UnkillableEnemy::onMap()
{
	return true;
}


