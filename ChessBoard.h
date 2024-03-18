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
        bool legal_moves_set_;
        bool has_legal_moves_;

    public:
        ChessBoard();
        ~ChessBoard();
        void DrawDefaultColorSquare(const int row, const int col) const;
        void DrawClickedSquare(const int row, const int col) const;
        void DrawPiece(const int row, const int col) const;
        void DrawMovableAndTakeableSquare(const int row, const int col, const string type) const;
        void SetupDefaultBoard();
        void DrawChessBoardAndPieces() const;
        void HandleGame(_CHESS_PIECE_COLORS & side_to_move, bool & game_end);
        void PutPiece(const int row, const int col, const _CHESS_PIECE_TYPES type, const _CHESS_PIECE_COLORS color);
        void DestroyPiece(const int row, const int col);
        void PromotePawn(const int col, const _CHESS_PIECE_COLORS color);
        pair<int, int> GetWhiteKingPosition() const;
        pair<int, int> GetBlackKingPosition() const;
        bool IsKingInCheck(const _CHESS_PIECE_COLORS king_color);
        bool IsLegalMove(const int old_row, const int old_col, const int new_row, const int new_col, const string move_type, const _CHESS_PIECE_COLORS side_to_move);
};
