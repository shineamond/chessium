#include "ChessBoard.h"



void ChessBoard::DrawChessBoard() const
{
    SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255); // WHITE
    SDL_RenderClear(RENDERER);

    SDL_Rect board_square {0, 0, _SQUARE_SIZE, _SQUARE_SIZE};
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        board_square.y = row * _SQUARE_SIZE;
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            board_square.x = col * _SQUARE_SIZE;

            if ((row + col) % 2 == 0)
            {
                SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255); // WHITE
            }
            else
            {
                SDL_SetRenderDrawColor(RENDERER, 130, 180, 170, 250); // LIGHT GREEN
            }

            SDL_RenderFillRect(RENDERER, &board_square);
        }
    }
}
