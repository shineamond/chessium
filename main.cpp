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
    board.SetupDefaultBoard();
    board.DrawDefaultChessBoardAndPieces();

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
