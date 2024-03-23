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
TTF_Font* FONT;

mutex MUTEX;



int main(int argc, char* args[])
{
    if (!Initialize())
    {
        Quit();
        exit(1);
    }

    ClassicChessGame game;
    game.Setup();
    game.DrawPlayers();
    game.Start();


    Quit();

    return 0;
}
