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
#include "WrappedTexture.h"
#include "ChessClock.h"
#include "ClassicChessGame.h"

SDL_Window* WINDOW = nullptr;
SDL_Renderer* RENDERER = nullptr;
SDL_Event EVENT;
TTF_Font* REGULAR_FONT_18;
TTF_Font* REGULAR_FONT_24;
TTF_Font* SEMIBOLD_FONT_12;
TTF_Font* SEMIBOLD_FONT_18;
TTF_Font* SEMIBOLD_FONT_24;
TTF_Font* SEMIBOLD_FONT_36;

mutex MUTEX;



int main(int argc, char* args[])
{
    if (!Initialize())
    {
        Quit();
        exit(1);
    }

    SDL_SetRenderDrawColor(RENDERER, 40, 40, 40, 0); // BLACK
    SDL_RenderClear(RENDERER);
    ClassicChessGame game;
    game.DrawPlayers();
    if (game.Setup())
    {
        game.Start();
    }


    Quit();

    return 0;
}
