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
	if (base==2)
	{
		//Separate this because majority of the time you will
		//be using this and it is faster than anything else.
		return 1 << exponent;
	}
	else
	{
		//Elliptic curve point multiplication seems fun.
		//!!Implement Later!!
		unsigned long u=1;
		for(int x=0;x<exponent;x++) u*=base;
		return u;
	}
}

void clear_matrix(Matrix matrix)
{
	for (unsigned int x=0;x<SIZE;x++)
	{
		for(unsigned int y=0;y<SIZE;y++)
		{
			matrix[x][y]=0;
		}
	}
}

unsigned long calculate_score(Matrix matrix)
{
	unsigned long score=0;
	for (unsigned int x=0;x<SIZE;x++)
	{
		for(unsigned int y=0;y<SIZE;y++)
		{
			if(matrix[x][y]!=0)
			{
				score+=pow_int(BASE,matrix[x][y]);
			}
		}
	}
	return score;
}

void print_matrix(Matrix matrix, FILE* stream)
{
	for (unsigned int x=0;x<SIZE;x++)
	{
		for(unsigned int y=0;y<SIZE;y++)
		{
			if (matrix[x][y])
			{
				fprintf(stream,"%d," ,matrix[x][y]);
			} else{
				fprintf(stream,"-,");
			}
		}
		fprintf(stream,"\n");
	}
	fprintf(stream,"\n");
}

void add_random(Matrix matrix)
{
	unsigned int pos[SIZE*SIZE];
	unsigned int len=0;
	for(unsigned int x=0;x<SIZE;x++)
	{
		for (unsigned int y=0;y<SIZE;y++)
		{
			if (matrix[x][y]==0){
			   pos[len]=x*SIZE+y;
			   len++; 
			}
		}
	}
	unsigned int index=rand() % len;
	matrix[pos[index]/SIZE][pos[index]%SIZE] = 1;
}

bool is_game_over(Matrix matrix)
{
	for(unsigned int x=0;x<SIZE-1;x++)
	{
		for (unsigned int y=0;y<SIZE-1;y++)
		{
			if (  matrix[x][y]==matrix[x][y+1] ||
				  matrix[x][y]==matrix[x+1][y] ||
				  matrix[x][y]==0)
			{return false;}
		}
		if (matrix[x][SIZE-1] == matrix[x+1][SIZE-1] || 
			matrix[x][SIZE-1] == 0) return false;
		if (matrix[SIZE-1][x] == matrix[SIZE-1][x+1] ||
			matrix[SIZE-1][x] == 0) return false;
	}
	return true;
}

bool shift_x(Matrix matrix, bool opp)
{
	bool moved=false;
	int start=0,end=SIZE,increment=1;
	if (opp)
	{
		start=SIZE-1;
		end=-1;
		increment=-1;
	}
	for (int x=0;x<SIZE;x++)
	{
		int index=start;
		for(int y=start;y!=end;y+=increment)
		{
			if (matrix[x][y]!=0)
			{
				matrix[x][index]=matrix[x][y];
				if(index!=y) {
					matrix[x][y]=0;
					moved=true;
				}
				index+=increment;
			}
		}
	}
	return moved;
}
bool merge_x(Matrix matrix, bool opp)
{
	bool merged=false;
	int start=0,end=SIZE-1,increment=1;
	if (opp)
	{
		start=SIZE-1;
		end=0;
		increment=-1;
	}
	for (int x=0;x<SIZE;x++)
	{
		int index=start;
		for(int y=start;y!=end;y+=increment)
		{
			if(matrix[x][y]!=0)
			{
				if(matrix[x][y]==matrix[x][y+increment])
				{
					matrix[x][index]=matrix[x][y]+1;
					matrix[x][y+increment]=0;
					if(index!=y) matrix[x][y]=0;
					merged=true;
					index+=increment;
				}
				else
				{
					matrix[x][index]=matrix[x][y];
					if(index!=y) matrix[x][y]=0;
					index+=increment;
				}
			}
		}
		
		if(matrix[x][end]!=0)
		{
			matrix[x][index]=matrix[x][end];
			if(index!=end) matrix[x][end]=0;
		}
	}
	return merged;
}
bool merge_y(Matrix matrix, bool opp)
{
	bool merged=false;
	int start=0,end=SIZE-1,increment=1;
	if (opp)
	{
		start=SIZE-1;
		end=0;
		increment=-1;
	}
	for (int y=0;y<SIZE;y++)
	{
		int index=start;
		for(int x=start;x!=end;x+=increment)
		{
			if(matrix[x][y]!=0)
			{
				if(matrix[x][y]==matrix[x+increment][y])
				{
					matrix[index][y]=matrix[x][y]+1;
					matrix[x+increment][y]=0;
					if(index!=x) matrix[x][y]=0;
					index+=increment;
					merged=true;
				}
				else
				{
					matrix[index][y]=matrix[x][y];
					if(index!=x) matrix[x][y]=0;
					index+=increment;
				}
			}
		}
		if(matrix[end][y]!=0)
		{
			matrix[index][y]=matrix[end][y];
			if(index!=end) matrix[end][y]=0;
		}
		
	}
	return merged;
}
bool shift_y(Matrix matrix, bool opp)
{
	bool moved=false;
	int start=0,end=SIZE,increment=1;
	if (opp)
	{
		start=SIZE-1;
		end=-1;
		increment=-1;
	}
	for (int y=0;y<SIZE;y++)
	{
		int index=start;
		for(int x=start;x!=end;x+=increment)
		{
			if (matrix[x][y]!=0)
			{
				matrix[index][y]=matrix[x][y];
				if(index!=x)
				{ 
					matrix[x][y]=0;
					moved=true;
				}
				index+=increment;
			}
		}
	}
	return moved;
}


inline void move_y(Matrix matrix, bool opp)
{
	//Assigning values insted of evaluating directly to force both operations
	//Bypassing lazy 'OR' evaluation
	bool a=shift_y(matrix,opp),b=merge_y(matrix,opp);
	if( a||b) add_random(matrix);
}

inline void move_x(Matrix matrix, bool opp)
{
	//Assigning values insted of evaluating directly to force both operations
	//Bypassing lazy 'OR' evaluation
	bool a=shift_x(matrix,opp), b=merge_x(matrix,opp);
	if(a||b)add_random(matrix);
}
