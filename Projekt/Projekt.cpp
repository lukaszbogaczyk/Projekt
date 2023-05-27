#include <SFML/Graphics.hpp>
#include "Global_variables.h"
#include "Map.h"
#include "Character.h"
#include "Camera.h"

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

    std::vector<sf::CircleShape> powers;
    unsigned short lg_timer = 300;

    sf::CircleShape power_up1;
    power_up1.setPosition(150, 450);
    power_up1.setRadius(10);
    power_up1.setFillColor(sf::Color(200, 0, 0));
    powers.emplace_back(power_up1);

    power_up1.setPosition(200, 300);
    power_up1.setFillColor(sf::Color(200, 0, 0));
    powers.emplace_back(power_up1);

    power_up1.setPosition(500, 300);
    power_up1.setFillColor(sf::Color(0, 0, 200));
    powers.emplace_back(power_up1);

    power_up1.setPosition(600, 200);
    power_up1.setFillColor(sf::Color(0, 200, 0));
    powers.emplace_back(power_up1);


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

        for (auto it = powers.begin(); it != powers.end(); it++) {
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
        character.power_ups(powers);


        window.display();
    }

    return 0;
}