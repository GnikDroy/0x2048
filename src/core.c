/**
 * @file core.c
 * @author Gnik Droy
 * @brief File containing implementation of the core game.
 *
 */
#include <stdlib.h>
#include <time.h>
#include "../include/core.h"

unsigned long pow_int(int base, int exponent)
{
	if (base == 2)
	{
		//Separate this because majority of the time you will
		//be using this and it is faster than anything else.
		return 1 << exponent;
	}
	else
	{
		//Elliptic curve point multiplication seems fun.
		//!!Implement Later!!
		unsigned long u = 1;
		for (int x = 0; x < exponent; x++)
			u *= base;
		return u;
	}
}

void clear_board(Board board)
{
	for (unsigned int x = 0; x < SIZE; x++)
	{
		for (unsigned int y = 0; y < SIZE; y++)
		{
			board[x][y] = 0;
		}
	}
}

unsigned long calculate_score(const Board board)
{
	unsigned long score = 0;
	for (unsigned int x = 0; x < SIZE; x++)
	{
		for (unsigned int y = 0; y < SIZE; y++)
		{
			if (board[x][y] != 0)
			{
				score += pow_int(BASE, board[x][y]);
			}
		}
	}
	return score;
}

void print_board(const Board board, FILE *stream)
{
	for (unsigned int x = 0; x < SIZE; x++)
	{
		for (unsigned int y = 0; y < SIZE; y++)
		{
			if (board[x][y])
			{
				fprintf(stream, "%d,", board[x][y]);
			}
			else
			{
				fprintf(stream, "-,");
			}
		}
		fprintf(stream, "\n");
	}
	fprintf(stream, "\n");
}

void add_random(Board board)
{
	unsigned int pos[SIZE * SIZE];
	unsigned int len = 0;
	for (unsigned int x = 0; x < SIZE; x++)
	{
		for (unsigned int y = 0; y < SIZE; y++)
		{
			if (board[x][y] == 0)
			{
				pos[len] = x * SIZE + y;
				len++;
			}
		}
	}
	unsigned int index = rand() % len;
	board[pos[index] / SIZE][pos[index] % SIZE] = 1;
}

bool is_game_over(const Board board)
{
	for (unsigned int x = 0; x < SIZE - 1; x++)
	{
		for (unsigned int y = 0; y < SIZE - 1; y++)
		{
			if (board[x][y] == board[x][y + 1] ||
				board[x][y] == board[x + 1][y] ||
				board[x][y] == 0)
			{
				return false;
			}
		}
		if (board[x][SIZE - 1] == board[x + 1][SIZE - 1] ||
			board[x][SIZE - 1] == 0)
			return false;
		if (board[SIZE - 1][x] == board[SIZE - 1][x + 1] ||
			board[SIZE - 1][x] == 0)
			return false;
	}
	return true;
}

bool shift_x(Board board, bool opp)
{
	bool moved = false;
	int start = 0, end = SIZE, increment = 1;
	if (opp)
	{
		start = SIZE - 1;
		end = -1;
		increment = -1;
	}
	for (int x = 0; x < SIZE; x++)
	{
		int index = start;
		for (int y = start; y != end; y += increment)
		{
			if (board[x][y] != 0)
			{
				board[x][index] = board[x][y];
				if (index != y)
				{
					board[x][y] = 0;
					moved = true;
				}
				index += increment;
			}
		}
	}
	return moved;
}
bool merge_x(Board board, bool opp)
{
	bool merged = false;
	int start = 0, end = SIZE - 1, increment = 1;
	if (opp)
	{
		start = SIZE - 1;
		end = 0;
		increment = -1;
	}
	for (int x = 0; x < SIZE; x++)
	{
		int index = start;
		for (int y = start; y != end; y += increment)
		{
			if (board[x][y] != 0)
			{
				if (board[x][y] == board[x][y + increment])
				{
					board[x][index] = board[x][y] + 1;
					board[x][y + increment] = 0;
					if (index != y)
						board[x][y] = 0;
					merged = true;
					index += increment;
				}
				else
				{
					board[x][index] = board[x][y];
					if (index != y)
						board[x][y] = 0;
					index += increment;
				}
			}
		}

		if (board[x][end] != 0)
		{
			board[x][index] = board[x][end];
			if (index != end)
				board[x][end] = 0;
		}
	}
	return merged;
}
bool merge_y(Board board, bool opp)
{
	bool merged = false;
	int start = 0, end = SIZE - 1, increment = 1;
	if (opp)
	{
		start = SIZE - 1;
		end = 0;
		increment = -1;
	}
	for (int y = 0; y < SIZE; y++)
	{
		int index = start;
		for (int x = start; x != end; x += increment)
		{
			if (board[x][y] != 0)
			{
				if (board[x][y] == board[x + increment][y])
				{
					board[index][y] = board[x][y] + 1;
					board[x + increment][y] = 0;
					if (index != x)
						board[x][y] = 0;
					index += increment;
					merged = true;
				}
				else
				{
					board[index][y] = board[x][y];
					if (index != x)
						board[x][y] = 0;
					index += increment;
				}
			}
		}
		if (board[end][y] != 0)
		{
			board[index][y] = board[end][y];
			if (index != end)
				board[end][y] = 0;
		}
	}
	return merged;
}
bool shift_y(Board board, bool opp)
{
	bool moved = false;
	int start = 0, end = SIZE, increment = 1;
	if (opp)
	{
		start = SIZE - 1;
		end = -1;
		increment = -1;
	}
	for (int y = 0; y < SIZE; y++)
	{
		int index = start;
		for (int x = start; x != end; x += increment)
		{
			if (board[x][y] != 0)
			{
				board[index][y] = board[x][y];
				if (index != x)
				{
					board[x][y] = 0;
					moved = true;
				}
				index += increment;
			}
		}
	}
	return moved;
}

inline void move_y(Board board, bool opp)
{
	//Assigning values insted of evaluating directly to force both operations
	//Bypassing lazy 'OR' evaluation
	bool a = shift_y(board, opp), b = merge_y(board, opp);
	if (a || b)
		add_random(board);
}

inline void move_x(Board board, bool opp)
{
	//Assigning values insted of evaluating directly to force both operations
	//Bypassing lazy 'OR' evaluation
	bool a = shift_x(board, opp), b = merge_x(board, opp);
	if (a || b)
		add_random(board);
}
