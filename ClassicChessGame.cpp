#include "ClassicChessGame.h"



ClassicChessGame::ClassicChessGame()
{
//    board_();
//    clock_(0);
    side_to_move_first_ = _WHITE;
    side_to_move_ = _WHITE;
    //running_ = false;
    game_over_ = true;
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



void ClassicChessGame::Setup()
{
    board_.SetupDefaultBoard();
    board_.CountPieces();
    board_.DrawChessBoardAndPieces();

    SDL_SetRenderDrawColor(RENDERER, 100, 100, 100, 200); // LIGHT BLACK
    SDL_Rect choosing_time_area;
    choosing_time_area.w = 80;
    choosing_time_area.h = 40;

    // Bullet category
    SDL_Texture* bullet_icon = LoadTexture("media/bullet_icon.png");
    SDL_Rect bullet_icon_area{700, 360, 20, 20};
    SDL_RenderCopy(RENDERER, bullet_icon, nullptr, &bullet_icon_area);

    WrappedTexture bullet_title;
    bullet_title.SetupTextureFromText(12, true, "Bullet", _WHITE_COLOR);
    bullet_title.Render(725, 360);

    choosing_time_area.x = 700;
    choosing_time_area.y = 380;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture bullet_1;
    bullet_1.SetupTextureFromText(18, true, "1 min", _WHITE_COLOR);
    bullet_1.Render(choosing_time_area.x + (choosing_time_area.w - bullet_1.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - bullet_1.GetHeight()) / 2);

    choosing_time_area.x = 800;
    choosing_time_area.y = 380;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture bullet_2;
    bullet_2.SetupTextureFromText(18, true, "1 | 1", _WHITE_COLOR);
    bullet_2.Render(choosing_time_area.x + (choosing_time_area.w - bullet_2.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - bullet_2.GetHeight()) / 2);

    choosing_time_area.x = 900;
    choosing_time_area.y = 380;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture bullet_3;
    bullet_3.SetupTextureFromText(18, true, "2 | 1", _WHITE_COLOR);
    bullet_3.Render(choosing_time_area.x + (choosing_time_area.w - bullet_3.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - bullet_3.GetHeight()) / 2);

    // Blitz category
    SDL_Texture* blitz_icon = LoadTexture("media/blitz_icon.png");
    SDL_Rect blitz_icon_area{700, 435, 20, 25};
    SDL_RenderCopy(RENDERER, blitz_icon, nullptr, &blitz_icon_area);

    WrappedTexture blitz_title;
    blitz_title.SetupTextureFromText(12, true, "Blitz", _WHITE_COLOR);
    blitz_title.Render(725, 440);

    choosing_time_area.x = 700;
    choosing_time_area.y = 460;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture blitz_1;
    blitz_1.SetupTextureFromText(18, true, "3 min", _WHITE_COLOR);
    blitz_1.Render(choosing_time_area.x + (choosing_time_area.w - blitz_1.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - blitz_1.GetHeight()) / 2);

    choosing_time_area.x = 800;
    choosing_time_area.y = 460;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture blitz_2;
    blitz_2.SetupTextureFromText(18, true, "3 | 2", _WHITE_COLOR);
    blitz_2.Render(choosing_time_area.x + (choosing_time_area.w - blitz_2.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - blitz_2.GetHeight()) / 2);

    choosing_time_area.x = 900;
    choosing_time_area.y = 460;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture blitz_3;
    blitz_3.SetupTextureFromText(18, true, "5 min", _WHITE_COLOR);
    blitz_3.Render(choosing_time_area.x + (choosing_time_area.w - blitz_3.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - blitz_3.GetHeight()) / 2);

    // Rapid category
    SDL_Texture* rapid_icon = LoadTexture("media/rapid_icon.png");
    SDL_Rect rapid_icon_area{700, 520, 20, 20};
    SDL_RenderCopy(RENDERER, rapid_icon, nullptr, &rapid_icon_area);

    WrappedTexture rapid_title;
    rapid_title.SetupTextureFromText(12, true, "Rapid", _WHITE_COLOR);
    rapid_title.Render(725, 520);

    choosing_time_area.x = 700;
    choosing_time_area.y = 540;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture rapid_1;
    rapid_1.SetupTextureFromText(18, true, "10 min", _WHITE_COLOR);
    rapid_1.Render(choosing_time_area.x + (choosing_time_area.w - rapid_1.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - rapid_1.GetHeight()) / 2);

    choosing_time_area.x = 800;
    choosing_time_area.y = 540;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture rapid_2;
    rapid_2.SetupTextureFromText(18, true, "15 | 10", _WHITE_COLOR);
    rapid_2.Render(choosing_time_area.x + (choosing_time_area.w - rapid_2.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - rapid_2.GetHeight()) / 2);

    choosing_time_area.x = 900;
    choosing_time_area.y = 540;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture rapid_3;
    rapid_3.SetupTextureFromText(18, true, "30 min", _WHITE_COLOR);
    rapid_3.Render(choosing_time_area.x + (choosing_time_area.w - rapid_3.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - rapid_3.GetHeight()) / 2);

    // Standard category
    SDL_Texture* standard_icon = LoadTexture("media/standard_icon.png");
    SDL_Rect standard_icon_area{700, 595, 25, 20};
    SDL_RenderCopy(RENDERER, standard_icon, nullptr, &standard_icon_area);

    WrappedTexture standard_title;
    standard_title.SetupTextureFromText(12, true, "Standard", _WHITE_COLOR);
    standard_title.Render(725, 600);

    choosing_time_area.x = 700;
    choosing_time_area.y = 620;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture standard_1;
    standard_1.SetupTextureFromText(18, true, "1 hour", _WHITE_COLOR);
    standard_1.Render(choosing_time_area.x + (choosing_time_area.w - standard_1.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - standard_1.GetHeight()) / 2);

    choosing_time_area.x = 800;
    choosing_time_area.y = 620;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    WrappedTexture standard_2;
    standard_2.SetupTextureFromText(18, true, "2 hour", _WHITE_COLOR);
    standard_2.Render(choosing_time_area.x + (choosing_time_area.w - standard_2.GetWidth()) / 2, choosing_time_area.y + (choosing_time_area.h - standard_2.GetHeight()) / 2);

    choosing_time_area.x = 900;
    choosing_time_area.y = 620;
    SDL_RenderFillRect(RENDERER, &choosing_time_area);
    SDL_Texture* standard3_icon = LoadTexture("media/standard3.png");
    SDL_Rect standard3_icon_area{900, 620, choosing_time_area.w, choosing_time_area.h};
    SDL_RenderCopy(RENDERER, standard3_icon, nullptr, &standard3_icon_area);

    clock_ = ChessClock(10000);
}



void ClassicChessGame::Start()
{
    //running_ = true;
    game_over_ = false;
    Run();
}



void ClassicChessGame::Run()
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
            }
            else
            {
                cout << "White wins\n";
            }

            clock_.StopClock();
            game_over_ = true;
        }
        else if (clock_.GetTimeLeft(_WHITE) == 0)
        {
            if (board_.IsOnlyKingLeft(_BLACK))
            {
                cout << "Draw\n";
            }
            else
            {
                cout << "Black wins\n";
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
                    if (side_to_move_ == _WHITE)
                    {
                        side_to_move_ = _BLACK;
                    }
                    else if (side_to_move_ ==  _BLACK)
                    {
                        side_to_move_ = _WHITE;
                    }
                }
                else if (message == _GAME_OVER)
                {
                    clock_.StopClock();
                    game_over_ = true;
                }

                SDL_RenderPresent(RENDERER);
            }

            if (EVENT.type == SDL_QUIT)
            {
                game_over_ = true;
                clock_.StopClock();
                return;
            }
        }
    }

    WaitUntilKeyPressed();
}
