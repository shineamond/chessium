#include "ChessPiece.h"
#include "CoreFunctions.h"
//
//
//
//ChessPiece::ChessPiece()
//{
//    image_ = nullptr;
//}
//
//
//
ChessPiece::~ChessPiece()
{
    type_ = _EMPTY;
    color_ = _NONE;
    SDL_DestroyTexture(image_);
    image_ = nullptr;
}



SDL_Texture* ChessPiece::GetImage() const
{
    return image_;
}



_CHESS_PIECE_TYPES ChessPiece::GetPieceType() const
{
    return type_;
}



_CHESS_PIECE_COLORS ChessPiece::GetPieceColor() const
{
    return color_;
}
