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

//    SDL_SetRenderDrawColor(RENDERER, 40, 40, 40, 0); // BLACK
//    SDL_RenderClear(RENDERER);
//    SpellChessBoard spell_board;
//    spell_board.DrawChessBoardAndPieces();
//
//    SDL_RenderPresent(RENDERER);
//    WaitUntilKeyPressed();



    Quit();

    return 0;
}
