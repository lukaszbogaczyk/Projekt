#include <SFML/Graphics.hpp>
#include "Global_variables.h"
#include "Map.h"
#include "Character.h"
#include "Camera.h"
#include <iostream>
#include "Game.h"
#include <SFML/Audio.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "projekt");
    window.setFramerateLimit(60);   //60 FPS

    sf::Music music;
    music.openFromFile("Music/music.ogg");
    music.setLoop(true);
    music.setVolume(10);
    music.play();
    

    while (window.isOpen())
    {
        Game game;
        game.update(window);
    }

    return 0;
}