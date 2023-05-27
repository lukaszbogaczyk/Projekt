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
    map.load_from_file("Images/mapa.png");   //wczytanie mapy z pliku


    Camera camera;

    Character character;
    float velocity_x = 0;
    float velocity_y = 0;

    std::vector<sf::Sprite> map_sprites;


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
                if (event.key.code == sf::Keyboard::D)
                {
                    character.set_double_jump(1);

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

        character.draw(window);
        camera.update(map, character);



        character.change_x(velocity_x, map_sprites);//zmiana pozycji
        character.change_y(velocity_y, map_sprites);

        if (velocity_y < MAX_PLAYER_FALL_VELOCITY) {   //grawitacja
            velocity_y += gravity;
        }

        for (int i = 0; i < map.Enemies.size(); i++)
        {
            map.Enemies[i]->update(map);
            map.Enemies[i]->draw(window);
        }

        window.display();
    }
    std::cout << map.Enemies.size();

    return 0;
}