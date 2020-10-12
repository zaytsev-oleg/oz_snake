#pragma once

#include "Snake.h"
#include "Food.h"

struct GAME
{
	SNAKE  snake;
	FOOD   food;
	BOARD* pBoard;
};

void InitGame(GAME*, BOARD*);
void UpdateMatrix(int**, MY_COORDS*, size_t);
void UpdateMatrix(int**, GAME*);
void UpdateGame(GAME*, char);