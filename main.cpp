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

SDL_Window* WINDOW = nullptr;
SDL_Renderer* RENDERER = nullptr;
SDL_Event EVENT;
TTF_Font* FONT;



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
//    board.PutPiece(7, 4, _KING, _WHITE);
//    board.PutPiece(0, 4, _KING, _BLACK);
//    board.PutPiece(1, 0, _BISHOP, _WHITE);
    //board.PutPiece(6, 0, _BISHOP, _BLACK);
    board.CountPieces();
    board.DrawChessBoardAndPieces();

    SDL_Rect player_pfp_position {0, 5, 50, 50};
    SDL_RenderCopy(RENDERER, LoadTexture("media/anonymous.png"), nullptr, &player_pfp_position);
    WrappedTexture player1_name;
    player1_name.SetupTextureFromText("Black", SDL_Color{0, 0, 0});
    player1_name.Render(60, 13);

    player_pfp_position.y = 705;
    SDL_RenderCopy(RENDERER, LoadTexture("media/anonymous.png"), nullptr, &player_pfp_position);
    WrappedTexture player2_name;
    player2_name.SetupTextureFromText("White", SDL_Color{0, 0, 0});
    player2_name.Render(60, 714);


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
