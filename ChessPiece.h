#pragma once

#include "CoreFunctions.h"



class ChessPiece
{
    protected:
        SDL_Texture* image_;
        _CHESS_PIECE_TYPES type_;
        _CHESS_PIECE_COLORS color_;
        vector <pair<pair <int, int>, string>> possible_moves_;

    public:
//        virtual ChessPiece() = 0;
        ~ChessPiece();
        SDL_Texture* GetImage() const;
        _CHESS_PIECE_TYPES GetPieceType() const;
        _CHESS_PIECE_COLORS GetPieceColor() const;
        virtual void SetPossibleMoves(const int row, const int col, ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE]) = 0;
        void UnsetPossibleMoves();
        vector <pair<pair <int, int>, string>> GetPossibleMoves() const;
};
