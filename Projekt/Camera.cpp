#include "Camera.h"

Camera::Camera()
{
	view.setCenter(sf::Vector2f(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f));
	view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT+400));
	x = SCREEN_WIDTH * 0.5f;
	y = SCREEN_HEIGHT * 0.5f;
}

void Camera::update(Map& map, Character& character)
{
	if ((((character.x) + (character.sprite.getGlobalBounds().width / 2)) >= ((SCREEN_WIDTH / 2) + (character.sprite.getGlobalBounds().width / 2))) && ((((character.x) + (character.sprite.getGlobalBounds().width / 2)) <= (map.map_width - ((SCREEN_WIDTH / 2) - (character.sprite.getGlobalBounds().width / 2))))))
	{
		x = character.x;
	}
	else if(character.x <= SCREEN_WIDTH / 2)
	{
		x = SCREEN_WIDTH/2;	
	}
	else
	{
		x = map.map_width - (SCREEN_WIDTH / 2);
	}
	view.setCenter(x, y);
}