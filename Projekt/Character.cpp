#include "Character.h"
#include "Global_variables.h"
#include "Map.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

Character::Character() {
	texture.loadFromFile("Images/guy.png");//wczytanie z pliku
	x = 0;
	y = 0;
	lives = 3;
	double_jump_orange = 0;
	low_gravity = 0;
	rect.setSize(sf::Vector2f(CELL_SIZE - 5, CELL_SIZE - 5));
	font.loadFromFile("Fonts/Arial.ttf");
	velocity_x = 0;
	velocity_y = 0;
	lg_timer = 300;
	jump = 0;
	end_jump = 1;
	double_jump_red = 0;

}



void Character::draw(sf::RenderWindow& _window) {


	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE - 5, CELL_SIZE - 5));


	_window.draw(sprite);

}
void Character::change_x(float X, std::vector<sf::Sprite> map) {
	std::cout << sprite.getPosition().x << " | " << sprite.getPosition().y << std::endl;
	//zmienienie pozycji rect
	rect.setPosition(x + X, y);
	sf::RectangleShape r = rect;
	//sprawdzanie kolizji rect z blokami mapy
	if (std::none_of(map.begin(), map.end(), [r](sf::Sprite map_sprite) {return map_sprite.getGlobalBounds().intersects(r.getGlobalBounds());  })) {
		x += X;
	}

}

void Character::change_y(float Y, std::vector<sf::Sprite> map, float &vel) {
	//zmienienie pozycji rect
	rect.setPosition(x, y + Y);
	sf::RectangleShape r = rect;
	//sprawdzanie kolizji rect z blokami mapy
	if (std::none_of(map.begin(), map.end(), [r](sf::Sprite map_sprite) {return map_sprite.getGlobalBounds().intersects(r.getGlobalBounds());  })) {
		y += Y;
	}
	else {
		if (vel < 0) {
			vel = 0;
		}
	}
}
bool Character::on_ground(std::vector<sf::Sprite> map) {
	//zmienienie pozycji rect
	rect.setPosition(x, y + 10);
	sf::RectangleShape r = rect;
	//sprawdzanie kolizji rect z blokami mapy
	if (std::any_of(map.begin(), map.end(), [r](sf::Sprite map_sprite) {return map_sprite.getGlobalBounds().intersects(r.getGlobalBounds());  })) {
		return 1;
	}
	else { return 0; }
}

void Character::set_xy(float X, float Y) {
	//ustawienie pozycji x i y postaci
	x = X;
	y = Y;
}

void Character::set_xy(const sf::Vector2f& _vect)
{
	x = _vect.x;
	y = _vect.y;
}

unsigned short Character::getLives() const
{
	return lives;
}

void Character::change_lives(const short &change) 
{
	lives += change;
	if (change < 0)
	{
		respawn = true;
	}
}

bool Character::power_ups(std::vector<sf::CircleShape>& powers) {
	for (auto it = powers.begin(); it != powers.end(); it++) {
		if (sprite.getGlobalBounds().intersects(it->getGlobalBounds())) {
			if (it->getFillColor() == sf::Color(250, 100, 50)) {
				double_jump_orange = 1;
				powers.erase(it);
				it--;
			}
			if (it->getFillColor() == sf::Color(0, 0, 200)) {
				low_gravity = 1;
				powers.erase(it);
				it--;
			}
			if (it->getFillColor() == sf::Color(0, 200, 0)) {
				lives++;
				powers.erase(it);
				it--;
			}
			if (it->getFillColor() == sf::Color(200, 0, 0)) {
				return 1;
			}
		}

	}
	return 0;
}

void Character::update(Map& _map, sf::RenderWindow& _window, Camera& _camera)
{
	if (y >= _map.map_height)
	{
		change_lives(-1);
	}

	sf::FloatRect rect = sprite.getGlobalBounds();
	if (_map.colision({ Cell::Spike }, rect))
	{
		change_lives(-1);
	}

	if ((_map.colision({ Cell::Checkpoint }, rect)) && checkpoint == true)
	{
		respawnPosition = sf::Vector2f(x, y);
		checkpoint = false;
	}
	else
	{
		checkTime++;
		if (checkTime >= 360)
		{
			checkpoint = true;
			checkTime = 0;
		}

	}

	if (_map.colision({ Cell::Finish_flag }, rect))
	{
		nextRound = true;
	}


	//¯ycia
	std::wstringstream ws;
	ws << L"Iloœæ ¿yæ: " << lives;
	std::wstring message = ws.str();
	sf::Text text;
	text.setFont(font);
	text.setString(message);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Red);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(5);

	int x = floor(_camera.x + 220);
	int y = floor(_camera.y - 270);

	text.setPosition(x, y);
	_window.draw(text);


	//Czas
	time += clock.restart();
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(3) << time.asSeconds();
	std::string timeString = "Czas: " + oss.str();

	text.setString(timeString);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(5);

	x = floor(_camera.x-40);
	y = floor(_camera.y - 280);

	text.setPosition(x, y);
	_window.draw(text);
}



void Character::movement(std::vector<sf::Sprite> map_sprites,bool dj) {
	if (jump && velocity_y > -PLAYER_JUMP_VELOCITY) {
		velocity_y += -PLAYER_JUMP_VELOCITY / 8;
		if (velocity_y <= -PLAYER_JUMP_VELOCITY)
			jump = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity_x = -PLAYER_X_VELOCITY;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity_x = PLAYER_X_VELOCITY;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity_x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && end_jump) {
		if (this->on_ground(map_sprites)) {
			velocity_y += -PLAYER_JUMP_VELOCITY / 2;
			jump = 1;
			end_jump = 0;
		}
		else if (double_jump_red) {
			velocity_y = 0;
			velocity_y = -PLAYER_JUMP_VELOCITY / 2;
			jump = 1;
			end_jump = 0;
		}
		else if (double_jump_orange) {
			velocity_y = 0;
			velocity_y = -PLAYER_JUMP_VELOCITY / 2;
			jump = 1;
			end_jump = 0;
			double_jump_orange = 0;
		}
	}
	else {
		jump = 0;
		end_jump = 1;
	}

	this->change_x(velocity_x, map_sprites);//zmiana pozycji
	this->change_y(velocity_y, map_sprites, velocity_y);

	if (!jump) {
		if (velocity_y < MAX_PLAYER_FALL_VELOCITY && low_gravity) {   //grawitacja
			velocity_y += GRAVITY / 2;
			lg_timer--;
			if (lg_timer == 0) {
				low_gravity=0;
				lg_timer = 300;
			}
		}
		else if (velocity_y < MAX_PLAYER_FALL_VELOCITY) {   //grawitacja
			velocity_y += GRAVITY;
		}
	}

	double_jump_red = dj;
}