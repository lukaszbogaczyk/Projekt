#pragma once
#include <vector>
#include <array>

//Zmienne globalne

const unsigned short SCREEN_WIDTH = 800;	//Szeroko�� ekranu
const unsigned short SCREEN_HEIGHT = 600;	//Wysoko�� ekranu
const unsigned short CELL_SIZE = 50;		//Wielko�� kom�rek 50x50
const unsigned short PLAYER_X_VELOCITY = 3;
const unsigned short PLAYER_JUMP_VELOCITY = 8;
const unsigned short MAX_PLAYER_FALL_VELOCITY = 5;
const float GRAVITY = 0.2;






enum class Cell		//Enum z nazwami kom�rek
{
	Brick,
	Spike,
	Cloud,
	Empty
};

using mapVector = std::vector<std::array<Cell, SCREEN_HEIGHT / CELL_SIZE>>;		//Macierz zawierajca kom�rki mapy o wyskokoci 12 i szerokoci n, gdzie n to szeroko�� mapy/wielko�� kom�rek