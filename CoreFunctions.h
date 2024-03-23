#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <SDL_ttf.h>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;
using namespace std::chrono;

const string _WINDOW_TITLE = "CHESSIUM";
const int _SQUARE_SIZE = 80;
const int _BOARD_SIZE = 8;
const int _SCREEN_WIDTH = 640;
const int _SCREEN_HEIGHT = 760;
const string _FONT_PATH = "open-sans/OpenSans-Bold.ttf";

enum _CHESS_PIECE_TYPES
{
    _EMPTY = 0,
    _PAWN = 1,
    _KNIGHT = 2,
    _BISHOP = 3,
    _ROOK = 4,
    _QUEEN = 5,
    _KING = 6,
    _TOTAL = 7
};

enum _CHESS_PIECE_COLORS
{
    _BLACK = -1,
    _COLORLESS = 0,
    _WHITE = 1
};

enum _MOVE_TYPES
{
    _NONE,
    _MOVE,
    _CAPTURE,
    _CASTLE,
    _EN_PASSANT
};

//enum _BOARD_SQUARE_COLORS
//{
//    _NONE = 0,
//    _WHITE = 1,
//    _LIGHT_GREEN = 2,
//    _YELLOW = 3;
//};

//enum _BOARD_SQUARE_STATUS
//{
//    _NOT_CLICKED = 0,
//    _CLICKED = 1
//};

extern SDL_Window* WINDOW;
extern SDL_Renderer* RENDERER;
extern SDL_Event EVENT;
extern TTF_Font* FONT;

extern mutex MUTEX;

bool Initialize();
SDL_Texture* LoadTexture(const string image_path);
void Quit();
//SDL_Texture* CreateTextureFromText(const string text, const SDL_Color text_color);
