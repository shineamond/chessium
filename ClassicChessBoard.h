#pragma once

#include "CoreFunctions.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "MoveInformation.h"
#include "ChessBoard.h"



class ClassicChessBoard : public ChessBoard
{
    private:
        //ChessPiece* pieces_positions_[_BOARD_SIZE][_BOARD_SIZE];
        vector <pair <int, int>> clicked_squares_list_;
        bool legal_moves_set_;
        bool has_legal_moves_;
        vector <MoveInformation> moves_log_;
        int no_capture_or_pawns_moves_;
        MoveInformation original_position_;
        vector <int> positions_repetition_times_;
        bool en_passant_available_;
        int black_pieces_count_[_TOTAL];
        int white_pieces_count_[_TOTAL];

    public:
        ClassicChessBoard();
//        ~ClassicChessBoard();
        void DrawDefaultColorSquare(const int row, const int col) const override;
//        void DrawClickedSquare(const int row, const int col) const;
//        void DrawPiece(const int row, const int col) const;
        void DrawRelevantSquares(const int row, const int col, const _MOVE_TYPES move_type) const;
        void SetupDefaultBoard();
//        void DrawChessBoardAndPieces() const override;
        _MESSAGES_FROM_CHESSBOARD HandleGame(const _CHESS_PIECE_COLORS side_to_move);
        void PutPiece(const int row, const int col, const _CHESS_PIECE_TYPES type, const _CHESS_PIECE_COLORS color);
        void DestroyPiece(const int row, const int col);
        bool PromotePawn(const int col, const _CHESS_PIECE_COLORS color);
        pair<int, int> GetWhiteKingPosition() const;
        pair<int, int> GetBlackKingPosition() const;
        bool IsKingInCheck(const _CHESS_PIECE_COLORS king_color);
        bool IsLegalMove(const int old_row, const int old_col, const int new_row, const int new_col, const _MOVE_TYPES move_type, const _CHESS_PIECE_COLORS side_to_move);
        void AddLegalCastling(const _CHESS_PIECE_COLORS side_to_move);
        bool AddEnPassantMoves(const _CHESS_PIECE_COLORS side_to_move);
        bool IsDraw50Moves();
        bool IsDrawThreefoldRepetition();
        void CountPieces();
        bool IsDrawInsufficientMaterials();
        pair<int, int> FindBishopPosition(const _CHESS_PIECE_COLORS bishop_color);
        bool IsOnlyKingLeft(const _CHESS_PIECE_COLORS side) const;
        void ResetBoard();
        void DrawSquareAndPieceIfKingInCheck(const _CHESS_PIECE_COLORS king_color);
};
