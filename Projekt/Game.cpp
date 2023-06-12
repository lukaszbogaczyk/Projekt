#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Global_variables.h"
#include "Map.h"
#include "Character.h"
#include "Camera.h"
#include <iostream>

void Game::update(sf::RenderWindow& window)
{
    unsigned short mapNumber = 0;
    const unsigned short numberOfMaps = 3;  //iloœæ map
    std::string mapName = "";

    Map map; //Inicjalizowanie mapy

    Camera camera;

    Character character;

    Menu menu;
    float velocity_x = 0;
    float velocity_y = 0;
    bool jump = 0;
    bool end_jump = 1;

    std::vector<sf::Sprite> map_sprites;

    unsigned short lg_timer = 300;

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
                std::cout << mapName;
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


            if (jump && velocity_y > -PLAYER_JUMP_VELOCITY) {
                velocity_y += -PLAYER_JUMP_VELOCITY / 8;
                if (velocity_y <= -PLAYER_JUMP_VELOCITY)
                    jump = 0;
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
                    if (event.key.code == sf::Keyboard::R)
                    {
                        restart = true;
                    }
                    if (event.key.code == sf::Keyboard::Left)//zmienianie prêdkoœci postaci
                    {
                        velocity_x = -PLAYER_X_VELOCITY;
                    }
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        velocity_x = PLAYER_X_VELOCITY;
                    }
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        if (character.on_ground(map_sprites)) {
                            velocity_y += -PLAYER_JUMP_VELOCITY / 2;
                            jump = 1;
                            end_jump = 0;
                        }
                        else if (dj) {
                            velocity_y = -PLAYER_JUMP_VELOCITY / 2;
                            jump = 1;
                            end_jump = 0;
                        }
                        else if (character.get_double_jump() && end_jump) {
                            velocity_y = -PLAYER_JUMP_VELOCITY / 2;
                            jump = 1;
                            end_jump = 0;
                            character.set_double_jump(0);
                        }

                    }
                }

                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Left && velocity_x != PLAYER_X_VELOCITY) {
                        velocity_x = 0;
                    }
                    if (event.key.code == sf::Keyboard::Right && velocity_x != -PLAYER_X_VELOCITY) {
                        velocity_x = 0;
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        jump = 0;
                        end_jump = 1;
                    }
                }

            }
            character.y_velocity = 0;

            window.clear(sf::Color(29, 210, 231));
            window.setView(camera.view);


            for (int i = 0; i < map.Enemies.size(); i++)    //pêtla przeciwników
            {
                map.Enemies[i]->update(map, character);
                map.Enemies[i]->draw(window);

                if (map.Enemies[i]->onMap() == false)
                {
                    map.Enemies.erase(map.Enemies.begin() + i);
                    std::cout << "erased\n";
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
            



            character.change_x(velocity_x, map_sprites);//zmiana pozycji
            character.change_y(velocity_y, map_sprites, velocity_y);

            if (!jump) {
                if (velocity_y < MAX_PLAYER_FALL_VELOCITY && character.get_low_gravity()) {   //grawitacja
                    velocity_y += GRAVITY / 2;
                    lg_timer--;
                    if (lg_timer == 0) {
                        character.set_low_gravity(0);
                        lg_timer = 300;
                    }
                }
                else if (velocity_y < MAX_PLAYER_FALL_VELOCITY) {   //grawitacja
                    velocity_y += GRAVITY;
                }
            }

            dj = character.power_ups(map.Powers);

            menu.draw(window, character, camera);



            window.display();
        }
    }
}
