#include "MoveInformation.h"




MoveInformation::MoveInformation()
{
    moved_piece_ = _EMPTY;
    old_position_ = make_pair(-1, -1);
    new_position_ = make_pair(-1, -1);
    move_type_ = _NONE;

    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            positions_record_[row][col] = make_pair(_EMPTY, _COLORLESS);
        }
    }

    en_passant_available_ = false;
}



MoveInformation::MoveInformation(const _CHESS_PIECE_TYPES moved_piece, const pair <int, int> old_position, const pair <int, int> new_position, const _MOVE_TYPES move_type)
{
    moved_piece_ = moved_piece;
    old_position_ = old_position;
    new_position_ = new_position;
    move_type_ = move_type;

    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            positions_record_[row][col] = make_pair(_EMPTY, _COLORLESS);
        }
    }
}



MoveInformation::MoveInformation(const _MOVE_TYPES move_type) // Castling log
{
    moved_piece_ = _EMPTY;
    old_position_ = make_pair(-1, -1);
    new_position_ = make_pair(-1, -1);
    move_type_ = move_type;

    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            positions_record_[row][col] = make_pair(_EMPTY, _COLORLESS);
        }
    }
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



void MoveInformation::AddPositionsRecord(ChessPiece* pieces_positions[_BOARD_SIZE][_BOARD_SIZE])
{
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            if (pieces_positions[row][col] == nullptr)
            {
                positions_record_[row][col] = make_pair(_EMPTY, _COLORLESS);
            }
            else
            {
                positions_record_[row][col] = make_pair(pieces_positions[row][col] -> GetPieceType(), pieces_positions[row][col] -> GetPieceColor());
            }
        }
    }
}



bool MoveInformation::operator ==(const MoveInformation & another_log)
{
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            if ((positions_record_[row][col].first != another_log.positions_record_[row][col].first) || (positions_record_[row][col].second != another_log.positions_record_[row][col].second))
            {
                return false;
            }
        }
    }

    if (en_passant_available_ != another_log.en_passant_available_)
    {
        //cout << "here\n";
        return false;
    }

    return true;
}



void MoveInformation::SetEnPassantAvailable(const bool en_passant_available)
{
    en_passant_available_ = en_passant_available;
}
