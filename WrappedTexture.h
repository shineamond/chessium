#pragma once

#include "CoreFunctions.h"



class WrappedTexture
{
    private:
        int width_;
        int height_;
        SDL_Texture* texture_;

    public:
        WrappedTexture();
        ~WrappedTexture();
        void SetupTextureFromText(const string text, const SDL_Color text_color);
        SDL_Texture* GetTexture() const;
        int GetWidth() const;
        int GetHeight() const;
        void Render(const int render_position_x, const int render_position_y);
};
