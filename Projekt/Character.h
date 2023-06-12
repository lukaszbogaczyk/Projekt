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
	bool double_jump_orange;
	unsigned short checkTime = 0;
	bool double_jump;
	bool low_gravity;
	bool checkpoint = true;
	sf::Font font;
	float velocity_x;
	float velocity_y;
	unsigned short lg_timer;
	bool jump;
	bool end_jump;
	bool double_jump_red;
	bool leftMoving;
	void animation();
	void textDisplay(sf::RenderWindow& _window, Camera& _camera);

	sf::Clock clock;
	sf::Time time;
	
	//animacja
	const unsigned short numberOfFrames = 3;
	unsigned short frameWidth = 0;
	unsigned short currentFrame = 0;
	float animationSpeed = 0.2f; 
	float elapsed = 0.0f; 
	unsigned short frameHeight = 1;
	bool isMoving = false;

public:
	Character();
	sf::RectangleShape rect;
	sf::Vector2f respawnPosition;
	bool respawn = false;
	bool nextRound = true;

	void draw(sf::RenderWindow& _window);
	void set_xy(float X, float Y);
	void change_x(float X, std::vector<sf::Sprite> map_sprites);
	void change_y(float Y, std::vector<sf::Sprite> map_sprites, float& vel);
	bool on_ground(std::vector<sf::Sprite> map_sprites);
	void change_lives(const short &change);
	void set_xy(const sf::Vector2f& _vect);
	bool power_ups(std::vector<sf::CircleShape>& powers);
	void update(Map& _map, sf::RenderWindow& _window, Camera& _camera);
	void movement(std::vector<sf::Sprite> map_sprites, bool dj);
	unsigned short getLives() const;
	friend class Camera;
	friend class WallEnemy;
	friend class UnkillableEnemy;
	friend class Menu;
};