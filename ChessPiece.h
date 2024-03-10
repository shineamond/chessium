#pragma once

#include "CoreFunctions.h"



class ChessPiece
{
    protected:
        SDL_Texture* image_;
        _CHESS_PIECE_TYPES type_;

    public:
//        virtual ChessPiece() = 0;
//        virtual ~ChessPiece() = 0;
        SDL_Texture* GetImage() const;
        _CHESS_PIECE_TYPES GetPieceType() const;
};
