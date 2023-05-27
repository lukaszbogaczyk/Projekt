#include "Character.h"
#include "Global_variables.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

Character::Character() {
	texture.loadFromFile("Images/guy.png");//wczytanie z pliku
	x = 0;
	y = 0;
	lives = 3;
	double_jump = 0;
	low_gravity = 0;
	rect.setSize(sf::Vector2f(CELL_SIZE - 5, CELL_SIZE - 5));
}

bool Character::get_double_jump() {
	return double_jump;
}
void Character::set_double_jump(bool change_double_jump) {
	double_jump = change_double_jump;
}

bool Character::get_low_gravity() {
	return low_gravity;
}
void Character::set_low_gravity(bool change_low_gravity) {
	low_gravity = change_low_gravity;
}

void Character::draw(sf::RenderWindow& _window) {


	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE - 5, CELL_SIZE - 5));


	_window.draw(sprite);

}
void Character::change_x(float X, std::vector<sf::Sprite> map) {
	//zmienienie pozycji rect
	rect.setPosition(x + X, y);
	sf::RectangleShape r = rect;
	//sprawdzanie kolizji rect z blokami mapy
	if (std::none_of(map.begin(), map.end(), [r](sf::Sprite map_sprite) {return map_sprite.getGlobalBounds().intersects(r.getGlobalBounds());  })) {
		x += X;
	}

}

void Character::change_y(float Y, std::vector<sf::Sprite> map) {
	//zmienienie pozycji rect
	rect.setPosition(x, y + Y);
	sf::RectangleShape r = rect;
	//sprawdzanie kolizji rect z blokami mapy
	if (std::none_of(map.begin(), map.end(), [r](sf::Sprite map_sprite) {return map_sprite.getGlobalBounds().intersects(r.getGlobalBounds());  })) {
		y += Y;
	}
}
bool Character::on_ground(std::vector<sf::Sprite> map) {
	//zmienienie pozycji rect
	rect.setPosition(x, y + 6);
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

void Character::change_lives(short change) {
	if (change > 0) {
		lives += change;
	}
	else if (change < 0) {
		if (sprite.getGlobalBounds().top > SCREEN_HEIGHT) {
			lives += change;
			this->set_xy(0, 0);
			std::cout << lives << std::endl;
		}
	}
}

void Character::power_ups(std::vector<sf::CircleShape>& powers) {
	for (auto it = powers.begin(); it != powers.end(); it++) {
		if (sprite.getGlobalBounds().intersects(it->getGlobalBounds())) {
			if (it->getFillColor() == sf::Color(200, 0, 0)) {
				double_jump = 1;
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
		}

	}
}