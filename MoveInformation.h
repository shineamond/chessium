#pragma once

#include "CoreFunctions.h"
#include "ChessPiece.h"



class MoveInformation
{
    private:
        _CHESS_PIECE_TYPES moved_piece_;
        pair <int, int> old_position_;
        pair <int, int> new_position_;
        _MOVE_TYPES move_type_;
        pair <_CHESS_PIECE_TYPES, _CHESS_PIECE_COLORS> positions_record_[_BOARD_SIZE][_BOARD_SIZE];
        bool en_passant_available_;

    public:
        MoveInformation();
        MoveInformation(const _CHESS_PIECE_TYPES moved_piece, const pair <int, int> old_position, const pair <int, int> new_position, const _MOVE_TYPES move_type);
        MoveInformation(const _MOVE_TYPES move_type);
        _CHESS_PIECE_TYPES GetMovedPiece() const;
        _MOVE_TYPES GetMoveType() const;
        pair <int, int> GetOldPosition() const;
        pair <int, int> GetNewPosition() const;
        void AddPositionsRecord(ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE]);
        bool operator == (const MoveInformation & another_log);
        void SetEnPassantAvailable(const bool en_passant_available);
};
