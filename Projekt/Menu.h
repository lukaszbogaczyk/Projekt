#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Camera.h"

class Camera;
class Menu
{
	sf::Texture gameOver;
	sf::Texture winTexture;

public:
	bool win = false;
	Menu();
	void draw(sf::RenderWindow& _window, Character &_character, Camera &_camera);
};

