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
    board.SetupDefaultBoard();
    board.SetSideToMoveFirst(_BLACK);
    board.DestroyPiece(6, 3);
    board.PutPiece(3, 3, _PAWN, _WHITE);
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
