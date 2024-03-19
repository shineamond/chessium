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
    color_ = _COLORLESS;
    SDL_DestroyTexture(image_);
    image_ = nullptr;
    possible_moves_.clear();
    covering_squares_.clear();
    legal_moves_.clear();
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



void ChessPiece::UnsetPossibleMoves()
{
    possible_moves_.clear();
}


vector <pair<pair <int, int>, _MOVE_TYPES>> ChessPiece::GetPossibleMoves() const
{
    return possible_moves_;
}



void ChessPiece::UnsetCoveringSquares()
{
    covering_squares_.clear();
}



vector <pair <int, int>> ChessPiece::GetCoveringSquares() const
{
    return covering_squares_;
}



void ChessPiece::AddLegalMoves(const int row, const int col, const _MOVE_TYPES move_type)
{
    legal_moves_.push_back(make_pair(make_pair(row, col), move_type));
}



void ChessPiece::UnsetLegalMoves()
{
    legal_moves_.clear();
}



vector <pair<pair <int, int>, _MOVE_TYPES>> ChessPiece::GetLegalMoves() const
{
    return legal_moves_;
}



void ChessPiece::SetMoved()
{
    moved_ = true;
}



bool ChessPiece::GetMoved() const
{
    return moved_;
}
