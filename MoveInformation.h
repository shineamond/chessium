#pragma once

#include "CoreFunctions.h"



class MoveInformation
{
    private:
        _CHESS_PIECE_TYPES moved_piece_;
        pair <int, int> old_position_;
        pair <int, int> new_position_;
        _MOVE_TYPES move_type_;

    public:
        MoveInformation();
        MoveInformation(const _CHESS_PIECE_TYPES moved_piece, const pair <int, int> old_position, const pair <int, int> new_position, const _MOVE_TYPES move_type);
        MoveInformation(const _MOVE_TYPES move_type);
        _CHESS_PIECE_TYPES GetMovedPiece() const;
        pair <int, int> GetOldPosition() const;
        pair <int, int> GetNewPosition() const;
};
