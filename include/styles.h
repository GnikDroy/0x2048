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
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 600
#define SCREEN_PAD 10

//FONT settings
#define FONT_PATH "UbuntuMono-R.ttf"
#define TITLE_FONT_SIZE 200
#define GOVER_FONT_SIZE 100  //Game Over font size
#define CELL_FONT_SIZE 40

struct COLOR{
    char r;
    char g;
    char b;
    char a;
};
struct COLOR g_bg={211, 204, 201, 255};
struct COLOR g_fg={80, 80, 80, 255};
struct COLOR g_button_bg={255, 153, 102,255};
struct COLOR g_score_bg={143, 122, 102,255};

struct COLOR g_COLORS[]={
    {230, 227, 232,255},
    {255, 127, 89,255},
    {224, 74, 69,255},
    {237, 207, 114,255},
    {65, 216, 127,255},
    {54, 63, 135,255},
    {78, 89, 178,255},
    {109, 118, 191,255},
    {84, 47, 132,255},
    {125, 77, 188,255},
    {163, 77, 188,255},
    {176, 109, 196,255},
    {0, 102, 204,255},
    {0, 153, 255,255},
    {51, 153, 255,255},
    {153, 204, 255,255},
    {102, 255, 102,255}
};
