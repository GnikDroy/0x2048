/**
 * @file styles.h
 * @author Gnik Droy
 * @brief File containing tile colors and related structs.
 *
 */
#pragma once
/** @struct COLOR
 *  @brief This structure defines a RBGA color
 *  All values are stored in chars.
 * 
 *  @var COLOR::r
 *  The red value 
 *  @var COLOR::g
 *  The green value 
 *  @var COLOR::b 
 *  The blue value
 *  @var COLOR::a 
 *  The alpha value
 * 
 */

//Screen dimension constants

/** @def SCREEN_WIDTH
 * The width of the window
 */
#define SCREEN_WIDTH 500

/** @def SCREEN_HEIGHT
 * The height of the window
 */
#define SCREEN_HEIGHT 600

/** @def SCREEN_PAD
 * The padding to use while drawing elements to window
 */
#define SCREEN_PAD 10

//FONT settings

/** @def FONT_PATH
 * The path to the ttf font used by the game.
 */
#define FONT_PATH "UbuntuMono-R.ttf"

/** @def TITLE_FONT_SIZE
 * The font size used while displaying "2048" at the start of game.
 */
#define TITLE_FONT_SIZE 200

/** @def GOVER_FONT_SIZE
 * The font size used while displaying "Game Over" at the end of game.
 */
#define GOVER_FONT_SIZE 100 //Game Over font size

/** @def CELL_FONT_SIZE
 * The font size used while displaying each number inside the cells
 */
#define CELL_FONT_SIZE 40

struct COLOR
{
    char r;
    char g;
    char b;
    char a;
};

/** The background color used by the application  */
struct COLOR g_bg = {211, 204, 201, 255};

/** The text color used by the ui elemets (dark only). draw_text_white()
 *  is used to draw white text.
 */
struct COLOR g_fg = {80, 80, 80, 255};

/** The background color used by the new game button  */
struct COLOR g_button_bg = {255, 153, 102, 255};

/** The background color used by the score field  */
struct COLOR g_score_bg = {143, 122, 102, 255};

/** The colors used by the tiles
 *  They are according to exponent.
 *  Example: exponent of 1 will use g_COLORS[1]
 */
struct COLOR g_COLORS[] = {
    {230, 227, 232, 255},
    {255, 127, 89, 255},
    {224, 74, 69, 255},
    {237, 207, 114, 255},
    {65, 216, 127, 255},
    {54, 63, 135, 255},
    {78, 89, 178, 255},
    {109, 118, 191, 255},
    {84, 47, 132, 255},
    {125, 77, 188, 255},
    {163, 77, 188, 255},
    {176, 109, 196, 255},
    {0, 102, 204, 255},
    {0, 153, 255, 255},
    {51, 153, 255, 255},
    {153, 204, 255, 255},
    {102, 255, 102, 255}};
