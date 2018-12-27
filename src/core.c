#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../include/core.h"


void clear_matrix(unsigned char matrix[][SIZE])
{
    for (unsigned int x=0;x<SIZE;x++)
    {
        for(unsigned int y=0;y<SIZE;y++)
        {
            matrix[x][y]=0;
        }
    }
}

int calculate_score(unsigned char matrix[][SIZE])
{
    int score=0;
    for (unsigned int x=0;x<SIZE;x++)
    {
        for(unsigned int y=0;y<SIZE;y++)
        {
            if(matrix[x][y]!=0)
            {
            	score+=pow(BASE,matrix[x][y]);
            }
        }
    }
    return score;
}

void print_matrix(unsigned char matrix[][SIZE],FILE* stream)
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

void add_random(unsigned char matrix[][SIZE])
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

bool is_game_over(unsigned char matrix[][SIZE])
{
    for(unsigned int x=0;x<SIZE-1;x++)
    {
        for (unsigned int y=0;y<SIZE-1;y++)
        {
            if (  matrix[x][y]==matrix[x][y+1] ||
                  matrix[x][y]==matrix[x+1][y] ||
                  matrix[x][y]==0)
            {return 0;}
        }
        if( matrix[x][SIZE-1]==matrix[x+1][SIZE-1] || 
            matrix[x][SIZE-1]==0) return 0;
        if( matrix[SIZE-1][x]==matrix[SIZE-1][x+1] ||
            matrix[SIZE-1][x]==0) return 0;
    }
    return 1;
}

bool shift_x(unsigned char matrix[][SIZE], bool opp)
{
    bool moved=0;
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
                    moved=1;
                }
                index+=increment;
            }
        }
    }
    return moved;
}
bool merge_x(unsigned char matrix[][SIZE],bool opp)
{
    bool merged=0;
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
                    merged=1;
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
bool merge_y(unsigned char matrix[][SIZE],bool opp)
{
    bool merged=0;
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
                    merged=1;
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
bool shift_y(unsigned char matrix[][SIZE],bool opp)
{
    bool moved=0;
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
                    moved=1;
                }
                index+=increment;
            }
        }
    }
    return moved;
}


inline void move_y(unsigned char matrix[][SIZE],bool opp)
{
    //Assigning values insted of evaluating directly to force both operations
    //Bypassing lazy 'OR' evaluation
    bool a=shift_y(matrix,opp),b=merge_y(matrix,opp);
    if( a||b) add_random(matrix);
}

inline void move_x(unsigned char matrix[][SIZE],bool opp)
{
    //Assigning values insted of evaluating directly to force both operations
    //Bypassing lazy 'OR' evaluation
    bool a=shift_x(matrix,opp), b=merge_x(matrix,opp);
    if(a||b)add_random(matrix);
}
