#include "SpellChessBoard.h"



SpellChessBoard::SpellChessBoard()
{
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            pieces_positions_[row][col] = nullptr;
        }
    }
}



void SpellChessBoard::DrawDefaultColorSquare(const int row, const int col) const
{
    SDL_Rect drawing_position{col * _SQUARE_SIZE, 60 + row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};

    if ((row + col) % 2 == 0)
    {
        SDL_SetRenderDrawColor(RENDERER, 214, 226, 233, 255); // NOT PURE WHITE
    }
    else
    {
        SDL_SetRenderDrawColor(RENDERER, 100, 80, 170, 255); // PURPLE
    }

    SDL_RenderFillRect(RENDERER, &drawing_position);
}
