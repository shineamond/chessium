#include "MoveInformation.h"




MoveInformation::MoveInformation()
{
    moved_piece_ = _EMPTY;
    old_position_ = make_pair(-1, -1);
    new_position_ = make_pair(-1, -1);
    move_type_ = _NONE;
}



MoveInformation::MoveInformation(const _CHESS_PIECE_TYPES moved_piece, const pair <int, int> old_position, const pair <int, int> new_position, const _MOVE_TYPES move_type)
{
    moved_piece_ = moved_piece;
    old_position_ = old_position;
    new_position_ = new_position;
    move_type_ = move_type;
}



MoveInformation::MoveInformation(const _MOVE_TYPES move_type)
{
    move_type_ = move_type;
}



_CHESS_PIECE_TYPES MoveInformation::GetMovedPiece() const
{
    return moved_piece_;
}



_MOVE_TYPES MoveInformation::GetMoveType() const
{
    return move_type_;
}



pair <int, int> MoveInformation::GetOldPosition() const
{
    return old_position_;
}



pair <int, int> MoveInformation::GetNewPosition() const
{
    return new_position_;
}
