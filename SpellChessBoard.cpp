#include "SpellChessBoard.h"



SpellChessBoard::SpellChessBoard()
{
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            pieces_positions_[row][col] = nullptr;
        }
    }

    side_to_move_ = _WHITE;
}



void SpellChessBoard::DrawDefaultColorSquare(const int row, const int col) const
{
    SDL_Rect drawing_position{col * _SQUARE_SIZE, 60 + row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};

    if ((row + col) % 2 == 0)
    {
        SDL_SetRenderDrawColor(RENDERER, 214, 226, 233, 255); // NOT PURE WHITE
    }
    else
    {
        SDL_SetRenderDrawColor(RENDERER, 100, 80, 170, 255); // PURPLE
    }

    SDL_RenderFillRect(RENDERER, &drawing_position);
}



_MESSAGES_FROM_CHESSBOARD SpellChessBoard::HandleGame()
{
    _MESSAGES_FROM_CHESSBOARD message = _NO_MESSAGE;
    if (EVENT.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouse_position_x, mouse_position_y;
        SDL_GetMouseState(&mouse_position_x, &mouse_position_y);

        int clicked_square_row = (mouse_position_y - 60) / _SQUARE_SIZE;
        int clicked_square_col = mouse_position_x / _SQUARE_SIZE;

        if ((clicked_square_row * _SQUARE_SIZE + 60 != mouse_position_y) && (clicked_square_col * _SQUARE_SIZE != mouse_position_x) && (clicked_square_row < _BOARD_SIZE) && (clicked_square_col < _BOARD_SIZE))
        {
            if (clicked_squares_list_.empty()) // Click a square
            {
                if (pieces_positions_[clicked_square_row][clicked_square_col] != nullptr)
                {
                    if (pieces_positions_[clicked_square_row][clicked_square_col] -> GetPieceColor() == side_to_move_)
                    {
                        DrawClickedSquare(clicked_square_row, clicked_square_col);
                        DrawPiece(clicked_square_row, clicked_square_col);

                        pieces_positions_[clicked_square_row][clicked_square_col] -> SetPossibleMoves(clicked_square_row, clicked_square_col, pieces_positions_);
                        vector <pair<pair <int, int>, _MOVE_TYPES>> temp = pieces_positions_[clicked_square_row][clicked_square_col] -> GetPossibleMoves();
                        for (unsigned int i = 0; i < temp.size(); i++)
                        {
                            DrawRelevantSquares(temp[i].first.first, temp[i].first.second, temp[i].second);
                        }

                        clicked_squares_list_.push_back(make_pair(clicked_square_row, clicked_square_col));
                    }
                }
            }

            else
            {
                vector <pair<pair <int, int>, _MOVE_TYPES>> temp = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> GetPossibleMoves();
                if (clicked_square_row == clicked_squares_list_[0].first && clicked_square_col == clicked_squares_list_[0].second) // Click the clicked square
                {
                    for (unsigned int i = 0; i < temp.size(); i++)
                    {
                        DrawDefaultColorSquare(temp[i].first.first, temp[i].first.second);
                        DrawPiece(temp[i].first.first, temp[i].first.second);
                    }

                    DrawDefaultColorSquare(clicked_square_row, clicked_square_col);
                    DrawPiece(clicked_square_row, clicked_square_col);
                    pieces_positions_[clicked_square_row][clicked_square_col] -> UnsetPossibleMoves();

                    clicked_squares_list_.clear();
                }
                else
                {
                    for (unsigned int i = 0; i < temp.size(); i++)
                    {
                        if (clicked_square_row == temp[i].first.first && clicked_square_col == temp[i].first.second) // Click a possible move
                        {
                            // Old relevant squares
                            for (unsigned int j = 0; j < temp.size(); j++)
                            {
                                DrawDefaultColorSquare(temp[j].first.first, temp[j].first.second);
                                DrawPiece(temp[j].first.first, temp[j].first.second);
                            }

                            if (temp[i].second == _MOVE || temp[i].second == _CAPTURE)
                            {
                                if (temp[i].second == _MOVE)
                                {
                                    // New square
                                    pieces_positions_[clicked_square_row][clicked_square_col] = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second];
                                    DrawPiece(clicked_square_row, clicked_square_col);
                                }
                                else if (temp[i].second == _CAPTURE)
                                {
                                    // New square
                                    DestroyPiece(clicked_square_row, clicked_square_col);
                                    pieces_positions_[clicked_square_row][clicked_square_col] = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second];
                                    DrawDefaultColorSquare(clicked_square_row, clicked_square_col);
                                    DrawPiece(clicked_square_row, clicked_square_col);
                                }

                                pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] = nullptr;
                                DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);
                            }

                            for (int row = 0; row < _BOARD_SIZE; row++)
                            {
                                for (int col = 0; col < _BOARD_SIZE; col++)
                                {
                                    if (pieces_positions_[row][col] != nullptr)
                                    {
                                        if (pieces_positions_[row][col] -> GetPieceColor() == side_to_move_)
                                        {
                                            pieces_positions_[row][col] -> UnsetPossibleMoves();
                                        }
                                    }
                                }
                            }

                            clicked_squares_list_.clear();

                            if (side_to_move_ == _BLACK)
                            {
                                side_to_move_ = _WHITE;
                            }
                            else if (side_to_move_ == _WHITE)
                            {
                                side_to_move_ = _BLACK;
                            }

                            message = _FINISHED_A_MOVE;
                            return message;
                        }
                    }

                    if (pieces_positions_[clicked_square_row][clicked_square_col] != nullptr)
                    {
                        if (pieces_positions_[clicked_square_row][clicked_square_col] -> GetPieceColor() == side_to_move_)
                        {
                            // Old relevant square
                            for (int i = 0; i < (int) temp.size(); i++)
                            {
                                DrawDefaultColorSquare(temp[i].first.first, temp[i].first.second);
                                DrawPiece(temp[i].first.first, temp[i].first.second);
                            }

                            // Old clicked square
                            DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);
                            DrawPiece(clicked_squares_list_[0].first, clicked_squares_list_[0].second);
                            pieces_positions_[clicked_square_row][clicked_square_col] -> UnsetPossibleMoves();
                            clicked_squares_list_.clear();

                            // New clicked square
                            DrawClickedSquare(clicked_square_row, clicked_square_col);
                            DrawPiece(clicked_square_row, clicked_square_col);

                            // New relevant squares
                            temp.clear();
                            pieces_positions_[clicked_square_row][clicked_square_col] -> SetPossibleMoves(clicked_square_row, clicked_square_col, pieces_positions_);
                            temp = pieces_positions_[clicked_square_row][clicked_square_col] -> GetPossibleMoves();
                            for (unsigned int i = 0; i < temp.size(); i++)
                            {
                                DrawRelevantSquares(temp[i].first.first, temp[i].first.second, temp[i].second);
                            }

                            clicked_squares_list_.push_back(make_pair(clicked_square_row, clicked_square_col));
                        }
                    }
                }
            }
        }
    }
    else if (EVENT.type == SDL_QUIT)
    {
        message = _QUIT;
    }

    return message;
}
