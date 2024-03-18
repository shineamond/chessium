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
//    board.PutPiece(0, 1, _ROOK, _WHITE);
//    board.PutPiece(0, 7, _KNIGHT, _BLACK);
//    board.PutPiece(2, 7, _KING, _WHITE);
//    board.PutPiece(4, 5, _KNIGHT, _WHITE);
//    board.PutPiece(5, 7, _PAWN, _BLACK);
//    board.PutPiece(6, 7, _PAWN, _BLACK);
//    board.PutPiece(6, 3, _KNIGHT, _BLACK);
//    board.PutPiece(7, 7, _KING, _BLACK);
    board.DrawChessBoardAndPieces();

    _CHESS_PIECE_COLORS side_to_move = _WHITE;
    while (!quit)
    {
        while (SDL_PollEvent(&EVENT) != 0)
        {
            if (!game_end)
            {
                board.HandleGame(side_to_move, game_end);

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
