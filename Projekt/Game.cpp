#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Global_variables.h"
#include "Map.h"
#include "Character.h"
#include "Camera.h"
#include <iostream>

void Game::update(sf::RenderWindow& window)
{
    unsigned short mapNumber =0;
    const unsigned short numberOfMaps = 3;  //iloœæ map
    std::string mapName = "";

    Map map; //Inicjalizowanie mapy

    Camera camera;

    Character character;

    Menu menu;

    std::vector<sf::Sprite> map_sprites;

    bool dj = 0;

    while (restart == false && window.isOpen())
    {
        if (character.nextRound)
        {
            map_sprites.clear();
            map.Powers.clear();
            map.Enemies.clear();
            mapNumber++;
            if (mapNumber > numberOfMaps)
            {
                menu.win = true;
            }
            else
            {
                mapName = "Images/mapa" + std::to_string(mapNumber) + ".png";
                character.respawnPosition = map.load_from_file(mapName); //wczytanie mapy z pliku
                character.set_xy(character.respawnPosition);
                character.nextRound = false;
            }
        }
        else
        {
            if (character.respawn)
            {
                character.respawn = false;
                character.set_xy(character.respawnPosition);
                map_sprites.clear();
                map.Powers.clear();
                map.Enemies.clear();
                map.load_from_file(mapName);
            }


            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::R)
                    {
                        restart = true;
                    }
                }
            }

            window.clear(sf::Color(68, 142, 228));
            window.setView(camera.view);


            for (int i = 0; i < map.Enemies.size(); i++)    //pêtla przeciwników
            {
                map.Enemies[i]->update(map, character);
                map.Enemies[i]->draw(window);

                if (map.Enemies[i]->onMap() == false)
                {
                    map.Enemies.erase(map.Enemies.begin() + i);
                    
                }
            }


            map_sprites = map.draw(window); //funkcja draw zwraca vektor z spritami bloków mapy

            for (auto it = map.Powers.begin(); it != map.Powers.end(); it++) {
                window.draw(*it);
            }

            if (character.getLives() != 0 && menu.win == false)
            {
                character.draw(window);
                character.update(map, window, camera);
                camera.update(map, character);
            }
          

            dj = character.power_ups(map.Powers);
            character.movement(map_sprites, dj);

            menu.draw(window, character, camera);



            window.display();
        }
    }
}
