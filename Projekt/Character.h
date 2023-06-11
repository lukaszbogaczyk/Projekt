#pragma once
#include "Global_variables.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include "WallEnemy.h"

class Character
{
	sf::Texture texture;
	sf::Sprite sprite;
	float x;
	float y;
	unsigned short lives;
	bool double_jump;
	bool low_gravity;

public:
	Character();
	sf::RectangleShape rect;
	float y_velocity;

	void draw(sf::RenderWindow& _window);
	void set_xy(float X, float Y);
	void change_x(float X, std::vector<sf::Sprite> map_sprites);
	void change_y(float Y, std::vector<sf::Sprite> map_sprites, float& vel);
	bool on_ground(std::vector<sf::Sprite> map_sprites);
	bool get_double_jump();
	void set_double_jump(bool change_double_jump);
	bool get_low_gravity();
	void set_low_gravity(bool change_low_gravity);
	void change_lives(short change);
	bool power_ups(std::vector<sf::CircleShape>& powers);
	friend class Camera;
	friend class WallEnemy;
};