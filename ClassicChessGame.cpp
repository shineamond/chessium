#include "ClassicChessGame.h"



ClassicChessGame::ClassicChessGame()
{
    board_ = ClassicChessBoard();
    clock_ = ChessClock(0, 0);
    side_to_move_first_ = _WHITE;
    side_to_move_ = _WHITE;
    //running_ = false;
    game_over_ = true;
    white_score_ = 0;
    black_score_ = 0;
}



void ClassicChessGame::DrawPlayers() const
{
    SDL_Rect player_pfp_position {0, 5, 50, 50};
    SDL_RenderCopy(RENDERER, LoadTexture("media/anonymous.png"), nullptr, &player_pfp_position);
    WrappedTexture player1_name;
    player1_name.SetupTextureFromText(24, false, "Black", _WHITE_COLOR);
    player1_name.Render(60, 13);

    player_pfp_position.y = 705;
    SDL_RenderCopy(RENDERER, LoadTexture("media/anonymous.png"), nullptr, &player_pfp_position);
    WrappedTexture player2_name;
    player2_name.SetupTextureFromText(24, false, "White", _WHITE_COLOR);
    player2_name.Render(60, 714);

    SDL_RenderPresent(RENDERER);
}



bool ClassicChessGame::Setup()
{
    board_.ResetBoard();
    board_.SetupDefaultBoard();
    board_.CountPieces();
    board_.DrawChessBoardAndPieces();

    side_to_move_ = _WHITE;

    if (!SetupTimer())
    {
        return false;
    }
    game_over_ = false;

    return true;
}



void ClassicChessGame::Start()
{
    //running_ = true;
    RenderScoreInMatch();
    game_over_ = false;
    if (clock_.GetTimeLimit() != 0)
    {
        RunGameWithTimer();
    }
    else
    {
        RunGameWithoutTimer();
    }
}



void ClassicChessGame::RunGameWithTimer()
{
    clock_.StartClock();

    while (!game_over_)
    {
        clock_.SetSideToMove(side_to_move_);
        clock_.RenderTime();
        SDL_RenderPresent(RENDERER);

        if(clock_.GetTimeLeft(_BLACK) == 0)
        {
            if (board_.IsOnlyKingLeft(_WHITE))
            {
                cout << "Draw\n";
                white_score_ += 1;
                black_score_ += 1;
            }
            else
            {
                cout << "White wins\n";
                white_score_ += 1;
            }

            clock_.StopClock();
            game_over_ = true;
        }
        else if (clock_.GetTimeLeft(_WHITE) == 0)
        {
            if (board_.IsOnlyKingLeft(_BLACK))
            {
                cout << "Draw\n";
                white_score_ += 1;
                black_score_ += 1;
            }
            else
            {
                cout << "Black wins\n";
                black_score_ += 1;
            }

            clock_.StopClock();
            game_over_ = true;
        }

        while (SDL_PollEvent(&EVENT) != 0)
        {
            if (!game_over_)
            {
                _MESSAGES_FROM_CHESSBOARD message = board_.HandleGame(side_to_move_);
                if (message == _FINISHED_A_MOVE)
                {
                    clock_.AddExtraTime();
                    if (side_to_move_ == _WHITE)
                    {

                        side_to_move_ = _BLACK;
                    }
                    else if (side_to_move_ ==  _BLACK)
                    {
                        side_to_move_ = _WHITE;
                    }
                }
                else if (message == _WHITE_WINS)
                {
                    clock_.StopClock();
                    white_score_ += 1;
                    game_over_ = true;
                }
                else if (message == _BLACK_WINS)
                {
                    clock_.StopClock();
                    black_score_ += 1;
                    game_over_ = true;
                }
                else if (message == _DRAW)
                {
                    clock_.StopClock();
                    white_score_ += 1;
                    black_score_ += 1;
                    game_over_ = true;
                }
                else if (message == _QUIT)
                {
                    clock_.StopClock();
                    game_over_ = true;
                    in_gameloop = false;
                    return;
                }

                SDL_RenderPresent(RENDERER);
            }
        }
    }

    WaitUntilKeyPressed();
}



