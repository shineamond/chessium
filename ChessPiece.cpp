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
//ChessPiece::~ChessPiece()
//{
//    SDL_DestroyTexture(image_);
//    image_ = nullptr;
//}



SDL_Texture* ChessPiece::GetImage() const
{
    return image_;
}



_CHESS_PIECE_TYPES ChessPiece::GetPieceType() const
{
    return type_;
}
