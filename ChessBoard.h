#pragma once

#include "CoreFunctions.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"



class ChessBoard
{
    private:
        ChessPiece* pieces_positions_[_BOARD_SIZE][_BOARD_SIZE];
        //_BOARD_SQUARE_STATUS square_status_[_BOARD_SIZE][_BOARD_SIZE];
        vector <pair <int, int>> clicked_squares_list_;
        //_BOARD_SQUARE_COLORS square_colors_[_BOARD_SIZE][_BOARD_SIZE];

    public:
        ChessBoard();
        ~ChessBoard();
        void DrawDefaultColorSquare(const int row, const int col) const;
        void DrawClickedSquare(const int row, const int col) const;
        void DrawPiece(const int row, const int col) const;
        void SetupDefaultBoard();
        void DrawDefaultChessBoardAndPieces() const;
        void HandleClick(SDL_Event & ev);
};