void ClassicChessGame::RunGameWithoutTimer()
{
    while (!game_over_)
    {
        while (SDL_PollEvent(&EVENT) != 0)
        {
            _MESSAGES_FROM_CHESSBOARD message = board_.HandleGame(side_to_move_);
            if (message == _FINISHED_A_MOVE)
            {
                if (side_to_move_ == _WHITE)
                {
                    side_to_move_ = _BLACK;
                }
                else if (side_to_move_ ==  _BLACK)
                {
                    side_to_move_ = _WHITE;
                }
            }
            else if (message == _WHITE_WINS)
            {
                white_score_ += 1;
                game_over_ = true;
            }
            else if (message == _BLACK_WINS)
            {
                black_score_ += 1;
                game_over_ = true;
            }
            else if (message == _DRAW)
            {
                white_score_ += 1;
                black_score_ += 1;
                game_over_ = true;
            }
            else if (message == _QUIT)
            {
                game_over_ = true;
                in_gameloop = false;
                return;
            }
            SDL_RenderPresent(RENDERER);


            if (EVENT.type == SDL_QUIT)
            {
                game_over_ = true;
                return;
            }
        }
    }

    WaitUntilKeyPressed();
}



bool ClassicChessGame::SetupTimer()
{
    RenderScoreWhileSelectingTimer();

    SDL_SetRenderDrawColor(RENDERER, 100, 100, 100, 200); // LIGHT BLACK
    vector <SDL_Rect> all_button_areas;

    // Bullet category
    SDL_Texture* bullet_icon = LoadTexture("media/bullet_icon.png");
    SDL_Rect bullet_icon_area{700, 280, 20, 20};
    SDL_RenderCopy(RENDERER, bullet_icon, nullptr, &bullet_icon_area);

    WrappedTexture bullet_title;
    bullet_title.SetupTextureFromText(12, true, "Bullet", _WHITE_COLOR);
    bullet_title.Render(725, 280);

    SDL_Rect bullet_1_area{700, 300, 80, 40};
    SDL_RenderFillRect(RENDERER, &bullet_1_area);
    WrappedTexture bullet_1;
    bullet_1.SetupTextureFromText(18, true, "1 min", _WHITE_COLOR);
    bullet_1.Render(bullet_1_area.x + (bullet_1_area.w - bullet_1.GetWidth()) / 2, bullet_1_area.y + (bullet_1_area.h - bullet_1.GetHeight()) / 2);
    all_button_areas.push_back(bullet_1_area);

    SDL_Rect bullet_2_area{800, 300, 80, 40};
    SDL_RenderFillRect(RENDERER, &bullet_2_area);
    WrappedTexture bullet_2;
    bullet_2.SetupTextureFromText(18, true, "1 | 1", _WHITE_COLOR);
    bullet_2.Render(bullet_2_area.x + (bullet_2_area.w - bullet_2.GetWidth()) / 2, bullet_2_area.y + (bullet_2_area.h - bullet_2.GetHeight()) / 2);
    all_button_areas.push_back(bullet_2_area);

    SDL_Rect bullet_3_area{900, 300, 80, 40};
    SDL_RenderFillRect(RENDERER, &bullet_3_area);
    WrappedTexture bullet_3;
    bullet_3.SetupTextureFromText(18, true, "2 | 1", _WHITE_COLOR);
    bullet_3.Render(bullet_3_area.x + (bullet_3_area.w - bullet_3.GetWidth()) / 2, bullet_3_area.y + (bullet_3_area.h - bullet_3.GetHeight()) / 2);
    all_button_areas.push_back(bullet_3_area);

    // Blitz category
    SDL_Texture* blitz_icon = LoadTexture("media/blitz_icon.png");
    SDL_Rect blitz_icon_area{700, 355, 20, 25};
    SDL_RenderCopy(RENDERER, blitz_icon, nullptr, &blitz_icon_area);

    WrappedTexture blitz_title;
    blitz_title.SetupTextureFromText(12, true, "Blitz", _WHITE_COLOR);
    blitz_title.Render(725, 360);

    SDL_Rect blitz_1_area{700, 380, 80, 40};
    SDL_RenderFillRect(RENDERER, &blitz_1_area);
    WrappedTexture blitz_1;
    blitz_1.SetupTextureFromText(18, true, "3 min", _WHITE_COLOR);
    blitz_1.Render(blitz_1_area.x + (blitz_1_area.w - blitz_1.GetWidth()) / 2, blitz_1_area.y + (blitz_1_area.h - blitz_1.GetHeight()) / 2);
    all_button_areas.push_back(blitz_1_area);

    SDL_Rect blitz_2_area{800, 380, 80, 40};
    SDL_RenderFillRect(RENDERER, &blitz_2_area);
    WrappedTexture blitz_2;
    blitz_2.SetupTextureFromText(18, true, "3 | 2", _WHITE_COLOR);
    blitz_2.Render(blitz_2_area.x + (blitz_2_area.w - blitz_2.GetWidth()) / 2, blitz_2_area.y + (blitz_2_area.h - blitz_2.GetHeight()) / 2);
    all_button_areas.push_back(blitz_2_area);

    SDL_Rect blitz_3_area{900, 380, 80, 40};
    SDL_RenderFillRect(RENDERER, &blitz_3_area);
    WrappedTexture blitz_3;
    blitz_3.SetupTextureFromText(18, true, "5 min", _WHITE_COLOR);
    blitz_3.Render(blitz_3_area.x + (blitz_3_area.w - blitz_3.GetWidth()) / 2, blitz_3_area.y + (blitz_3_area.h - blitz_3.GetHeight()) / 2);
    all_button_areas.push_back(blitz_3_area);

    // Rapid category
    SDL_Texture* rapid_icon = LoadTexture("media/rapid_icon.png");
    SDL_Rect rapid_icon_area{700, 440, 20, 20};
    SDL_RenderCopy(RENDERER, rapid_icon, nullptr, &rapid_icon_area);

    WrappedTexture rapid_title;
    rapid_title.SetupTextureFromText(12, true, "Rapid", _WHITE_COLOR);
    rapid_title.Render(725, 440);

    SDL_Rect rapid_1_area{700, 460, 80, 40};
    SDL_RenderFillRect(RENDERER, &rapid_1_area);
    WrappedTexture rapid_1;
    rapid_1.SetupTextureFromText(18, true, "10 min", _WHITE_COLOR);
    rapid_1.Render(rapid_1_area.x + (rapid_1_area.w - rapid_1.GetWidth()) / 2, rapid_1_area.y + (rapid_1_area.h - rapid_1.GetHeight()) / 2);
    all_button_areas.push_back(rapid_1_area);

    SDL_Rect rapid_2_area{800, 460, 80, 40};
    SDL_RenderFillRect(RENDERER, &rapid_2_area);
    WrappedTexture rapid_2;
    rapid_2.SetupTextureFromText(18, true, "15 | 10", _WHITE_COLOR);
    rapid_2.Render(rapid_2_area.x + (rapid_2_area.w - rapid_2.GetWidth()) / 2, rapid_2_area.y + (rapid_2_area.h - rapid_2.GetHeight()) / 2);
    all_button_areas.push_back(rapid_2_area);

    SDL_Rect rapid_3_area{900, 460, 80, 40};
    SDL_RenderFillRect(RENDERER, &rapid_3_area);
    WrappedTexture rapid_3;
    rapid_3.SetupTextureFromText(18, true, "30 min", _WHITE_COLOR);
    rapid_3.Render(rapid_3_area.x + (rapid_3_area.w - rapid_3.GetWidth()) / 2, rapid_3_area.y + (rapid_3_area.h - rapid_3.GetHeight()) / 2);
    all_button_areas.push_back(rapid_3_area);

    // Standard category
    SDL_Texture* standard_icon = LoadTexture("media/standard_icon.png");
    SDL_Rect standard_icon_area{700, 515, 25, 20};
    SDL_RenderCopy(RENDERER, standard_icon, nullptr, &standard_icon_area);

    WrappedTexture standard_title;
    standard_title.SetupTextureFromText(12, true, "Standard", _WHITE_COLOR);
    standard_title.Render(725, 520);

    SDL_Rect standard_1_area{700, 540, 80, 40};
    SDL_RenderFillRect(RENDERER, &standard_1_area);
    WrappedTexture standard_1;
    standard_1.SetupTextureFromText(18, true, "1 hour", _WHITE_COLOR);
    standard_1.Render(standard_1_area.x + (standard_1_area.w - standard_1.GetWidth()) / 2, standard_1_area.y + (standard_1_area.h - standard_1.GetHeight()) / 2);
    all_button_areas.push_back(standard_1_area);

    SDL_Rect standard_2_area{800, 540, 80, 40};
    SDL_RenderFillRect(RENDERER, &standard_2_area);
    WrappedTexture standard_2;
    standard_2.SetupTextureFromText(18, true, "2 hour", _WHITE_COLOR);
    standard_2.Render(standard_2_area.x + (standard_2_area.w - standard_2.GetWidth()) / 2, standard_2_area.y + (standard_2_area.h - standard_2.GetHeight()) / 2);
    all_button_areas.push_back(standard_2_area);

    SDL_Rect standard_3_area{900, 540, 80, 40};
    SDL_RenderFillRect(RENDERER, &standard_3_area);
    SDL_Texture* standard3_icon = LoadTexture("media/standard3.png");
    SDL_RenderCopy(RENDERER, standard3_icon, nullptr, &standard_3_area);
    all_button_areas.push_back(standard_3_area);

    // Play button
    SDL_Rect play_button_area{700, 620, 280, 60};
    SDL_SetRenderDrawColor(RENDERER, 130, 180, 80, 200); // LIGHT GREEN
    SDL_RenderFillRect(RENDERER, &play_button_area);
    WrappedTexture play;
    play.SetupTextureFromText(36, true, "Play", _WHITE_COLOR);
    play.Render(play_button_area.x + (play_button_area.w - play.GetWidth()) / 2, play_button_area.y + (play_button_area.h - play.GetHeight()) / 2);
    all_button_areas.push_back(play_button_area);

    SDL_RenderPresent(RENDERER);

    // Select timer
    bool timer_set = false;
    int timer_chosen = -1;
    vector <SDL_Rect> clicked_area;
    while(!timer_set)
    {
        while(SDL_PollEvent(&EVENT))
        {
            if (EVENT.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouse_position_x, mouse_position_y;
                SDL_GetMouseState(&mouse_position_x, &mouse_position_y);

                if (clicked_area.empty())
                {
                    for (unsigned int i = 0; i < all_button_areas.size() - 1; i++)
                    {
                        if (mouse_position_x > all_button_areas[i].x && mouse_position_x < all_button_areas[i].x + 80 &&
                            mouse_position_y > all_button_areas[i].y && mouse_position_y < all_button_areas[i].y + 40) // Clicked a timer
                        {
                            SDL_SetRenderDrawColor(RENDERER, 130, 180, 80, 200); // LIGHT GREEN
                            SDL_RenderDrawRect(RENDERER, &all_button_areas[i]);
                            SDL_RenderPresent(RENDERER);
                            clicked_area.push_back(all_button_areas[i]);
                            timer_chosen = i;
                            break;
                        }
                    }
                }
                else
                {
                    for (unsigned int i = 0; i < all_button_areas.size() - 1; i++)
                    {
                        if (mouse_position_x > all_button_areas[i].x && mouse_position_x < all_button_areas[i].x + 80 &&
                            mouse_position_y > all_button_areas[i].y && mouse_position_y < all_button_areas[i].y + 40) // Click another timer
                        {
                            SDL_SetRenderDrawColor(RENDERER, 100, 100, 100, 200); // LIGHT BLACK
                            SDL_RenderDrawRect(RENDERER, &clicked_area[0]);
                            clicked_area.clear();

                            SDL_SetRenderDrawColor(RENDERER, 130, 180, 80, 200); // LIGHT GREEN
                            SDL_RenderDrawRect(RENDERER, &all_button_areas[i]);
                            SDL_RenderPresent(RENDERER);
                            clicked_area.push_back(all_button_areas[i]);
                            timer_chosen = i;
                            break;
                        }
                    }

                    if (mouse_position_x > all_button_areas[all_button_areas.size() - 1].x && mouse_position_x < all_button_areas[all_button_areas.size() - 1].x + 280 &&
                            mouse_position_y > all_button_areas[all_button_areas.size() - 1].y && mouse_position_y < all_button_areas[all_button_areas.size() - 1].y + 60) // Click the play button
                    {
                        timer_set = true;
                    }
                }
            }
            else if (EVENT.type == SDL_QUIT)
            {
                return false;
            }
        }
    }

    switch (timer_chosen)
    {
        case 0:
            clock_ = ChessClock(1 * 60 * 1000, 0);
            break;
        case 1:
            clock_ = ChessClock(1 * 60 * 1000, 1 * 1000);
            break;
        case 2:
            clock_ = ChessClock(2 * 60 * 1000, 1 * 1000);
            break;
        case 3:
            clock_ = ChessClock(3 * 60 * 1000, 0);
            break;
        case 4:
            clock_ = ChessClock(3 * 60 * 1000, 2 * 1000);
            break;
        case 5:
            clock_ = ChessClock(5 * 60 * 1000, 0);
            break;
        case 6:
            clock_ = ChessClock(10 * 60 * 1000, 0);
            break;
        case 7:
            clock_ = ChessClock(15 * 60 * 1000, 10 * 1000);
            break;
        case 8:
            clock_ = ChessClock(30 * 60 * 1000, 0);
            break;
        case 9:
            clock_ = ChessClock(60 * 60 * 1000, 0);
            break;
        case 10:
            clock_ = ChessClock(120 * 60 * 1000, 0);
            break;
        case 11:
            clock_ = ChessClock(0, 0);
            break;
    }

    SDL_SetRenderDrawColor(RENDERER, 40, 40, 40, 0);
    SDL_Rect temp{640, 0, 460, _SCREEN_HEIGHT};
    SDL_RenderFillRect(RENDERER, &temp);

    return true;
}



