#include "CoreFunctions.h"



bool Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL couldn't initialize. SDL_Error: " << SDL_GetError() << endl;

        return false;
    }

    WINDOW = SDL_CreateWindow(_WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _SCREEN_WIDTH, _SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (WINDOW == nullptr)
    {
        cout << "Couldn't create window. SDL_Error: " << SDL_GetError() << endl;

        return false;
    }

    RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
    if (RENDERER == nullptr)
    {
        cout << "Couldn't create renderer. SDL_Error: " << SDL_GetError() << endl;

        return false;
    }

    return true;
}



void Quit()
{
    SDL_DestroyRenderer(RENDERER);
    RENDERER = nullptr;
    SDL_DestroyWindow(WINDOW);
    WINDOW = nullptr;

    SDL_Quit();
}
