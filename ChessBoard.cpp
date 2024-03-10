#include "ChessBoard.h"
#include "ChessPiece.h"



ChessBoard::ChessBoard()
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        for (int j = 0; j < _BOARD_SIZE; j++)
        {
            pieces_positions_[i][j] = nullptr;
        }
    }
}



ChessBoard::~ChessBoard()
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        for (int j = 0; j < _BOARD_SIZE; j++)
        {
            delete pieces_positions_[i][j];
            pieces_positions_[i][j] = nullptr;
        }
    }
}



void ChessBoard::DrawChessBoard() const
{
    SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255); // WHITE
    SDL_RenderClear(RENDERER);

    SDL_Rect board_square {0, 0, _SQUARE_SIZE, _SQUARE_SIZE};
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        board_square.y = row * _SQUARE_SIZE;
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            board_square.x = col * _SQUARE_SIZE;

            if ((row + col) % 2 == 0)
            {
                SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255); // WHITE
            }
            else
            {
                SDL_SetRenderDrawColor(RENDERER, 130, 180, 170, 250); // LIGHT GREEN
            }

            SDL_RenderFillRect(RENDERER, &board_square);
        }
    }
}



void ChessBoard::SetupBeginningBoard()
{
    pieces_positions_[0][0] = new Rook(_BLACK);
    pieces_positions_[0][1] = new Knight(_BLACK);
    pieces_positions_[0][2] = new Bishop(_BLACK);
    pieces_positions_[0][3] = new Queen(_BLACK);
    pieces_positions_[0][4] = new King(_BLACK);
    pieces_positions_[0][5] = new Bishop(_BLACK);
    pieces_positions_[0][6] = new Knight(_BLACK);
    pieces_positions_[0][7] = new Rook(_BLACK);

    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        pieces_positions_[1][i] = new Pawn(_BLACK);
    }

    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        pieces_positions_[6][i] = new Pawn(_WHITE);
    }

    pieces_positions_[7][0] = new Rook(_WHITE);
    pieces_positions_[7][1] = new Knight(_WHITE);
    pieces_positions_[7][2] = new Bishop(_WHITE);
    pieces_positions_[7][3] = new Queen(_WHITE);
    pieces_positions_[7][4] = new King(_WHITE);
    pieces_positions_[7][5] = new Bishop(_WHITE);
    pieces_positions_[7][6] = new Knight(_WHITE);
    pieces_positions_[7][7] = new Rook(_WHITE);
}



void ChessBoard::DrawPieces() const
{
    SDL_Rect drawing_position {0, 0, _SQUARE_SIZE, _SQUARE_SIZE};

    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        drawing_position.y = i * _SQUARE_SIZE;

        for (int j = 0; j < _BOARD_SIZE; j++)
        {
            if (pieces_positions_[i][j] != nullptr)
            {
                drawing_position.x = j * _SQUARE_SIZE;
                SDL_RenderCopy(RENDERER, pieces_positions_[i][j] -> GetImage(), nullptr, &drawing_position);
            }
        }
    }
}
