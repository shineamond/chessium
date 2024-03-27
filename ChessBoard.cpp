#include "ChessBoard.h"



ChessBoard::~ChessBoard()
{
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            delete pieces_positions_[row][col];
            pieces_positions_[row][col] = nullptr;
        }
    }
}



void ChessBoard::DrawClickedSquare(const int row, const int col) const
{
    SDL_Rect drawing_position{col * _SQUARE_SIZE, 60 + row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};
    SDL_SetRenderDrawColor(RENDERER, 230, 230, 50, 200);
    SDL_RenderFillRect(RENDERER, &drawing_position);
}



void ChessBoard::DrawPiece(const int row, const int col) const
{
    if (pieces_positions_[row][col] != nullptr)
    {
        SDL_Rect drawing_position {col * _SQUARE_SIZE, 60 + row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};
        SDL_RenderCopy(RENDERER, pieces_positions_[row][col] -> GetImage(), nullptr, &drawing_position);
    }
}



void ChessBoard::DrawChessBoardAndPieces() const
{
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            DrawDefaultColorSquare(row, col);
            DrawPiece(row, col);
        }
    }
}



void ChessBoard::PutPiece(const int row, const int col, const _CHESS_PIECE_TYPES type, const _CHESS_PIECE_COLORS color)
{
    switch (type)
    {
        case _PAWN:
            pieces_positions_[row][col] = new Pawn(color);
            break;
        case _KNIGHT:
            pieces_positions_[row][col] = new Knight(color);
            break;
        case _BISHOP:
            pieces_positions_[row][col] = new Bishop(color);
            break;
        case _ROOK:
            pieces_positions_[row][col] = new Rook(color);
            break;
        case _QUEEN:
            pieces_positions_[row][col] = new Queen(color);
            break;
        case _KING:
            pieces_positions_[row][col] = new King(color);
            break;
        default:
            break;
    }
}



void ChessBoard::DestroyPiece(const int row, const int col)
{
    if (pieces_positions_[row][col] != nullptr)
    {
        delete pieces_positions_[row][col];
        pieces_positions_[row][col] = nullptr;
    }
}



void ChessBoard::DrawRelevantSquares(const int row, const int col, const _MOVE_TYPES move_type) const
{
    SDL_Rect drawing_position {col * _SQUARE_SIZE, 60 + row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};

    if (move_type == _MOVE || move_type == _CASTLE)
    {
        SDL_RenderCopy(RENDERER, LoadTexture("media/movable_square.png"), nullptr, &drawing_position);
    }
    else if (move_type == _CAPTURE || move_type == _EN_PASSANT)
    {
        DrawDefaultColorSquare(row, col);
        SDL_RenderCopy(RENDERER, LoadTexture("media/takeable_square.png"), nullptr, &drawing_position);
        DrawPiece(row, col);
    }
}
