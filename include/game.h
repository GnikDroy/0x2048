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

/**
 * @brief Initializes the SDL window.
 *
 * When two pointers to the pointer of window and renderer are provided,
 * the function initializes both values with the values of created window
 * and renderer. 
 * 
 * If initialization is failed it may display error to stderr but
 * does not exit inside the function.
 * 
 * @param window The window of the game.
 * @param renderer The renderer for the game
 * @return If the initialization was successful.
 */
bool initSDL(SDL_Window **window, SDL_Renderer** renderer);

/**
 * @brief Destroyes and closes the SDL window and closes SDK_ttk.
 *
 * Frees up resource by destroying the SDL window.
 * 
 * @param window The window of the game.
 */
void closeSDL(SDL_Window** window);

/**
 * @brief Draws text centered inside the rect. 
 *
 * When two pointers to the pointer of window and renderer are provided,
 * the function initializes both values with the values of created window
 * and renderer. 
 * 
 * If initialization is failed it may display error to stderr but
 * does not exit.
 * 
 * @param renderer The renderer for the game
 * @param font The font for the text
 * @param text The text to write
 * @param rect The SDL_Rect object inside which text is written
 * @param color The color of the text
 */
void draw_text(SDL_Renderer* renderer,TTF_Font* font,const char* text, SDL_Rect rect, SDL_Color color);

/**
 * @brief Draws white text centered inside a rect. 
 *
 * Same as draw_text(..., SDL_Color White)
 * 
 * @param renderer The renderer for the game
 * @param font The font for the text
 * @param text The text to write
 * @param rect The SDL_Rect object inside which text is written
 */
void draw_white_text(SDL_Renderer* renderer,TTF_Font* font,const char* text, SDL_Rect rect);


/**
 * @brief Clears the window screen.
 *
 * Fills a color to entire screen.
 * 
 * @param renderer The renderer for the game
 */
void clear_screen(SDL_Renderer* renderer);


/**
 * @brief Draws black text centered inside the window. 
 *
 * @param renderer The renderer for the game
 * @param size The size for the text
 * @param text The text to write
 */
void display_text(SDL_Renderer* renderer,const char* text,int size);


/**
 * @brief Draws the game tiles. 
 *
 * It draws the SIZE*SIZE game tiles to the window.
 * 
 * @param renderer The renderer for the game
 * @param font The font for the tiles
 * @param board The game board.
 */
void draw_board(SDL_Renderer* renderer, Board board, TTF_Font* font);

/**
 * @brief Draws the new game button. 
 *
 * It draws the new game button to the bottom corner.
 * 
 * @param renderer The renderer for the game
 * @param font The font for the button
 * @param board The game board. Needed to reset game.
 */
void draw_button(SDL_Renderer* renderer, Board board, TTF_Font* font);

/**
 * @brief Handles the action of New Game button. 
 *
 * Resets the game board for a new game, if the correct mouse event 
 * had occured.
 * Function is run if left mouse button is released 
 * 
 * @param e The mouse event
 * @param board The game board.
 */
void button_handler(SDL_Event e, Board board);

/**
 * @brief Draws the current game score
 *
 * It draws the current game score to the window
 * 
 * @param renderer The renderer for the game
 * @param font The font for the tiles
 * @param board The game board.
 */
void draw_score(SDL_Renderer* renderer, Board board, TTF_Font* font);

/**
 * @brief Draws everything for the game and renders it to screen. 
 *
 * It calls clear_screen(),draw_board(),draw_score() and draw_button()
 * and also renders it to screem.
 * 
 * @param renderer The renderer for the game
 * @param font The font for the tiles
 * @param board The game board.
 */
void render_game(SDL_Renderer* renderer, Board board, TTF_Font* font);

/**
 * @brief This is the main game loop that handles all events and drawing 
 * 
 * @param renderer The renderer for the game
 * @param board The game board.
 */
void game_loop(Board board,SDL_Renderer* renderer);

/**
 * @brief Handles keyboard presses that correspond with the arrowkeys. 
 * 
 * It transforms the game board according to the keypresses.
 * It also checks if the game has been finished, draws game over screen 
 * and resets the board if game over. 
 * 
 * @param renderer The renderer for the game
 * @param e A Keyup event.
 * @param board The game board.
 */
void handle_move(SDL_Event e, Board board, SDL_Renderer * renderer);

