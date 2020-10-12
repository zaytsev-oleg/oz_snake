#pragma once
#include <windows.h>

const size_t FOOD_SIZE  = 15;
const size_t SNAKE_SIZE = FOOD_SIZE + 2;

enum VECTOR { UNSET = 0, LEFT_TO_RIGHT, RIGHT_TO_LEFT, BOTTOM_TOP, TOP_BOTTOM };

enum COLORS
{
	EMPTY = 0,
	RED   = RGB(0xff, 0, 0),
	GREEN = RGB(0, 0xff, 0),
	BLUE  = RGB(0, 0, 0xff)
};

struct BOARD
{
	size_t w;
	size_t h;
};

struct MY_COORDS
{
	size_t x;
	size_t y;

	COLORS color;
};