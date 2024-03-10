#pragma once

#include "CoreFunctions.h"



class ChessPiece
{
    protected:
        SDL_Texture* image_;
        _CHESS_PIECE_TYPES type_;
        _CHESS_PIECE_COLORS color_;

    public:
//        virtual ChessPiece() = 0;
        ~ChessPiece();
        SDL_Texture* GetImage() const;
        _CHESS_PIECE_TYPES GetPieceType() const;
        _CHESS_PIECE_COLORS GetPieceColor() const;
};
