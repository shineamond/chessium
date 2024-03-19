#include "ChessBoard.h"



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

    legal_moves_set_ = false;
    has_legal_moves_ = false;
    side_to_move_first_ = _WHITE;
    side_to_move_ = _WHITE;
    no_capture_or_pawns_moves_ = 0;
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



void ChessBoard::DrawRelevantSquares(const int row, const int col, const _MOVE_TYPES move_type) const
{
    SDL_Rect drawing_position {col * _SQUARE_SIZE, row * _SQUARE_SIZE, _SQUARE_SIZE, _SQUARE_SIZE};

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



void ChessBoard::HandleGame(bool & game_end)
{
    if (!legal_moves_set_)
    {
        for (int row = 0; row < _BOARD_SIZE; row++)
        {
            for (int col = 0; col < _BOARD_SIZE; col++)
            {
                if (pieces_positions_[row][col] != nullptr)
                {
                    if (pieces_positions_[row][col] -> GetPieceColor() == side_to_move_)
                    {
                        pieces_positions_[row][col] -> SetPossibleMoves(row, col, pieces_positions_);
                        vector <pair<pair <int, int>, _MOVE_TYPES>> temp = pieces_positions_[row][col] -> GetPossibleMoves();
                        pieces_positions_[row][col] -> UnsetPossibleMoves();

                        for (unsigned int i = 0; i < temp.size(); i++)
                        {
                            if (IsLegalMove(row, col, temp[i].first.first, temp[i].first.second, temp[i].second))
                            {
                                pieces_positions_[row][col] -> AddLegalMoves(temp[i].first.first, temp[i].first.second, temp[i].second);
                            }
                        }

                        temp.clear();
                        temp = pieces_positions_[row][col] -> GetLegalMoves();
                        if (temp.size() != 0)
                        {
                            has_legal_moves_ = true;
                        }
                    }
                }
            }
        }

        AddLegalCastling();
        if (AddEnPassantMove())
        {
            has_legal_moves_ = true;
        }

        legal_moves_set_ = true;
    }

    if (!has_legal_moves_)
    {
        game_end = true;
        if (IsKingInCheck(side_to_move_))
        {
            switch (side_to_move_)
            {
                case _BLACK:
                    cout << "White wins\n";
                    break;
                case _WHITE:
                    cout << "Black wins\n";
                    break;
                default:
                    break;
            }
        }
        else
        {
            cout << "Draw\n";
        }

        return;
    }


    if (EVENT.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouse_position_x, mouse_position_y;
        SDL_GetMouseState(&mouse_position_x, &mouse_position_y);

        int clicked_square_row = mouse_position_y / _SQUARE_SIZE;
        int clicked_square_col = mouse_position_x / _SQUARE_SIZE;

        if (clicked_squares_list_.empty()) // Click a square
        {
            if (pieces_positions_[clicked_square_row][clicked_square_col] != nullptr)
            {
                if (pieces_positions_[clicked_square_row][clicked_square_col] -> GetPieceColor() == side_to_move_)
                {
                    DrawClickedSquare(clicked_square_row, clicked_square_col);
                    DrawPiece(clicked_square_row, clicked_square_col);

                    vector <pair<pair <int, int>, _MOVE_TYPES>> temp = pieces_positions_[clicked_square_row][clicked_square_col] -> GetLegalMoves();
                    for (unsigned int i = 0; i < temp.size(); i++)
                    {
                        DrawRelevantSquares(temp[i].first.first, temp[i].first.second, temp[i].second);
                    }

                    clicked_squares_list_.push_back(make_pair(clicked_square_row, clicked_square_col));
                }
            }
        }
        else // A square has already been clicked
        {
            vector <pair<pair <int, int>, _MOVE_TYPES>> temp = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> GetLegalMoves();
            if (clicked_square_row == clicked_squares_list_[0].first && clicked_square_col == clicked_squares_list_[0].second) // Click the clicked square
            {
                for (unsigned int i = 0; i < temp.size(); i++)
                {
                    DrawDefaultColorSquare(temp[i].first.first, temp[i].first.second);
                    DrawPiece(temp[i].first.first, temp[i].first.second);
                }

                DrawDefaultColorSquare(clicked_square_row, clicked_square_col);
                DrawPiece(clicked_square_row, clicked_square_col);

                clicked_squares_list_.clear();
            }
            else
            {
                bool is_move = false, is_capture = false, is_castle = false;
                for (unsigned int i = 0; i < temp.size(); i++)
                {
                    if (clicked_square_row == temp[i].first.first && clicked_square_col == temp[i].first.second) // Click a legal move
                    {
                        // Old relevant squares
                        for (int j = 0; j < (int) temp.size(); j++)
                        {
                            DrawDefaultColorSquare(temp[j].first.first, temp[j].first.second);
                            DrawPiece(temp[j].first.first, temp[j].first.second);
                        }

                        if (temp[i].second == _MOVE || temp[i].second == _CAPTURE || temp[i].second == _EN_PASSANT)
                        {
                            if (temp[i].second == _MOVE) // Move to an empty square
                            {
                                is_move = true;

                                // New square
                                pieces_positions_[clicked_square_row][clicked_square_col] = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second];
                                DrawPiece(clicked_square_row, clicked_square_col);
                            }
                            else if (temp[i].second == _CAPTURE) // Take another piece
                            {
                                is_capture = true;

                                // New square
                                DestroyPiece(clicked_square_row, clicked_square_col);
                                pieces_positions_[clicked_square_row][clicked_square_col] = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second];
                                DrawDefaultColorSquare(clicked_square_row, clicked_square_col);
                                DrawPiece(clicked_square_row, clicked_square_col);

                                //no_capture_or_pawns_moves_ += 1;
                            }
                            else if (temp[i].second == _EN_PASSANT)
                            {
                                is_capture = true;

                                // New square
                                pieces_positions_[clicked_square_row][clicked_square_col] = pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second];
                                DrawPiece(clicked_square_row, clicked_square_col);

                                switch (side_to_move_)
                                {
                                    case _BLACK:
                                        DestroyPiece(clicked_square_row - 1, clicked_square_col);
                                        pieces_positions_[clicked_square_row - 1][clicked_square_col] = nullptr;
                                        DrawDefaultColorSquare(clicked_square_row - 1, clicked_square_col);
                                        break;

                                    case _WHITE:
                                        DestroyPiece(clicked_square_row + 1, clicked_square_col);
                                        pieces_positions_[clicked_square_row + 1][clicked_square_col] = nullptr;
                                        DrawDefaultColorSquare(clicked_square_row + 1, clicked_square_col);
                                        break;

                                    default:
                                        break;
                                }

                                //no_capture_or_pawns_moves_ = 0;
                            }

                            pieces_positions_[clicked_square_row][clicked_square_col] -> SetMoved();
                            moves_log_.push_back(MoveInformation(pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] -> GetPieceType(),
                                                                     clicked_squares_list_[0], make_pair(clicked_square_row, clicked_square_col), temp[i].second));

                            // Old squares
                            pieces_positions_[clicked_squares_list_[0].first][clicked_squares_list_[0].second] = nullptr;
                            DrawDefaultColorSquare(clicked_squares_list_[0].first, clicked_squares_list_[0].second);
                        }
                        else if (temp[i].second == _CASTLE)
                        {
                            is_castle = true;

                            if (clicked_square_row == 0) // Black castles
                            {
                                if (clicked_square_col == 2)
                                {
                                    pieces_positions_[0][2] = pieces_positions_[0][4];
                                    pieces_positions_[0][4] = nullptr;
                                    pieces_positions_[0][3] = pieces_positions_[0][0];
                                    pieces_positions_[0][0] = nullptr;

                                    pieces_positions_[0][2] -> SetMoved();
                                    pieces_positions_[0][3] -> SetMoved();

                                    for (int col = 0; col <= 4; col++)
                                    {
                                        DrawDefaultColorSquare(0, col);
                                        DrawPiece(0, col);
                                    }
                                }

                                else if (clicked_square_col == 6)
                                {
                                    pieces_positions_[0][6] = pieces_positions_[0][4];
                                    pieces_positions_[0][4] = nullptr;
                                    pieces_positions_[0][5] = pieces_positions_[0][7];
                                    pieces_positions_[0][7] = nullptr;

                                    pieces_positions_[0][6] -> SetMoved();
                                    pieces_positions_[0][5] -> SetMoved();

                                    for (int col = 4; col < _BOARD_SIZE; col++)
                                    {
                                        DrawDefaultColorSquare(0, col);
                                        DrawPiece(0, col);
                                    }
                                }
                            }

                            else if (clicked_square_row == 7) // White castles
                            {
                                if (clicked_square_col == 2)
                                {
                                    pieces_positions_[7][2] = pieces_positions_[7][4];
                                    pieces_positions_[7][4] = nullptr;
                                    pieces_positions_[7][3] = pieces_positions_[7][0];
                                    pieces_positions_[7][0] = nullptr;

                                    pieces_positions_[7][2] -> SetMoved();
                                    pieces_positions_[7][3] -> SetMoved();

                                    for (int col = 0; col <= 4; col++)
                                    {
                                        DrawDefaultColorSquare(7, col);
                                        DrawPiece(7, col);
                                    }
                                }

                                else if (clicked_square_col == 6)
                                {
                                    pieces_positions_[7][6] = pieces_positions_[7][4];
                                    pieces_positions_[7][4] = nullptr;
                                    pieces_positions_[7][5] = pieces_positions_[7][7];
                                    pieces_positions_[7][7] = nullptr;

                                    pieces_positions_[7][6] -> SetMoved();
                                    pieces_positions_[7][5] -> SetMoved();

                                    for (int col = 4; col < _BOARD_SIZE; col++)
                                    {
                                        DrawDefaultColorSquare(7, col);
                                        DrawPiece(7, col);
                                    }
                                }
                            }

                            moves_log_.push_back(MoveInformation(_CASTLE));
                        }

                        for (int row = 0; row < _BOARD_SIZE; row++)
                        {
                            for (int col = 0; col < _BOARD_SIZE; col++)
                            {
                                if (pieces_positions_[row][col] != nullptr)
                                {
                                    if (pieces_positions_[row][col] -> GetPieceColor() == side_to_move_)
                                    {
                                        pieces_positions_[row][col] -> UnsetLegalMoves();
                                    }
                                }
                            }
                        }

                        legal_moves_set_ = false;
                        has_legal_moves_ = false;
                        clicked_squares_list_.clear();

                        if (pieces_positions_[clicked_square_row][clicked_square_col] -> GetPieceType() == _PAWN)
                        {
                            if (pieces_positions_[clicked_square_row][clicked_square_col] -> GetPieceColor() == _WHITE && clicked_square_row == 0)
                            {
                                PromotePawn(clicked_square_col, _WHITE);
                            }
                            else if (pieces_positions_[clicked_square_row][clicked_square_col] -> GetPieceColor() == _BLACK && clicked_square_row == 7)
                            {
                                PromotePawn(clicked_square_col, _BLACK);
                            }
                        }

                        if (side_to_move_ == _WHITE)
                        {
                            side_to_move_ = _BLACK;
                        }
                        else if (side_to_move_ == _BLACK)
                        {
                            side_to_move_ = _WHITE;
                        }

                        if (side_to_move_ == side_to_move_first_)
                        {
                            if (IsDraw50Moves())
                            {
                                cout << "Draw\n";
                                game_end = true;

                                return;
                            }
                        }

                        break;
                    }
                }

                if (!(is_move || is_capture || is_castle))
                {
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
                            clicked_squares_list_.clear();

                            // New clicked square
                            DrawClickedSquare(clicked_square_row, clicked_square_col);
                            DrawPiece(clicked_square_row, clicked_square_col);

                            // New relevant squares
                            temp.clear();
                            temp = pieces_positions_[clicked_square_row][clicked_square_col] -> GetLegalMoves();
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



void ChessBoard::PromotePawn(const int col, const _CHESS_PIECE_COLORS color)
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
        while (SDL_PollEvent(&EVENT))
        {
            if (EVENT.type == SDL_MOUSEBUTTONDOWN)
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
//            else if (EVENT.type == SDL_QUIT)
//            {
//
//            }
        }
    }
}



