#include "CoreFunctions.h"



bool Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL couldn't initialize. SDL_Error: " << SDL_GetError() << endl;

        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cout << "SDL_image couldn't initialize. IMG_Error: " << IMG_GetError() << endl;

        return false;
    }

    if (TTF_Init() == -1)
    {
        cout << "SDL_ttf couldn't initialize. TTF_Error: " << TTF_GetError() << endl;

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

    FONT = TTF_OpenFont(_FONT_PATH.c_str(), 24);
    if (FONT == nullptr)
    {
        cout << "Couldn't load " << _FONT_PATH << " font. TTF_Error: " << TTF_GetError() << endl;

        return false;
    }

    return true;
}



SDL_Texture* LoadTexture(const string image_path)
{
    SDL_Surface* image_surface = IMG_Load(image_path.c_str());
    if (image_surface == nullptr)
    {
        cout << "Couldn't load image " << image_path << ". IMG_Error: " << IMG_GetError() << endl;
    }

    SDL_Texture* image_texture = nullptr;
    if (image_surface != nullptr)
    {
        image_texture = SDL_CreateTextureFromSurface(RENDERER, image_surface);

        if (image_texture == nullptr)
        {
            cout << "Couldn't create texture for image " << image_path << ". IMG_Error: " << IMG_GetError() << endl;
        }
    }

    SDL_FreeSurface(image_surface);
    image_surface = nullptr;

    return image_texture;
}




void Quit()
{
    TTF_CloseFont(FONT);
    FONT = nullptr;
    SDL_DestroyRenderer(RENDERER);
    RENDERER = nullptr;
    SDL_DestroyWindow(WINDOW);
    WINDOW = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
