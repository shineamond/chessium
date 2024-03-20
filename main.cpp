#include "CoreFunctions.h"
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "MoveInformation.h"

SDL_Window* WINDOW = nullptr;
SDL_Renderer* RENDERER = nullptr;
SDL_Event EVENT;



int main(int argc, char* args[])
{
    if (!Initialize())
    {
        Quit();
        exit(1);
    }

    bool quit = false;
    bool game_end = false;

    ChessBoard board;
    //board.SetupDefaultBoard();
    board.PutPiece(7, 4, _KING, _WHITE);
    board.PutPiece(0, 4, _KING, _BLACK);
    board.PutPiece(1, 0, _BISHOP, _WHITE);
    //board.PutPiece(6, 0, _BISHOP, _BLACK);
    board.CountPieces();
    board.DrawChessBoardAndPieces();

    while (!quit)
    {
        while (SDL_PollEvent(&EVENT) != 0)
        {
            if (!game_end)
            {
                board.HandleGame(game_end);

                SDL_RenderPresent(RENDERER);
            }

            if (EVENT.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    Quit();

    return 0;
}
