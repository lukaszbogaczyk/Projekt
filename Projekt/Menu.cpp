#include "Menu.h"
#include "Character.h"
#include "Camera.h"



Menu::Menu()
{
	gameOver.loadFromFile("Images/gameover.png");
	winTexture.loadFromFile("Images/win.png");
}

void Menu::draw(sf::RenderWindow& _window, Character& _character, Camera& _camera)
{
	if (win)
	{
		sf::Sprite sprite(winTexture);
		sf::Vector2f vec = sf::Vector2f(_camera.view.getCenter().x - 400, _camera.view.getCenter().y - 300);
		sprite.setPosition(vec);
		_window.draw(sprite);
	}
	else if (_character.lives == 0)
	{
		sf::Sprite gameoverSprite(gameOver);
		sf::Vector2f vec = sf::Vector2f(_camera.view.getCenter().x-400, _camera.view.getCenter().y-300);
		gameoverSprite.setPosition(vec);
		_window.draw(gameoverSprite);
	}
}
