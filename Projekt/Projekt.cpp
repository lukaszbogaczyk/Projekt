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
    map.load_from_file("Images/mapa3.png"); //wczytanie mapy z pliku


    Camera camera;

    Character character;
    
    std::vector<sf::Sprite> map_sprites;

    

    
    character.set_xy(100, 502);
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
                
            }
            
            
            

        }
        

        window.clear(sf::Color(29, 210, 231));
        window.setView(camera.view);

        
        for (int i = 0; i < map.Enemies.size(); i++)    //pętla przeciwników
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
        character.draw(window);
        character.update(map, window, camera);
        camera.update(map, character);

bool double_jump = character.power_ups(map.Powers);

character.movement(map_sprites,double_jump);

        window.display();
    }

    return 0;
}