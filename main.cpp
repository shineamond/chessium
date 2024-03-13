#include "CoreFunctions.h"
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

SDL_Window* WINDOW = nullptr;
SDL_Renderer* RENDERER = nullptr;



int main(int argc, char* args[])
{
    if (!Initialize())
    {
        Quit();
        exit(1);
    }

    bool quit = false;
    SDL_Event ev;

    ChessBoard board;
    board.PutPiece(3, 3, _KNIGHT, _WHITE);
    board.PutPiece(2, 5, _PAWN, _BLACK);
    board.PutPiece(0, 4, _ROOK, _WHITE);
    board.PutPiece(3, 4, _QUEEN, _WHITE);
    board.PutPiece(2, 4, _BISHOP, _BLACK);
    board.PutPiece(1, 5, _BISHOP, _WHITE);
    board.PutPiece(1, 4, _KING, _BLACK);
    board.PutPiece(6, 6, _PAWN, _WHITE);
    board.DrawChessBoardAndPieces();

    while (!quit)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            board.HandleClick(ev);

            SDL_RenderPresent(RENDERER);

            if (ev.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    Quit();

    return 0;
}