void ClassicChessGame::RenderScoreInMatch()
{
    SDL_Rect player_pfp_position {700, 340, 80, 80};
    SDL_RenderCopy(RENDERER, LoadTexture("media/anonymous.png"), nullptr, &player_pfp_position);
    WrappedTexture player1_name;
    player1_name.SetupTextureFromText(24, false, "White", _WHITE_COLOR);
    player1_name.Render(700 + (80 - player1_name.GetWidth()) / 2, 440);

    WrappedTexture player1_score;
    player1_score.SetupTextureFromText(36, true, to_string(white_score_), _WHITE_COLOR);
    player1_score.Render(800, 340 + (80 - player1_score.GetHeight()) / 2);

    player_pfp_position = SDL_Rect {1000, 340, 80, 80};
    SDL_RenderCopy(RENDERER, LoadTexture("media/anonymous.png"), nullptr, &player_pfp_position);
    WrappedTexture player2_name;
    player2_name.SetupTextureFromText(24, false, "Black", _WHITE_COLOR);
    player2_name.Render(1000 + (80 - player2_name.GetWidth()) / 2, 440);

    WrappedTexture player2_score;
    player2_score.SetupTextureFromText(36, true, to_string(black_score_), _WHITE_COLOR);
    player2_score.Render(1000 - 20 - player2_score.GetWidth(), 340 + (80 - player2_score.GetHeight()) / 2);
}



