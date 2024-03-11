#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
using namespace std;

const string _WINDOW_TITLE = "CHESSIUM";
const int _SQUARE_SIZE = 80;
const int _BOARD_SIZE = 8;
const int _SCREEN_WIDTH = _SQUARE_SIZE * _BOARD_SIZE;
const int _SCREEN_HEIGHT = _SQUARE_SIZE * _BOARD_SIZE;

enum _CHESS_PIECE_TYPES
{
    _EMPTY = 0,
    _PAWN = 1,
    _KNIGHT = 2,
    _BISHOP = 3,
    _ROOK = 4,
    _QUEEN = 5,
    _KING = 6
};

enum _CHESS_PIECE_COLORS
{
    _BLACK = -1,
    _NONE = 0,
    _WHITE = 1
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

bool Initialize();
SDL_Texture* LoadTexture(const string image_path);
void Quit();
