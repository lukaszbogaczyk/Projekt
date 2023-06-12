#pragma once
#include "Global_variables.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include "WallEnemy.h"
#include "Camera.h"

class Camera;
class Character
{
	sf::Texture texture;
	sf::Sprite sprite;
	float x;
	float y;
	unsigned short lives;
	bool double_jump_orange;
	bool low_gravity;
	sf::Font font;
	float velocity_x;
	float velocity_y;
	unsigned short lg_timer;
	bool jump;
	bool end_jump;
	bool double_jump_red;


public:
	Character();
	sf::RectangleShape rect;

	void draw(sf::RenderWindow& _window);
	void set_xy(float X, float Y);
	void change_x(float X, std::vector<sf::Sprite> map_sprites);
	void change_y(float Y, std::vector<sf::Sprite> map_sprites, float& vel);
	bool on_ground(std::vector<sf::Sprite> map_sprites);
	void change_lives(const short &change);
	bool power_ups(std::vector<sf::CircleShape>& powers);
	void update(Map& _map, sf::RenderWindow& _window, Camera& _camera);
	void movement(std::vector<sf::Sprite> map_sprites, bool dj);
	friend class Camera;
	friend class WallEnemy;
	friend class UnkillableEnemy;
};