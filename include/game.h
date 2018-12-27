/**
 * @file game.h
 * @author Gnik Droy
 * @brief File containing function declarations for the game gui.
 *
 */
#pragma once
#include "../include/core.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 600

/**
 * @brief Initializes the SDL window.
 *
 * When two pointers to the pointer of gWindow and gRenderer are provided,
 * the function initializes both values with the values of created window
 * and renderer. 
 * 
 * If initialization is failed it may display error to stderr but
 * does not exit.
 * 
 * @param gWindow The window of the game.
 * @param gRenderer The renderer for the game
 * @return If the initialization was successful.
 */
bool initSDL(SDL_Window **gWindow,SDL_Renderer** gRenderer);

/**
 * @brief Closes the SDL window.
 *
 * Frees up resource by closing destroying the SDL window 
 * 
 * @param gWindow The window of the game.
 */
void SDLclose(SDL_Window* gWindow);

/**
 * @brief Draws text centered inside a rect. 
 *
 * When two pointers to the pointer of gWindow and gRenderer are provided,
 * the function initializes both values with the values of created window
 * and renderer. 
 * 
 * If initialization is failed it may display error to stderr but
 * does not exit.
 * 
 * @param gRenderer The renderer for the game
 * @param font The font for the text
 * @param text The text to write
 * @param rect The SDL_Rect object inside which text is written
 * @param color The color of the text
 */
void draw_text(SDL_Renderer* gRenderer,TTF_Font* font,const char* text, SDL_Rect rect, SDL_Color color);

/**
 * @brief Draws white text centered inside a rect. 
 *
 * Same as draw_text(..., SDL_Color White)
 * 
 * @param gRenderer The renderer for the game
 * @param font The font for the text
 * @param text The text to write
 * @param rect The SDL_Rect object inside which text is written
 */
void draw_text_white(SDL_Renderer* gRenderer,TTF_Font* font,const char* text, SDL_Rect rect);


/**
 * @brief Clears the window
 *
 * Fills a color to entire screen.
 * 
 * @param gRenderer The renderer for the game
 */
void SDLclear(SDL_Renderer* gRenderer);


/**
 * @brief Draws black text centered inside the window. 
 *
 * @param gRenderer The renderer for the game
 * @param size The size for the text
 * @param text The text to write
 */
void display_text(SDL_Renderer* gRenderer,const char* text,int size);


/**
 * @brief Draws the game tiles. 
 *
 * It draws the SIZE*SIZE game tiles to the window.
 * 
 * @param gRenderer The renderer for the game
 * @param font The font for the tiles
 * @param matrix The game matrix.
 */
void draw_matrix(SDL_Renderer* gRenderer,unsigned char matrix[][SIZE], TTF_Font* font);

/**
 * @brief Draws the new game button. 
 *
 * It draws the new game button to the bottom corner.
 * 
 * @param gRenderer The renderer for the game
 * @param font The font for the button
 * @param matrix The game matrix. Needed to reset game.
 */
void draw_button(SDL_Renderer* gRenderer,unsigned char matrix[][SIZE], TTF_Font* font);

/**
 * @brief Handles the action of New Game button. 
 *
 * Resets the game board for a new game, if the correct mouse event 
 * had occured.
 * Function is run if left mouse button is released 
 * 
 * @param gRenderer The renderer for the game
 * @param e The mouse event
 * @param matrix The game matrix.
 */
void button_action(SDL_Event e,unsigned char matrix[][SIZE]);

/**
 * @brief Draws the current game score
 *
 * It draws the current game score to the window
 * 
 * @param gRenderer The renderer for the game
 * @param font The font for the tiles
 * @param matrix The game matrix.
 */
void draw_score(SDL_Renderer* gRenderer,unsigned char matrix[][SIZE], TTF_Font* font);

/**
 * @brief Draws everything for the game and renders it to screen. 
 *
 * It calls SDLclear(),draw_matrix(),draw_score() and draw_button()
 * and also renders it to screem.
 * 
 * @param gRenderer The renderer for the game
 * @param font The font for the tiles
 * @param matrix The game matrix.
 */
void render_game(SDL_Renderer* gRenderer,unsigned char matrix[][SIZE], TTF_Font* font);

/**
 * @brief This is the main game loop that handles all events and drawing 
 * 
 * @param gRenderer The renderer for the game
 * @param font The font for the tiles
 * @param matrix The game matrix.
 */
void gameLoop(unsigned char matrix[][SIZE],SDL_Renderer* gRenderer);

/**
 * @brief Handles keyboard presses that correspond with the arrowkeys. 
 * 
 * It transforms the game matrix according to the keypresses.
 * It also checks if the game has been finished, draws game over screen 
 * and resets the board if game over. 
 * 
 * @param gRenderer The renderer for the game
 * @param font The font for the tiles
 * @param matrix The game matrix.
 */
void handle_move(SDL_Event e,unsigned char matrix[][SIZE], SDL_Renderer * gRenderer);

