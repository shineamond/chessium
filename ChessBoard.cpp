#include "ChessBoard.h"
#include "ChessPiece.h"



ChessBoard::ChessBoard()
{
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            pieces_positions_[row][col] = nullptr;
            //square_status_[row][col] = _NOT_CLICKED;
        }
    }
}



ChessBoard::~ChessBoard()
{
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            delete pieces_positions_[row][col];
            pieces_positions_[row][col] = nullptr;
            //square_status_[row][col] = _NOT_CLICKED;
        }
    }
}



void ChessBoard::DrawDefaultColorSquare(const int row, const int col) const
{
    SDL_Rect drawing_position{col * _SQUARE_SIZE, row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};

    if ((row + col) % 2 == 0)
    {
        SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255); // WHITE
    }
    else
    {
        SDL_SetRenderDrawColor(RENDERER, 130, 180, 170, 250); // LIGHT GREEN
    }

    SDL_RenderFillRect(RENDERER, &drawing_position);
}



void ChessBoard::DrawClickedSquare(const int row, const int col) const
{
    SDL_Rect drawing_position{col * _SQUARE_SIZE, row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};
    SDL_SetRenderDrawColor(RENDERER, 230, 230, 50, 200);
    SDL_RenderFillRect(RENDERER, &drawing_position);
}



void ChessBoard::DrawPiece(const int row, const int col) const
{
    if (pieces_positions_[row][col] != nullptr)
    {
        SDL_Rect drawing_position {col * _SQUARE_SIZE, row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};
        SDL_RenderCopy(RENDERER, pieces_positions_[row][col] -> GetImage(), nullptr, &drawing_position);
    }
}



void ChessBoard::DrawMovableAndTakeableSquare(const int row, const int col, const string type) const
{
    SDL_Rect drawing_position {col * _SQUARE_SIZE, row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};

    if (type == "_MOVABLE")
    {
        SDL_RenderCopy(RENDERER, LoadTexture("media/movable_square.png"), nullptr, &drawing_position);
    }
    else if (type == "_TAKEABLE")
    {
        DrawDefaultColorSquare(row, col);
        SDL_RenderCopy(RENDERER, LoadTexture("media/takeable_square.png"), nullptr, &drawing_position);
        DrawPiece(row, col);
    }
}



void ChessBoard::SetupDefaultBoard()
{
    pieces_positions_[0][0] = new Rook(_BLACK);
    pieces_positions_[0][1] = new Knight(_BLACK);
    pieces_positions_[0][2] = new Bishop(_BLACK);
    pieces_positions_[0][3] = new Queen(_BLACK);
    pieces_positions_[0][4] = new King(_BLACK);
    pieces_positions_[0][5] = new Bishop(_BLACK);
    pieces_positions_[0][6] = new Knight(_BLACK);
    pieces_positions_[0][7] = new Rook(_BLACK);

    for (int col = 0; col < _BOARD_SIZE; col++)
    {
        pieces_positions_[1][col] = new Pawn(_BLACK);
    }

    for (int col = 0; col < _BOARD_SIZE; col++)
    {
        pieces_positions_[6][col] = new Pawn(_WHITE);
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



void ChessBoard::DrawChessBoardAndPieces() const
{
    SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255); // WHITE
    SDL_RenderClear(RENDERER);

    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            DrawDefaultColorSquare(row, col);
            DrawPiece(row, col);
        }
    }
}



