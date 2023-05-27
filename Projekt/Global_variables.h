#pragma once
#include <vector>
#include <array>

//Zmienne globalne

const unsigned short SCREEN_WIDTH = 800;	//Szerokoœæ ekranu
const unsigned short SCREEN_HEIGHT = 600;	//Wysokoœæ ekranu
const unsigned short CELL_SIZE = 50;		//Wielkoœæ komórek 50x50
const unsigned short PLAYER_X_VELOCITY = 3;
const unsigned short PLAYER_JUMP_VELOCITY = 8;
const unsigned short MAX_PLAYER_FALL_VELOCITY = 5;
const float GRAVITY = 0.2;






enum class Cell		//Enum z nazwami komórek
{
	Brick,
	Spike,
	Cloud,
	Empty
};

using mapVector = std::vector<std::array<Cell, SCREEN_HEIGHT / CELL_SIZE>>;		//Macierz zawierajca komórki mapy o wyskokoci 12 i szerokoci n, gdzie n to szerokoœæ mapy/wielkoœæ komórek