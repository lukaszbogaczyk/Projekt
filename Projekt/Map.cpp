#include "Map.h"
#include "Global_variables.h"
#include "WallEnemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Map::Map()
{	
	//brick
	brick_texture.loadFromFile("Images/brick.png");
	brick_texture.setSmooth(true);

	//spike
	spike_texture.loadFromFile("Images/spike.png");
	spike_texture.setSmooth(true);

	//cloud
	cloud_texture.loadFromFile("Images/cloud.png");
	cloud_texture.setSmooth(true);
}

std::vector<sf::Sprite> Map::draw(sf::RenderWindow& _window)
{
	std::vector<sf::Sprite> sprites;
	for (unsigned short i = 0; i < map.size(); i++)
	{
		for (unsigned short j = 0; j < map[i].size(); j++) //2 pêtle for przechodz¹ce przez ca³¹ macierz z map
		{
			switch (map[i][j])
			{
				case Cell::Empty:
				{
					continue;
				}
				case Cell::Brick:
				{
					sf::Sprite brick_sprite(brick_texture);
					brick_sprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
					_window.draw(brick_sprite);
					sprites.emplace_back(brick_sprite);	//wektor spritów
					break;
				}
				case Cell::Spike:
				{
					sf::Sprite spike_sprite(spike_texture);
					if (map[i - 1][j] == Cell::Brick && map[i + 1][j] != Cell::Brick)
					{
						spike_sprite.setRotation(90);
						spike_sprite.setPosition((i + 1) * CELL_SIZE, j * CELL_SIZE);
					}
					else if (map[i + 1][j] == Cell::Brick && map[i - 1][j] != Cell::Brick)
					{
						spike_sprite.setRotation(270);
						spike_sprite.setPosition(i * CELL_SIZE, (j + 1) * CELL_SIZE);
					}
					else
					{
						spike_sprite.setRotation(0);
						spike_sprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
					}
					_window.draw(spike_sprite);
					break;
				}
				case Cell::Cloud:
				{
					sf::Sprite cloud_sprite(cloud_texture);
					unsigned short x = (i * CELL_SIZE) - (cloud_sprite.getTextureRect().left + (cloud_sprite.getTextureRect().width / 2));
					unsigned short y = (j * CELL_SIZE) - (cloud_sprite.getTextureRect().top + (cloud_sprite.getTextureRect().height / 2));

					cloud_sprite.setPosition(x, y);
					_window.draw(cloud_sprite);
					break;
				}
				default:
				{
					std::cout << "default";
				}
			}
		}
	}
	return sprites;
}

void Map::load_from_file(std::string map_directory)
{
	sf::Image map_image;
	map_image.loadFromFile(map_directory);	//wczytanie mapy z pliku
	map.resize(map_image.getSize().x);	//zmiana wielkoci macierzy mapy do szerokoci mapy pobranej z pliku

	map_height = 50 * map_image.getSize().y;
	map_width = 50 * map_image.getSize().x;


	for (unsigned short i = 0; i < map.size(); i++)
	{
		for (unsigned short j = 0; j < map[i].size(); j++) //2 pêtle for przechodz¹ce przez ca³¹ macierz z map¹
		{
			if (map_image.getPixel(i, j) == sf::Color(0, 0, 0)) //jezeli na pozycji i,j wykryje czarny piksel dodaje do macierzy w tym miejscu Cell::Brick. W innym przypadku dodaje pust¹ komrkê Cell::Empty
			{
				map[i][j] = Cell::Brick;
			}
			else if (map_image.getPixel(i, j) == sf::Color(237, 28, 36))
			{
				map[i][j] = Cell::Spike;
			}
			else if (map_image.getPixel(i, j) == sf::Color(0, 162, 232))
			{
				map[i][j] = Cell::Cloud;
			}
			else if (map_image.getPixel(i, j) == sf::Color(163, 73, 164))
			{
				Enemies.emplace_back(std::make_unique<WallEnemy>(i * CELL_SIZE, j * CELL_SIZE));
			}
			else if (map_image.getPixel(i, j) == sf::Color(200, 0, 0))
			{
				sf::CircleShape circle;
				circle.setPosition(i * CELL_SIZE, j * CELL_SIZE);
				circle.setRadius(10);
				circle.setFillColor(sf::Color(200, 0, 0));
				Powers.emplace_back(circle);
			}
			else if (map_image.getPixel(i, j) == sf::Color(0, 200, 0))
			{
				sf::CircleShape circle;
				circle.setPosition(i * CELL_SIZE, j * CELL_SIZE);
				circle.setRadius(10);
				circle.setFillColor(sf::Color(0, 200, 0));
				Powers.emplace_back(circle);
			}
			else if (map_image.getPixel(i, j) == sf::Color(0, 0, 200))
			{
				sf::CircleShape circle;
				circle.setPosition(i * CELL_SIZE, j * CELL_SIZE);
				circle.setRadius(10);
				circle.setFillColor(sf::Color(0, 0, 200));
				Powers.emplace_back(circle);
			}
			else if (map_image.getPixel(i, j) == sf::Color(250, 100, 50))
			{
				sf::CircleShape circle;
				circle.setPosition(i * CELL_SIZE, j * CELL_SIZE);
				circle.setRadius(10);
				circle.setFillColor(sf::Color(250, 100, 50));
				Powers.emplace_back(circle);
			}
			else
			{
				map[i][j] = Cell::Empty;
			}
		}
	}
}

bool Map::colision(const std::vector<Cell>& cells, sf::FloatRect bounds)
{
	for (unsigned short a = std::max<short>(0, floor(bounds.left / CELL_SIZE)); a <= std::min<short>((map_width / CELL_SIZE), floor((bounds.left + bounds.width) / CELL_SIZE)); a++)
	{
		for (unsigned short b = std::max<short>(0, floor(bounds.top / CELL_SIZE)); b <= std::min<short>((map_height / CELL_SIZE), floor((bounds.top + bounds.height) / CELL_SIZE)); b++)
		{
			if (cells.end() != std::find(cells.begin(), cells.end(), map[a][b]))
			{
				return true;
			}
		}
	}
	return false;
}

