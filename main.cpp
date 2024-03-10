#include "CoreFunctions.h"

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

    while (!quit)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_QUIT)
            {
                quit = true;
            }

            SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255);
            SDL_RenderClear(RENDERER);

            SDL_RenderPresent(RENDERER);
        }
    }

    Quit();

    return 0;
}