void ChessBoard::HandleClick(SDL_Event & ev)
{
    if (ev.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouse_position_x, mouse_position_y;
        SDL_GetMouseState(&mouse_position_x, &mouse_position_y);

        int clicked_square_row = mouse_position_y / _SQUARE_SIZE;
        int clicked_square_col = mouse_position_x / _SQUARE_SIZE;

        if (((clicked_square_row * _SQUARE_SIZE) != mouse_position_y) && ((clicked_square_col * _SQUARE_SIZE) != mouse_position_x))
        {
            if (pieces_positions_[clicked_square_row][clicked_square_col] != nullptr)
            {
                if (clicked_squares_list_.empty()) // Click a square
                {
                    DrawClickedSquare(clicked_square_row, clicked_square_col);
                    DrawPiece(clicked_square_row, clicked_square_col);

                    pieces_positions_[clicked_square_row][clicked_square_col] -> SetPossibleMoves(clicked_square_row, clicked_square_col, pieces_positions_);
                    vector <pair<pair <int, int>, string>> temp = pieces_positions_[clicked_square_row][clicked_square_col] -> GetPossibleMoves();

                    for (int i = 0; i < (int) temp.size(); i++)
                    {
                        DrawMovableAndTakeableSquare(temp[i].first.first, temp[i].first.second, temp[i].second);
                    }

                    clicked_squares_list_.push_back(pair <int, int> {clicked_square_row, clicked_square_col});
                }
                else
                {
                    if (clicked_squares_list_[0].first == clicked_square_row && clicked_squares_list_[0].second == clicked_square_col) // Unclick clicked square
                    {
                        DrawDefaultColorSquare(clicked_square_row, clicked_square_col);
                        DrawPiece(clicked_square_row, clicked_square_col);

                        vector <pair<pair <int, int>, string>> temp = pieces_positions_[clicked_square_row][clicked_square_col] -> GetPossibleMoves();
                        for (int i = 0; i < (int) temp.size(); i++)
                        {
                            DrawDefaultColorSquare(temp[i].first.first, temp[i].first.second);
                            DrawPiece(temp[i].first.first, temp[i].first.second);
                        }

                        pieces_positions_[clicked_square_row][clicked_square_col] -> UnsetPossibleMoves();

                        clicked_squares_list_.clear();
                    }
                    else // Capture or Unclick previously clicked square and click another square
                    {
                        bool is_capture = false;
                        vector <pair<pair <int, int>, string>> temp = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> GetPossibleMoves();
                        for (int i = 0; i < (int) temp.size(); i++)
                        {
                            if (clicked_square_row == temp[i].first.first && clicked_square_col == temp[i].first.second) // Capture
                            {
                                for (int j = 0; j < (int) temp.size(); j++)
                                {
                                    DrawDefaultColorSquare(temp[j].first.first, temp[j].first.second);
                                    DrawPiece(temp[j].first.first, temp[j].first.second);
                                }
                                pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> UnsetPossibleMoves();
                                DestroyPiece(clicked_square_row, clicked_square_col);
                                DrawDefaultColorSquare(clicked_square_row, clicked_square_col);

                                pieces_positions_[clicked_square_row][clicked_square_col] = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second];
                                pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] = nullptr;
                                DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);
                                clicked_squares_list_.clear();
                                DrawPiece(clicked_square_row, clicked_square_col);
                                is_capture = true;

                                break;
                            }
                        }

                        if (!is_capture)
                        {
                            // Unclick previously clicked square
                            DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);
                            DrawPiece(clicked_squares_list_[0].first, clicked_squares_list_[0].second);

                            vector <pair<pair <int, int>, string>> temp = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> GetPossibleMoves();
                            for (int i = 0; i < (int) temp.size(); i++)
                            {
                                DrawDefaultColorSquare(temp[i].first.first, temp[i].first.second);
                                DrawPiece(temp[i].first.first, temp[i].first.second);
                            }

                            pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> UnsetPossibleMoves();

                            clicked_squares_list_.clear();

                            temp.clear();

                            // Click another square
                            DrawClickedSquare(clicked_square_row, clicked_square_col);
                            DrawPiece(clicked_square_row, clicked_square_col);

                            pieces_positions_[clicked_square_row][clicked_square_col] -> SetPossibleMoves(clicked_square_row, clicked_square_col, pieces_positions_);
                            temp = pieces_positions_[clicked_square_row][clicked_square_col] -> GetPossibleMoves();

                            for (int i = 0; i < (int) temp.size(); i++)
                            {
                                DrawMovableAndTakeableSquare(temp[i].first.first, temp[i].first.second, temp[i].second);
                            }

                            clicked_squares_list_.push_back(pair <int, int> {clicked_square_row, clicked_square_col});
                        }
                    }
                }
            }
            else
            {
                if (!clicked_squares_list_.empty())
                {
                    vector <pair<pair <int, int>, string>> temp = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> GetPossibleMoves();
                    for (int i = 0; i < (int) temp.size(); i++)
                    {
                        if (temp[i].first.first == clicked_square_row && temp[i].first.second == clicked_square_col) // Move
                        {
                            for (int j = 0; j < (int) temp.size(); j++)
                            {
                                DrawDefaultColorSquare(temp[j].first.first, temp[j].first.second);
                                DrawPiece(temp[j].first.first, temp[j].first.second);
                            }
                            pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> UnsetPossibleMoves();
                            pieces_positions_[clicked_square_row][clicked_square_col] = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second];
                            pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] = nullptr;
                            DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);
                            clicked_squares_list_.clear();
                            DrawPiece(clicked_square_row, clicked_square_col);

                            break;
                        }
                    }
                }
            }
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
