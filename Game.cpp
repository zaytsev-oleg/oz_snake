#include <cstdlib>

#include "Game.h"

void InitGame(GAME* pGame, BOARD* pBoard)
{
	pGame->snake.size = 1;
	
	size_t x = pBoard->w / 2 - 1;
	size_t y = pBoard->h / 2 - 1;

	pGame->snake.coords[0].x = x;
	pGame->snake.coords[0].y = y;
	pGame->snake.coords[0].color = GREEN;

	for (size_t i = 1; i < SNAKE_SIZE; i++)
	{
		pGame->snake.coords[i].x = x + i;
		pGame->snake.coords[i].y = y;
		pGame->snake.coords[i].color = EMPTY;
	}

	for (size_t i = 0; i < FOOD_SIZE; i++)
	{
		size_t rand_x = rand() % pBoard->w;
		size_t rand_y = rand() % pBoard->h;

		bool isDuplicate = false;

		for (size_t j = 0; j < i; j++)
		{
			if (pGame->food.coords[j].x == rand_x && pGame->food.coords[j].y == rand_y)
			{
				isDuplicate = true;
				break;
			}
		}

		if (isDuplicate)
		{
			i--;
			continue;
		}

		pGame->food.coords[i].x = rand_x;
		pGame->food.coords[i].y = rand_y;

		pGame->food.coords[i].color = RED;
	}

	pGame->snake.vector = UNSET;
	pGame->pBoard = pBoard;
}

void UpdateMatrix(int** pp, MY_COORDS* coords, size_t n)
{
	for (size_t i = n; i > 0; i--)
	{
		pp[coords[i - 1].y][coords[i - 1].x] = static_cast<int>(coords[i - 1].color);
	}
}

void UpdateMatrix(int** pp, GAME* pGame)
{
	SNAKE* snake = &pGame->snake;
	FOOD* food   = &pGame->food;

	if ((snake->size - 1) < FOOD_SIZE)
	{
		for (size_t i = 0; i < FOOD_SIZE; i++)
		{
			if (food->coords[i].color == EMPTY)
			{
				continue;
			}

			if (food->coords[i].x == snake->coords[0].x && 
				food->coords[i].y == snake->coords[0].y)
			{
				food->coords[i].color = EMPTY;
				snake->coords[snake->size++].color = GREEN;

				break;
			}
		}

		UpdateMatrix(pp, food->coords, FOOD_SIZE);
	}

	UpdateMatrix(pp, snake->coords, snake->size + 1);
}

void UpdateGame(GAME* pGame, char myChar)
{
	SNAKE* snake = &pGame->snake;
	BOARD* board = pGame->pBoard;

	if (myChar == 'a')
	{
		if (snake->vector == RIGHT_TO_LEFT)
		{
			return;
		}

		for (size_t i = SNAKE_SIZE - 1; i > 0 ; i--)
		{
			snake->coords[i].x = snake->coords[i - 1].x;
			snake->coords[i].y = snake->coords[i - 1].y;
		}

		if (snake->coords[0].x)
		{
			snake->coords[0].x -= 1;
		}
		else
		{
			snake->coords[0].x = board->w - 1;
		}

		snake->vector = LEFT_TO_RIGHT;
	}

	if (myChar == 'd')
	{
		if (snake->vector == LEFT_TO_RIGHT)
		{
			return;
		}

		for (size_t i = SNAKE_SIZE - 1; i > 0; i--)
		{
			snake->coords[i].x = snake->coords[i - 1].x;
			snake->coords[i].y = snake->coords[i - 1].y;
		}

		if (snake->coords[0].x < board->w - 1)
		{
			snake->coords[0].x += 1;
		}
		else
		{
			snake->coords[0].x = 0;
		}

		snake->vector = RIGHT_TO_LEFT;
	}

	if (myChar == 'w')
	{
		if (snake->vector == TOP_BOTTOM)
		{
			return;
		}

		for (size_t i = SNAKE_SIZE - 1; i > 0; i--)
		{
			snake->coords[i].x = snake->coords[i - 1].x;
			snake->coords[i].y = snake->coords[i - 1].y;
		}

		if (snake->coords[0].y)
		{
			snake->coords[0].y -= 1;
		}
		else
		{
			snake->coords[0].y = board->h - 1;
		}

		snake->vector = BOTTOM_TOP;
	}

	if (myChar == 's')
	{
		if (snake->vector == BOTTOM_TOP)
		{
			return;
		}

		for (size_t i = SNAKE_SIZE - 1; i > 0; i--)
		{
			snake->coords[i].x = snake->coords[i - 1].x;
			snake->coords[i].y = snake->coords[i - 1].y;
		}

		if (snake->coords[0].y < board->h - 1)
		{
			snake->coords[0].y += 1;
		}
		else
		{
			snake->coords[0].y = 0;
		}

		snake->vector = TOP_BOTTOM;
	}
}