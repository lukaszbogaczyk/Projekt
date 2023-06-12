#pragma once
#include "Global_variables.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include "WallEnemy.h"
#include "Camera.h"
#include "Menu.h"

class Camera;
class Character
{
	sf::Texture texture;
	sf::Sprite sprite;
	float x;
	float y;
	unsigned short lives;
	unsigned short checkTime = 0;
	bool double_jump;
	bool low_gravity;
	bool checkpoint = true;
	sf::Font font;
	sf::Clock clock;
	sf::Time time;

public:
	Character();
	sf::RectangleShape rect;
	sf::Vector2f respawnPosition;
	bool respawn = false;
	bool nextRound = true;
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
	void change_lives(const short &change);
	void set_xy(const sf::Vector2f& _vect);
	bool power_ups(std::vector<sf::CircleShape>& powers);
	void update(Map& _map, sf::RenderWindow& _window, Camera& _camera);
	unsigned short getLives() const;
	friend class Camera;
	friend class WallEnemy;
	friend class UnkillableEnemy;
	friend class Menu;
};