#include "CoreFunctions.h"
#include "ChessBoard.h"

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

    while (!quit)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        board.DrawChessBoard();

        SDL_RenderPresent(RENDERER);
    }

    Quit();

    return 0;
}
