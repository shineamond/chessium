#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

const string _WINDOW_TITLE = "CHESSIUM";
const int _SQUARE_SIZE = 80;
const int _BOARD_SIZE = 8;
const int _SCREEN_WIDTH = _SQUARE_SIZE * _BOARD_SIZE;
const int _SCREEN_HEIGHT = _SQUARE_SIZE * _BOARD_SIZE;

extern SDL_Window* WINDOW;
extern SDL_Renderer* RENDERER;

bool Initialize();
void Quit();
