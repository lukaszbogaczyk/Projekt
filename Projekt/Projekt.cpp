#include <SFML/Graphics.hpp>
#include "Global_variables.h"
#include "Map.h"
#include "Character.h"
#include "Camera.h"
#include <iostream>

int main()
{




    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "projekt");
    window.setFramerateLimit(60);   //60 FPS

    Map map; //Inicjalizowanie mapy
    map.load_from_file("Images/mapa.png"); //wczytanie mapy z pliku


    Camera camera;

    Character character;
    float velocity_x = 0;
    float velocity_y = 0;

    std::vector<sf::Sprite> map_sprites;

    unsigned short lg_timer = 300;


    while (window.isOpen())
    {
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
                if (event.key.code == sf::Keyboard::Left)//zmienianie prędkości postaci
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
                        velocity_y = -PLAYER_JUMP_VELOCITY;
                    }
                    else if (character.get_double_jump()) {
                        velocity_y = -PLAYER_JUMP_VELOCITY;
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
            }

        }

        window.clear(sf::Color(29, 210, 231));
        window.setView(camera.view);


        map_sprites = map.draw(window); //funkcja draw zwraca vektor z spritami bloków mapy

        for (auto it = map.Powers.begin(); it != map.Powers.end(); it++) {
            window.draw(*it);
        }
        character.draw(window);
        camera.update(map, character);



        character.change_x(velocity_x, map_sprites);//zmiana pozycji
        character.change_y(velocity_y, map_sprites);

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

        character.change_lives(-1);
        character.power_ups(map.Powers);

        for (int i = 0; i < map.Enemies.size(); i++)
        {
            map.Enemies[i]->update(map, character);
            map.Enemies[i]->draw(window);

            if (map.Enemies[i]->onMap() == false)
            {
                map.Enemies.erase(map.Enemies.begin() + i);
                std::cout << "erased\n";
            }
        }

        window.display();
    }

    return 0;
}