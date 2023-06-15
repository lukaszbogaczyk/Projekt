#pragma once
#include <SFML/Graphics.hpp>
#include "Global_variables.h"
#include "Map.h"
#include "Character.h"
#include "Camera.h"

class Game
{
public:
	bool restart = false;
	void update(sf::RenderWindow& window);
};