pair <int, int> ChessBoard::GetWhiteKingPosition() const
{
    for (int row = 7; row >= 0; row--)
    {
        for (int col = 7; col >= 0; col--)
        {
            if (pieces_positions_[row][col] != nullptr)
            {
                if (pieces_positions_[row][col] -> GetPieceType() == _KING)
                {
                    if (pieces_positions_[row][col] -> GetPieceColor() == _WHITE)
                    {
                        return (make_pair(row, col));
                    }
                }
            }
        }
    }
}



pair <int, int> ChessBoard::GetBlackKingPosition() const
{
    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col <_BOARD_SIZE; col++)
        {
            if (pieces_positions_[row][col] != nullptr)
            {
                if (pieces_positions_[row][col] -> GetPieceType() == _KING)
                {
                    if (pieces_positions_[row][col] -> GetPieceColor() == _BLACK)
                    {
                        return (make_pair(row, col));
                    }
                }
            }
        }
    }
}



bool ChessBoard::IsKingInCheck(const _CHESS_PIECE_COLORS king_color)
{
    pair <int, int> king_position;
    switch (king_color)
    {
        case _BLACK:
            king_position = GetBlackKingPosition();
            break;

        case _WHITE:
            king_position = GetWhiteKingPosition();
            break;

        default:
            break;
    }

    for (int row = 0; row < _BOARD_SIZE; row++)
    {
        for (int col = 0; col < _BOARD_SIZE; col++)
        {
            if (pieces_positions_[row][col] != nullptr)
            {
                if (pieces_positions_[row][col] -> GetPieceColor() != king_color)
                {
                    pieces_positions_[row][col] -> SetCoveringSquares(row, col, pieces_positions_);
                    vector <pair <int, int>> temp = pieces_positions_[row][col] -> GetCoveringSquares();
                    pieces_positions_[row][col] -> UnsetCoveringSquares();

                    for (unsigned int i = 0; i < temp.size(); i++)
                    {
                        if (temp[i].first == king_position.first && temp[i].second == king_position.second)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}



bool ChessBoard::IsLegalMove(const int old_row, const int old_col, const int new_row, const int new_col, const _MOVE_TYPES move_type)
{
    bool is_legal = true;

    if (move_type == _MOVE)
    {
        // Try to move
        pieces_positions_[new_row][new_col] = pieces_positions_[old_row][old_col];
        pieces_positions_[old_row][old_col] = nullptr;

        if (IsKingInCheck(side_to_move_) == true)
        {
            is_legal = false;
        }

        // Revert
        pieces_positions_[old_row][old_col] = pieces_positions_[new_row][new_col];
        pieces_positions_[new_row][new_col] = nullptr;
    }
    else if (move_type == _CAPTURE)
    {
        //Try to move
        ChessPiece* temp = pieces_positions_[new_row][new_col];
        pieces_positions_[new_row][new_col] = pieces_positions_[old_row][old_col];
        pieces_positions_[old_row][old_col] = nullptr;

        if (IsKingInCheck(side_to_move_) == true)
        {
            is_legal = false;
        }

        //Revert
        pieces_positions_[old_row][old_col] = pieces_positions_[new_row][new_col];
        pieces_positions_[new_row][new_col] = temp;
        temp = nullptr;
    }

    return is_legal;
}



void ChessBoard::AddLegalCastling()
{
    switch (side_to_move_)
    {
        case _BLACK:
            if (pieces_positions_[0][4] != nullptr)
            {
                if (pieces_positions_[0][4] -> GetPieceType() == _KING)
                {
                    if (pieces_positions_[0][4] -> GetPieceColor() == _BLACK)
                    {
                        if (IsKingInCheck(_BLACK) == false)
                        {
                            if (pieces_positions_[0][4] -> GetMoved() == false)
                            {
                                if (pieces_positions_[0][0] != nullptr)
                                {
                                    if (pieces_positions_[0][0] -> GetPieceType() == _ROOK)
                                    {
                                        if (pieces_positions_[0][0] -> GetPieceColor() == _BLACK)
                                        {
                                            if (pieces_positions_[0][0] -> GetMoved() == false)
                                            {
                                                bool has_pieces_between = false;
                                                for (int col = 1; col <= 3; col++)
                                                {
                                                    if (pieces_positions_[0][col] != nullptr)
                                                    {
                                                        has_pieces_between = true;
                                                        break;
                                                    }
                                                }

                                                if (!has_pieces_between)
                                                {
                                                    bool can_castle = true;

                                                    for (int row = 0; row < _BOARD_SIZE; row++)
                                                    {
                                                        for (int col = 0; col < _BOARD_SIZE; col++)
                                                        {
                                                            if (pieces_positions_[row][col] != nullptr)
                                                            {
                                                                if (pieces_positions_[row][col] -> GetPieceColor() == _WHITE)
                                                                {
                                                                    pieces_positions_[row][col] -> SetCoveringSquares(row, col, pieces_positions_);
                                                                    vector <pair <int, int>> temp = pieces_positions_[row][col] -> GetCoveringSquares();
                                                                    pieces_positions_[row][col] -> UnsetCoveringSquares();

                                                                    for (unsigned int i = 0; i < temp.size(); i++)
                                                                    {
                                                                        if (temp[i].first == 0)
                                                                        {
                                                                            if (temp[i].second == 1 || temp[i].second == 2 || temp[i].second == 3)
                                                                            {
                                                                                can_castle = false;
                                                                                break;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (can_castle)
                                                    {
                                                        pieces_positions_[0][4] -> AddLegalMoves(0, 2, _CASTLE);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                if (pieces_positions_[0][7] != nullptr)
                                {
                                    if (pieces_positions_[0][7] -> GetPieceType() == _ROOK)
                                    {
                                        if (pieces_positions_[0][7] -> GetPieceColor() == _BLACK)
                                        {
                                            if (pieces_positions_[0][7] -> GetMoved() == false)
                                            {
                                                bool has_pieces_between = false;
                                                for (int col = 5; col <= 6; col++)
                                                {
                                                    if (pieces_positions_[0][col] != nullptr)
                                                    {
                                                        has_pieces_between = true;
                                                        break;
                                                    }
                                                }

                                                if (!has_pieces_between)
                                                {
                                                    bool can_castle = true;

                                                    for (int row = 0; row < _BOARD_SIZE; row++)
                                                    {
                                                        for (int col = 0; col < _BOARD_SIZE; col++)
                                                        {
                                                            if (pieces_positions_[row][col] != nullptr)
                                                            {
                                                                if (pieces_positions_[row][col] -> GetPieceColor() == _WHITE)
                                                                {
                                                                    pieces_positions_[row][col] -> SetCoveringSquares(row, col, pieces_positions_);
                                                                    vector <pair <int, int>> temp = pieces_positions_[row][col] -> GetCoveringSquares();
                                                                    pieces_positions_[row][col] -> UnsetCoveringSquares();

                                                                    for (unsigned int i = 0; i < temp.size(); i++)
                                                                    {
                                                                        if (temp[i].first == 0)
                                                                        {
                                                                            if (temp[i].second == 5 || temp[i].second == 6)
                                                                            {
                                                                                can_castle = false;
                                                                                break;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (can_castle)
                                                    {
                                                        pieces_positions_[0][4] -> AddLegalMoves(0, 6, _CASTLE);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            break;

        case _WHITE:
            if (pieces_positions_[7][4] != nullptr)
            {
                if (pieces_positions_[7][4] -> GetPieceType() == _KING)
                {
                    if (pieces_positions_[7][4] -> GetPieceColor() == _WHITE)
                    {
                        if (IsKingInCheck(_WHITE) == false)
                        {
                            if (pieces_positions_[7][4] -> GetMoved() == false)
                            {
                                if (pieces_positions_[7][0] != nullptr)
                                {
                                    if (pieces_positions_[7][0] -> GetPieceType() == _ROOK)
                                    {
                                        if (pieces_positions_[7][0] -> GetPieceColor() == _WHITE)
                                        {
                                            if (pieces_positions_[7][0] -> GetMoved() == false)
                                            {
                                                bool has_pieces_between = false;
                                                for (int col = 1; col <= 3; col++)
                                                {
                                                    if (pieces_positions_[7][col] != nullptr)
                                                    {
                                                        has_pieces_between = true;
                                                        break;
                                                    }
                                                }

                                                if (!has_pieces_between)
                                                {
                                                    bool can_castle = true;

                                                    for (int row = 0; row < _BOARD_SIZE; row++)
                                                    {
                                                        for (int col = 0; col < _BOARD_SIZE; col++)
                                                        {
                                                            if (pieces_positions_[row][col] != nullptr)
                                                            {
                                                                if (pieces_positions_[row][col] -> GetPieceColor() == _BLACK)
                                                                {
                                                                    pieces_positions_[row][col] -> SetCoveringSquares(row, col, pieces_positions_);
                                                                    vector <pair <int, int>> temp = pieces_positions_[row][col] -> GetCoveringSquares();
                                                                    pieces_positions_[row][col] -> UnsetCoveringSquares();

                                                                    for (unsigned int i = 0; i < temp.size(); i++)
                                                                    {
                                                                        if (temp[i].first == 7)
                                                                        {
                                                                            if (temp[i].second == 1 || temp[i].second == 2 || temp[i].second == 3)
                                                                            {
                                                                                can_castle = false;
                                                                                break;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (can_castle)
                                                    {
                                                        pieces_positions_[7][4] -> AddLegalMoves(7, 2, _CASTLE);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                if (pieces_positions_[7][7] != nullptr)
                                {
                                    if (pieces_positions_[7][7] -> GetPieceType() == _ROOK)
                                    {
                                        if (pieces_positions_[7][7] -> GetPieceColor() == _WHITE)
                                        {
                                            if (pieces_positions_[7][7] -> GetMoved() == false)
                                            {
                                                bool has_pieces_between = false;
                                                for (int col = 5; col <= 6; col++)
                                                {
                                                    if (pieces_positions_[7][col] != nullptr)
                                                    {
                                                        has_pieces_between = true;
                                                        break;
                                                    }
                                                }

                                                if (!has_pieces_between)
                                                {
                                                    bool can_castle = true;

                                                    for (int row = 0; row < _BOARD_SIZE; row++)
                                                    {
                                                        for (int col = 0; col < _BOARD_SIZE; col++)
                                                        {
                                                            if (pieces_positions_[row][col] != nullptr)
                                                            {
                                                                if (pieces_positions_[row][col] -> GetPieceColor() == _BLACK)
                                                                {
                                                                    pieces_positions_[row][col] -> SetCoveringSquares(row, col, pieces_positions_);
                                                                    vector <pair <int, int>> temp = pieces_positions_[row][col] -> GetCoveringSquares();
                                                                    pieces_positions_[row][col] -> UnsetCoveringSquares();

                                                                    for (unsigned int i = 0; i < temp.size(); i++)
                                                                    {
                                                                        if (temp[i].first == 7)
                                                                        {
                                                                            if (temp[i].second == 5 || temp[i].second == 6)
                                                                            {
                                                                                can_castle = false;
                                                                                break;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }

                                                    if (can_castle)
                                                    {
                                                        pieces_positions_[7][4] -> AddLegalMoves(7, 6, _CASTLE);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            break;

        default:
            break;
    }
}



bool ChessBoard::AddEnPassantMove()
{
    bool has_en_passant_moves = false;
    unsigned int log_size = moves_log_.size();

    if (log_size > 0)
    {
        MoveInformation last_move = moves_log_[log_size - 1];

        if (last_move.GetMovedPiece() == _PAWN)
        {
            pair <int, int> new_position = last_move.GetNewPosition();

            switch (side_to_move_)
            {
                case _BLACK:
                    if (new_position.first - last_move.GetOldPosition().first == -2)
                    {
                        if (new_position.second - 1 >= 0)
                        {
                            if (pieces_positions_[new_position.first][new_position.second - 1] != nullptr)
                            {
                                if (pieces_positions_[new_position.first][new_position.second - 1] -> GetPieceType() == _PAWN)
                                {
                                    if (pieces_positions_[new_position.first][new_position.second - 1] -> GetPieceColor() == _BLACK)
                                    {
                                        pieces_positions_[new_position.first][new_position.second - 1] -> AddLegalMoves(new_position.first + 1, new_position.second, _EN_PASSANT);
                                        has_en_passant_moves = true;
                                    }
                                }
                            }
                        }

                        if (new_position.second + 1 < _BOARD_SIZE)
                        {
                            if (pieces_positions_[new_position.first][new_position.second + 1] != nullptr)
                            {
                                if (pieces_positions_[new_position.first][new_position.second + 1] -> GetPieceType() == _PAWN)
                                {
                                    if (pieces_positions_[new_position.first][new_position.second + 1] -> GetPieceColor() == _BLACK)
                                    {
                                        pieces_positions_[new_position.first][new_position.second + 1] -> AddLegalMoves(new_position.first + 1, new_position.second, _EN_PASSANT);
                                        has_en_passant_moves = true;
                                    }
                                }
                            }
                        }
                    }
                    break;

                case _WHITE:
                    if (new_position.first - last_move.GetOldPosition().first == 2)
                    {
                        if (new_position.second - 1 >= 0)
                        {
                            if (pieces_positions_[new_position.first][new_position.second - 1] != nullptr)
                            {
                                if (pieces_positions_[new_position.first][new_position.second - 1] -> GetPieceType() == _PAWN)
                                {
                                    if (pieces_positions_[new_position.first][new_position.second - 1] -> GetPieceColor() == _WHITE)
                                    {
                                        pieces_positions_[new_position.first][new_position.second - 1] -> AddLegalMoves(new_position.first - 1, new_position.second, _EN_PASSANT);
                                        has_en_passant_moves = true;
                                    }
                                }
                            }
                        }

                        if (new_position.second + 1 < _BOARD_SIZE)
                        {
                            if (pieces_positions_[new_position.first][new_position.second + 1] != nullptr)
                            {
                                if (pieces_positions_[new_position.first][new_position.second + 1] -> GetPieceType() == _PAWN)
                                {
                                    if (pieces_positions_[new_position.first][new_position.second + 1] -> GetPieceColor() == _WHITE)
                                    {
                                        pieces_positions_[new_position.first][new_position.second + 1] -> AddLegalMoves(new_position.first - 1, new_position.second, _EN_PASSANT);
                                        has_en_passant_moves = true;
                                    }
                                }
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }
    }

    return has_en_passant_moves;
}



bool ChessBoard::IsDraw50Moves()
{
    int log_size = moves_log_.size();

    if (moves_log_[log_size - 2].GetMoveType() == _CAPTURE || moves_log_[log_size - 2].GetMovedPiece() == _PAWN)
    {
        no_capture_or_pawns_moves_ = 0;
    }
    else
    {
        if (moves_log_[log_size - 1].GetMoveType() == _CAPTURE || moves_log_[log_size - 1].GetMovedPiece() == _PAWN)
        {
            no_capture_or_pawns_moves_ = 0;
        }
        else
        {
            no_capture_or_pawns_moves_ += 1;
        }
    }

    if (no_capture_or_pawns_moves_ == 50)
    {
        return true;
    }

    return false;
}
