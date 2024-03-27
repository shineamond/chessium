#include "CoreFunctions.h"
#include "ClassicChessBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "MoveInformation.h"
#include "WrappedTexture.h"
#include "ChessClock.h"
#include "ClassicChessGame.h"
#include "SpellChessBoard.h"
#include "ChessBoard.h"

SDL_Window* WINDOW = nullptr;
SDL_Renderer* RENDERER = nullptr;
SDL_Event EVENT;
TTF_Font* REGULAR_FONT_18;
TTF_Font* REGULAR_FONT_24;
TTF_Font* SEMIBOLD_FONT_12;
TTF_Font* SEMIBOLD_FONT_18;
TTF_Font* SEMIBOLD_FONT_24;
TTF_Font* SEMIBOLD_FONT_36;
//TTF_Font* SEMIBOLD_FONT_48;

mutex MUTEX;

bool in_gameloop = true;



int main(int argc, char* args[])
{
    if (!Initialize())
    {
        Quit();
        exit(1);
    }

    ClassicChessGame game;
    while (in_gameloop)
    {
        SDL_SetRenderDrawColor(RENDERER, 40, 40, 40, 0); // BLACK
        SDL_RenderClear(RENDERER);

        game.DrawPlayers();
        if (game.Setup())
        {
            game.Start();
        }
        else
        {
            in_gameloop = false;
        }
    }

//    bool quit = false;
//    SDL_SetRenderDrawColor(RENDERER, 40, 40, 40, 0); // BLACK
//    SDL_RenderClear(RENDERER);
//    SpellChessBoard spell_board;
//    spell_board.PutPiece(5, 3, _QUEEN, _WHITE);
//    spell_board.PutPiece(4, 4, _ROOK, _BLACK);
//    spell_board.PutPiece(0, 5, _BISHOP, _WHITE);
//    spell_board.PutPiece(7, 7, _KING, _BLACK);
//    spell_board.PutPiece(4, 2, _KNIGHT, _WHITE);
//    spell_board.PutPiece(1, 4, _PAWN, _BLACK);
//    spell_board.DrawChessBoardAndPieces();
//
//    while(!quit)
//    {
//        while(SDL_PollEvent(&EVENT))
//        {
//            _MESSAGES_FROM_CHESSBOARD message = spell_board.HandleGame();
//            if (message == _QUIT)
//            {
//                quit = true;
//            }
//        }
//
//        SDL_RenderPresent(RENDERER);
//    }

    //WaitUntilKeyPressed();

    Quit();

    return 0;
}
