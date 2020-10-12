#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#include "Game.h"
#include "GraphicsLib.h"

#define stop __asm  nop

int main()
{
	srand(time(0));

	StartDemo();
	
	pause(1000);

	BOARD board;
	board.w = 20;
	board.h = 20;

	SetDimensions(board.h, board.w);

	int *p   = new int[board.h * board.w];
	int **pp = new int*[board.h];

	for (size_t i = 0; i < board.h; i++)
	{
		pp[i] = p + i * board.w;
	}

	for (size_t i = 0; i < board.h; i++)
	{
		for (size_t j = 0; j < board.w; j++)
		{
			pp[i][j] = EMPTY;
		}
	}
		
	DrawBalls(p, board.h, board.w);
	
	GAME game;

	InitGame(&game, &board);
	UpdateMatrix(pp, &game);
	DrawBalls(p, board.h, board.w);

	char myChar;
	
	do
	{
		myChar = 0;
		pause(50);
		
		if (_kbhit())
		{
			myChar = _getch();

			UpdateGame(&game, myChar);
			UpdateMatrix(pp, &game);

			DrawBalls(p, board.h, board.w);
		}
	} while (toupper(myChar) != 'Q');

	std::cout << "FinishDemo\n";
	std::cin.get();

	FinishDemo();

	delete[] pp;
	delete[] p;
}
 