/**
 * @file game.c
 * @author Gnik Droy
 * @brief File containing implementation for the game's gui.
 *
 */
#include "../include/styles.h"
#include "../include/game.h"
#include <time.h>
#include <stdlib.h>

bool initSDL(SDL_Window **gWindow,SDL_Renderer** gRenderer)
{
	TTF_Init();
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf(stderr, "SDL could not initialize: %s\n", SDL_GetError());
		return false;
	}
	*gWindow = SDL_CreateWindow( "2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( gWindow == NULL )
	{
		fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
		return false;
	}
	*gRenderer = SDL_CreateRenderer( *gWindow, -1, SDL_RENDERER_ACCELERATED );
	if( gRenderer == NULL )
	{
		fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
		SDLclose(gWindow);
		return false;
	}
	return true;
}

void draw_text(SDL_Renderer* gRenderer,TTF_Font* font,const char* text, SDL_Rect rect, SDL_Color color){
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, color); 
	SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
	SDL_Rect message_rect;
	
	TTF_SizeText(font, text, &message_rect.w, &message_rect.h);
	message_rect.x = rect.x+rect.w/2-message_rect.w/2;     
	message_rect.y = rect.y+rect.h/2-message_rect.h/2; 

	SDL_RenderCopy(gRenderer, Message, NULL, &message_rect); 
	SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);
}

void draw_text_white(SDL_Renderer* gRenderer,TTF_Font* font,const char* text, SDL_Rect rect)
{
	SDL_Color White = {255, 255, 255};
	draw_text(gRenderer,font,text,rect,White);
}


void SDLclose(SDL_Window** gWindow)
{
	SDL_DestroyWindow( *gWindow );
	*gWindow = NULL;
	TTF_Quit();
	SDL_Quit();
}

void SDLclear(SDL_Renderer* gRenderer)
{
	
	SDL_SetRenderDrawColor( gRenderer, g_bg.r,g_bg.g,g_bg.b,g_bg.a );
	SDL_RenderClear( gRenderer );

}

void display_text(SDL_Renderer* gRenderer,const char* text,int size)
{
	TTF_Font* font =NULL;
	font= TTF_OpenFont(FONT_PATH, size);
	if(font==NULL)
	{
		fprintf(stderr,"The required font was not found");
		exit(EXIT_FAILURE);
	}
	SDL_Color black = {g_fg.r,g_fg.g, g_fg.b};
	SDLclear(gRenderer);
	SDL_Rect rect = {SCREEN_PAD ,SCREEN_HEIGHT/4 , SCREEN_WIDTH-2*SCREEN_PAD , SCREEN_HEIGHT/2 };
	draw_text(gRenderer,font,text,rect,black);
	SDL_RenderPresent( gRenderer );
	SDL_Delay(1000);
	TTF_CloseFont(font);
}

void draw_matrix(SDL_Renderer* gRenderer, Matrix matrix, TTF_Font* font)
{
	int squareSize=(SCREEN_WIDTH - 2*SCREEN_PAD)/SIZE-SCREEN_PAD;

	for(int x=0;x<SIZE;x++)
	{
		for(int y=0;y<SIZE;y++)
		{
			SDL_Rect fillRect = { SCREEN_PAD+x*(squareSize+SCREEN_PAD), SCREEN_PAD+y*(squareSize+SCREEN_PAD), squareSize , squareSize };
			struct COLOR s=g_COLORS[matrix[y][x]];
			SDL_SetRenderDrawColor( gRenderer, s.r, s.g, s.b, s.a );		
			SDL_RenderFillRect( gRenderer, &fillRect );
			char str[15]; // 15 chars is enough for 2^16. But not for other exponents ;)
			sprintf(str, "%lu", pow_int(BASE,matrix[y][x]));

			if(matrix[y][x]==0)
			{
				 str[0]=' ';
				 str[1]='\0';
			 }
			draw_text_white(gRenderer,font,str,fillRect);
		}
	}
}



void handle_move(SDL_Event e, Matrix matrix, SDL_Renderer * gRenderer)
{
	if(is_game_over(matrix))
	{
		display_text(gRenderer,"Game Over",GOVER_FONT_SIZE);
		clear_matrix(matrix);
		add_random(matrix);
		return;
	}
	switch(e.key.keysym.sym)
	{
		case SDLK_UP: 
		move_y(matrix,0);
		break;
		case SDLK_DOWN: 
		move_y(matrix,1);
		break;
		case SDLK_LEFT: 
		move_x(matrix,0);
		break;
		case SDLK_RIGHT: 
		move_x(matrix,1);
		break;
		default:;
	}
}

