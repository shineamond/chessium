#include "WrappedTexture.h"



WrappedTexture::WrappedTexture()
{
    width_ = 0;
    height_ = 0;
    texture_ = nullptr;
}



WrappedTexture::~WrappedTexture()
{
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    width_ = 0;
    height_ = 0;
}



void WrappedTexture::SetupTextureFromText(const int font_size, const bool is_bold, const string text, const SDL_Color text_color)
{
    texture_ = nullptr;
    SDL_Surface* text_surface = nullptr;

    if (!is_bold)
    {
        if (font_size == 18)
        {
            text_surface = TTF_RenderText_Solid(REGULAR_FONT_18, text.c_str(), text_color);
        }
        else if (font_size == 24)
        {
            text_surface = TTF_RenderText_Solid(REGULAR_FONT_24, text.c_str(), text_color);
        }
    }
    else
    {
        if (font_size == 12)
        {
            text_surface = TTF_RenderText_Solid(SEMIBOLD_FONT_12, text.c_str(), text_color);
        }
        else if (font_size == 18)
        {
            text_surface = TTF_RenderText_Solid(SEMIBOLD_FONT_18, text.c_str(), text_color);
        }
        else if (font_size == 24)
        {
            text_surface = TTF_RenderText_Solid(SEMIBOLD_FONT_24, text.c_str(), text_color);
        }
        else if (font_size == 36)
        {
            text_surface = TTF_RenderText_Solid(SEMIBOLD_FONT_36, text.c_str(), text_color);
        }
//        else if (font_size == 48)
//        {
//            text_surface = TTF_RenderText_Solid(SEMIBOLD_FONT_48, text.c_str(), text_color);
//        }
    }

    if (text_surface == nullptr)
    {
        cout << "Couldn't create text surface. TTF_Error: " << TTF_GetError() << endl;
    }
    else
    {
        texture_ = SDL_CreateTextureFromSurface(RENDERER, text_surface);
        if (texture_ == nullptr)
        {
            cout << "Couldn't create text texture from text surface. SDL_Error: " << SDL_GetError() << endl;
        }
        else
        {
            width_ = text_surface -> w;
            height_ = text_surface -> h;

            //cout << width_ << endl << height_ << endl;
        }
    }

    SDL_FreeSurface(text_surface);
    text_surface = nullptr;
}



SDL_Texture* WrappedTexture::GetTexture() const
{
    return texture_;
}



int WrappedTexture::GetWidth() const
{
    return width_;
}



int WrappedTexture::GetHeight() const
{
    return height_;
}



void WrappedTexture::Render(const int render_position_x, const int render_position_y)
{
    SDL_Rect render_position{render_position_x, render_position_y, width_, height_};
    SDL_RenderCopy(RENDERER, texture_, nullptr, &render_position);
}
