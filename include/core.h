/**
 * @file core.h
 * @author Gnik Droy
 * @brief File containing function declarations for the core game.
 *
 */
#pragma once
#include <stdio.h>
#include <stdbool.h>

/** @def SIZE
 * The size of the board
 */
#define SIZE 4

/** @def BASE
 * The base used for the exponents.
 */
#define BASE 2

/** The game board type */
typedef unsigned char Board[][SIZE];

/**
 * @brief Unsigned integer exponentiation.
 * 
 * @param base Base
 * @param exponent Exponent
 * @return Base^Exponent
 */
unsigned long pow_int(int base, int exponent);

/**
 * @brief Write the game board to the stream.
 *
 * The board is written as a comma seperated list of indices.
 * Each row is seperated by a '\n' character.
 * Each empty cell is represented by '-' character.
 * 
 * The indices can be used to calculate the actual integers.
 * 
 * You can use the constant stdout from <stdio.h> for printing to 
 * standard output
 * 
 * @param board The game board that is to be printed.
 * @param stream The file stream to use.
 */
void print_board(Board board, FILE *stream);

/**
 * @brief Checks if there are possible moves left on the game board.
 *
 * Checks for both movement and combinations of tiles.
 * 
 * @param board The game board.
 * @return Either 0 or 1
 */
bool is_game_over(Board board);

/**
 * @brief This clears out the game board
 *
 * This zeros out the entire game board.
 * 
 * @param board The game board.
 */
void clear_board(Board board);

/**
 * @brief Adds a value of 1 to random place to the board.
 *
 * The function adds 1 to a random place in the board.
 * The 1 is placed in empty tiles. i.e tiles containing 0.
 * 1 is kept since you can use raise it with BASE to get required value.
 * Also it keeps the size of board to a low value.
 * 
 * NOTE: It has no checks if there are any empty places for keeping 
 * the random value.
 * If no empty place is found a floating point exception will occur.
 */
void add_random(Board board);

/**
 * @brief Calculates the score of a game board
 *
 * It scores the board in a simple way.
 * Each element in the board is used as exponents of the BASE. And the 
 * sum of all BASE^element is returned.
 * 
 * @return An integer that represents the current score
 */
unsigned long calculate_score(Board board);

/**
 * @brief Shifts the game board in X direction.
 *
 * It shifts all the elements of the game board in the X direction.
 * If the direction is given as 0, it shifts the game board in the left
 * direction. Any other non zero value shifts it to the right direction.
 * 
 * @param board The game board.
 * @param opp The direction of the shift.
 * 
 * @return If the shift was successful
 */
bool shift_x(Board board, bool opp);

/**
 * @brief Merges the elements in X direction.
 *
 * It merges consecutive successive elements of the game board in the X direction.
 * If the direction is given as 0, it merges the game board to the left
 * direction. Any other non zero value merges it to the right direction.
 * 
 * @param board The game board.
 * @param opp The direction of the shift.
 * 
 * @return If the merge was successful
 */
bool merge_x(Board board, bool opp);

/**
 * @brief Moves the elements in X direction.
 *
 * It simply performs shift_x() and merge_x().
 * If either of them were successful, it also calls add_random()
 * 
 * @param board The game board.
 * @param opp The direction of the move.
 * 
 */
void move_x(Board board, bool opp);

/**
 * @brief Shifts the game board in Y direction.
 *
 * It shifts all the elements of the game board in the Y direction.
 * If the direction is given as 0, it shifts the game board in the top
 * direction. Any other non-zero value shifts it to the bottom.
 * 
 * @param board The game board.
 * @param opp The direction of the shift.
 * 
 * @return If the shift was successful
 */
bool shift_y(Board board, bool opp);

/**
 * @brief Merges the elements in Y direction.
 *
 * It merges consecutive successive elements of the game board in the Y direction.
 * If the direction is given as 0, it merges the game board to the top
 * direction. Any other non zero value merges it to the bottom.
 * 
 * @param board The game board.
 * @param opp The direction of the shift.
 * 
 * @return If the merge was successful
 */
bool merge_y(Board board, bool opp);

/**
 * @brief Moves the elements in Y direction.
 *
 * It simply performs shift_y() and merge_y().
 * If either of them were successful, it also calls add_random()
 * 
 * @param board The game board.
 * @param opp The direction of the move.
 * 
 */
void move_y(Board board, bool opp);