void draw_button(SDL_Renderer* gRenderer, Matrix matrix, TTF_Font* font)
{
	char txt[]="New Game";
	SDL_Rect fillRect = { SCREEN_PAD/2 ,
							SCREEN_WIDTH+SCREEN_PAD ,
							SCREEN_WIDTH/2-2*SCREEN_PAD ,
							(SCREEN_HEIGHT-SCREEN_WIDTH)-2*SCREEN_PAD };
	SDL_SetRenderDrawColor( gRenderer,g_button_bg.r, g_button_bg.g, g_button_bg.b,g_button_bg.a );		
	SDL_RenderFillRect( gRenderer, &fillRect );
	draw_text_white(gRenderer,font,txt,fillRect);
				
}
void button_action(SDL_Event e, Matrix matrix)
{
	SDL_Rect draw_rect = { SCREEN_PAD/2 ,
							SCREEN_WIDTH+SCREEN_PAD ,
							SCREEN_WIDTH/2-2*SCREEN_PAD ,
							SCREEN_HEIGHT-SCREEN_WIDTH-2*SCREEN_PAD };
	if(e.button.button == SDL_BUTTON_LEFT &&
				e.button.x >= draw_rect.x &&
				e.button.x <= (draw_rect.x + draw_rect.w) &&
				e.button.y >= draw_rect.y &&
				e.button.y <= (draw_rect.y + draw_rect.h))
	{
		clear_matrix(matrix);
		add_random(matrix);
	}
}
void draw_score(SDL_Renderer* gRenderer, Matrix matrix, TTF_Font* font)
{
	char score[15]; //15 chars is enough for score.
	sprintf(score, "%lu", calculate_score(matrix));
	char scoreText[30]="Score:";
	strncat(scoreText,score,15);
	SDL_Rect fillRect = {   SCREEN_WIDTH/2+5,
							SCREEN_WIDTH+SCREEN_PAD,
							SCREEN_WIDTH/2-2*SCREEN_PAD,
							SCREEN_HEIGHT-SCREEN_WIDTH-2*SCREEN_PAD };
	SDL_SetRenderDrawColor( gRenderer,g_score_bg.r,g_score_bg.g,g_score_bg.b,g_score_bg.a );		
	SDL_RenderFillRect( gRenderer, &fillRect );
	draw_text_white(gRenderer,font,scoreText,fillRect);
				
}
void render_game(SDL_Renderer* gRenderer, Matrix matrix, TTF_Font* font)
{
	SDLclear(gRenderer);
  	draw_matrix(gRenderer,matrix,font);
   	draw_score(gRenderer,matrix,font);
  	draw_button(gRenderer,matrix,font);
	SDL_RenderPresent( gRenderer );
}

void gameLoop(Matrix matrix,SDL_Renderer* gRenderer)
{
	TTF_Font* font =NULL;
	font= TTF_OpenFont(FONT_PATH, CELL_FONT_SIZE);
	if(font==NULL)
	{
		fprintf(stderr,"The required font was not found");
		exit(EXIT_FAILURE);
	}

	render_game(gRenderer,matrix,font);
	
	bool quit=false;
	SDL_Event e;
	while (!quit)
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
			else if(e.type==SDL_KEYUP)
			{
				handle_move(e,matrix,gRenderer);
				//Redraw all portions of game
				render_game(gRenderer,matrix,font);
			}
			else if(e.type==SDL_MOUSEBUTTONUP)
			{
				button_action(e,matrix);
				render_game(gRenderer,matrix,font);
			}
		}
	}
	TTF_CloseFont(font);
	//No need to null out font.
}

/**
 * @brief The standard main function
 * 
 * Starts the game
 * 
 * @param argc Number of arguments
 * @param argv Arguments
 */
int main(int argc,char** argv)
{
	//Set up the seed 
	srand(time(NULL));
	
	//Set up the game matrix.
	unsigned char matrix[SIZE][SIZE];
	clear_matrix(matrix);
	add_random(matrix);
	
	//Init the SDL gui variables
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	if(!initSDL(&gWindow,&gRenderer)) exit(EXIT_FAILURE);
	
	display_text(gRenderer,"2048",TITLE_FONT_SIZE);
	gameLoop(matrix,gRenderer);
	
	//Releases all resource
	SDLclose(&gWindow);   
	return EXIT_SUCCESS;
}
