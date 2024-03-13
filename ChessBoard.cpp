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

        if (clicked_squares_list_.empty()) // Click a square
        {
            if (pieces_positions_[clicked_square_row][clicked_square_col] != nullptr)
            {
                DrawClickedSquare(clicked_square_row, clicked_square_col);
                DrawPiece(clicked_square_row, clicked_square_col);

                pieces_positions_[clicked_square_row][clicked_square_col] -> SetPossibleMoves(clicked_square_row, clicked_square_col, pieces_positions_);
                vector <pair<pair <int, int>, string>> temp = pieces_positions_[clicked_square_row][clicked_square_col] -> GetPossibleMoves();
                for (int i = 0; i < (int) temp.size(); i++)
                {
                    DrawMovableAndTakeableSquare(temp[i].first.first, temp[i].first.second, temp[i].second);
                }

                clicked_squares_list_.push_back(make_pair(clicked_square_row, clicked_square_col));
            }
        }
        else // A square has already been clicked
        {
            vector <pair<pair <int, int>, string>> temp = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> GetPossibleMoves();
            if (clicked_square_row == clicked_squares_list_[0].first && clicked_square_col == clicked_squares_list_[0].second) // Click the clicked square
            {
                for (int i = 0; i < (int) temp.size(); i++)
                {
                    DrawDefaultColorSquare(temp[i].first.first, temp[i].first.second);
                    DrawPiece(temp[i].first.first, temp[i].first.second);
                }

                pieces_positions_[clicked_square_row][clicked_square_col] -> UnsetPossibleMoves();
                DrawDefaultColorSquare(clicked_square_row, clicked_square_col);
                DrawPiece(clicked_square_row, clicked_square_col);

                clicked_squares_list_.clear();
            }
            else
            {
                bool is_move = false, is_capture = false;
                for (int i = 0; i < (int) temp.size(); i++)
                {
                    if (clicked_square_row == temp[i].first.first && clicked_square_col == temp[i].first.second) // Click a possible move
                    {
                        for (int j = 0; j < (int) temp.size(); j++)
                        {
                            DrawDefaultColorSquare(temp[j].first.first, temp[j].first.second);
                            DrawPiece(temp[j].first.first, temp[j].first.second);
                        }


                        if (temp[i].second == "_MOVABLE") // Move to an empty square
                        {
                            is_move = true;

                            // Old relevant squares
//                            for (int j = 0; j < (int) temp.size(); j++)
//                            {
//                                DrawDefaultColorSquare(temp[j].first.first, temp[j].first.second);
//                                DrawPiece(temp[j].first.first, temp[j].first.second);
//                            }

                            // New square
                            pieces_positions_[clicked_square_row][clicked_square_col] = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second];
                            DrawPiece(clicked_square_row, clicked_square_col);

                            // Old squares
//                            pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> UnsetPossibleMoves();
//                            pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] = nullptr;
//                            DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);

//                            clicked_squares_list_.clear();
                        }
                        else if (temp[i].second == "_TAKEABLE") // Take another piece
                        {
                            is_capture = true;

                            // Relevant squares
//                            for (int j = 0; j < (int) temp.size(); j++)
//                            {
//                                DrawDefaultColorSquare(temp[j].first.first, temp[j].first.second);
//                                DrawPiece(temp[j].first.first, temp[j].first.second);
//                            }

                            // New square
                            DestroyPiece(clicked_square_row, clicked_square_col);
                            pieces_positions_[clicked_square_row][clicked_square_col] = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second];
                            DrawDefaultColorSquare(clicked_square_row, clicked_square_col);
                            DrawPiece(clicked_square_row, clicked_square_col);

                            // Old square
//                            pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> UnsetPossibleMoves();
//                            pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] = nullptr;
//                            DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);

//                            clicked_squares_list_.clear();
                        }

                        // Old squares
                        pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> UnsetPossibleMoves();
                        pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] = nullptr;
                        DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);

                        clicked_squares_list_.clear();

                        if (pieces_positions_[clicked_square_row][clicked_square_col] -> GetPieceType() == _PAWN)
                        {
                            if (pieces_positions_[clicked_square_row][clicked_square_col] -> GetPieceColor() == _WHITE && clicked_square_row == 0)
                            {
                                PromotePawn(ev, clicked_square_col, _WHITE);
                            }
                            else if (pieces_positions_[clicked_square_row][clicked_square_col] -> GetPieceColor() == _BLACK && clicked_square_row == 7)
                            {
                                PromotePawn(ev, clicked_square_col, _BLACK);
                            }
                        }

                        break;
                    }
                }

                if (!(is_move || is_capture))
                {
                    if (pieces_positions_[clicked_square_row][clicked_square_col] != nullptr)
                    {
                        // Old relevant square
                        for (int j = 0; j < (int) temp.size(); j++)
                        {
                            DrawDefaultColorSquare(temp[j].first.first, temp[j].first.second);
                            DrawPiece(temp[j].first.first, temp[j].first.second);
                        }

                        // Old clicked square
                        DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);
                        DrawPiece(clicked_squares_list_[0].first, clicked_squares_list_[0].second);
                        pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> UnsetPossibleMoves();
                        clicked_squares_list_.clear();

                        // New clicked square
                        DrawClickedSquare(clicked_square_row, clicked_square_col);
                        DrawPiece(clicked_square_row, clicked_square_col);
                        pieces_positions_[clicked_square_row][clicked_square_col] -> SetPossibleMoves(clicked_square_row, clicked_square_col, pieces_positions_);

                        // New relevant squares
                        temp.clear();
                        temp = pieces_positions_[clicked_square_row][clicked_square_col] -> GetPossibleMoves();
                        for (int i = 0; i < (int) temp.size(); i++)
                        {
                            DrawMovableAndTakeableSquare(temp[i].first.first, temp[i].first.second, temp[i].second);
                        }

                        clicked_squares_list_.push_back(make_pair(clicked_square_row, clicked_square_col));
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



void ChessBoard::PromotePawn(SDL_Event & ev, const int col, const _CHESS_PIECE_COLORS color)
{
    SDL_Rect drawing_position;
    drawing_position.x = _SQUARE_SIZE * col;
    drawing_position.w = _SQUARE_SIZE;
    drawing_position.h = _SQUARE_SIZE * 4;

    if (color == _WHITE)
    {
        drawing_position.y = 0;

        SDL_RenderCopy(RENDERER, LoadTexture("media/white_promotion.png"), nullptr, &drawing_position);
    }
    else if (color == _BLACK)
    {
        drawing_position.y = _SQUARE_SIZE * 4;

        SDL_RenderCopy(RENDERER, LoadTexture("media/black_promotion.png"), nullptr, &drawing_position);
    }
    SDL_RenderPresent(RENDERER);

    bool promoted = false;
    while(!promoted)
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouse_position_x, mouse_position_y;
                SDL_GetMouseState(&mouse_position_x, &mouse_position_y);

                int clicked_square_row = mouse_position_y / _SQUARE_SIZE;
                int clicked_square_col = mouse_position_x / _SQUARE_SIZE;

                if (clicked_square_row * _SQUARE_SIZE != mouse_position_y && clicked_square_col * _SQUARE_SIZE != mouse_position_x)
                {
                    if (color == _WHITE)
                    {
                        if (clicked_square_col == col && clicked_square_row < 4)
                        {
                            DestroyPiece(0, col);
                            switch(clicked_square_row)
                            {
                                case 0:
                                    PutPiece(0, col, _QUEEN, _WHITE);
                                    break;
                                case 1:
                                    PutPiece(0, col, _KNIGHT, _WHITE);
                                    break;
                                case 2:
                                    PutPiece(0, col, _ROOK, _WHITE);
                                    break;
                                case 3:
                                    PutPiece(0, col, _BISHOP, _WHITE);
                                    break;
                            }

                            for (int temp_row = 0; temp_row < 4; temp_row++)
                            {
                                DrawDefaultColorSquare(temp_row, col);
                                DrawPiece(temp_row, col);
                            }

                            promoted = true;
                        }
                    }
                    else if (color == _BLACK)
                    {
                        if (clicked_square_col == col && clicked_square_row >= 4)
                        {
                            DestroyPiece(7, col);
                            switch(clicked_square_row)
                            {
                                case 4:
                                    PutPiece(7, col, _BISHOP, _BLACK);
                                    break;
                                case 5:
                                    PutPiece(7, col, _ROOK, _BLACK);
                                    break;
                                case 6:
                                    PutPiece(7, col, _KNIGHT, _BLACK);
                                    break;
                                case 7:
                                    PutPiece(7, col, _QUEEN, _BLACK);
                                    break;
                            }

                            for (int temp_row = 4; temp_row < _BOARD_SIZE; temp_row++)
                            {
                                DrawDefaultColorSquare(temp_row, col);
                                DrawPiece(temp_row, col);
                            }

                            promoted = true;
                        }
                    }
                }
            }
//            else if (ev.type == SDL_QUIT)
//            {
//
//            }
        }
    }
}