void ClassicChessGame::RenderScoreWhileSelectingTimer()
{
    SDL_Rect player_pfp_position {700, 60, 50, 50};
    SDL_RenderCopy(RENDERER, LoadTexture("media/anonymous.png"), nullptr, &player_pfp_position);
    WrappedTexture player1_name;
    player1_name.SetupTextureFromText(18, false, "White", _WHITE_COLOR);
    player1_name.Render(player_pfp_position.x + (player_pfp_position.w - player1_name.GetWidth()) / 2, 130);

    WrappedTexture player1_score;
    player1_score.SetupTextureFromText(24, true, to_string(white_score_), _WHITE_COLOR);
    player1_score.Render(player_pfp_position.x + player_pfp_position.w + 20, player_pfp_position.y + (player_pfp_position.h - player1_score.GetHeight()) / 2);

    player_pfp_position = SDL_Rect {980 - 50, 60, 50, 50};
    SDL_RenderCopy(RENDERER, LoadTexture("media/anonymous.png"), nullptr, &player_pfp_position);
    WrappedTexture player2_name;
    player2_name.SetupTextureFromText(18, false, "Black", _WHITE_COLOR);
    player2_name.Render(player_pfp_position.x + (player_pfp_position.w - player2_name.GetWidth()) / 2, 130);

    WrappedTexture player2_score;
    player2_score.SetupTextureFromText(24, true, to_string(black_score_), _WHITE_COLOR);
    player2_score.Render(player_pfp_position.x - 20 - player2_score.GetWidth(), player_pfp_position.y + (player_pfp_position.h - player2_score.GetHeight()) / 2);
}
