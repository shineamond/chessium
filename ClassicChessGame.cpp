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
    player1_name.SetupTextureFromText("Black", SDL_Color{0, 0, 0}); // BLACK
    player1_name.Render(60, 13);

    player_pfp_position.y = 705;
    SDL_RenderCopy(RENDERER, LoadTexture("media/anonymous.png"), nullptr, &player_pfp_position);
    WrappedTexture player2_name;
    player2_name.SetupTextureFromText("White", SDL_Color{0, 0, 0});
    player2_name.Render(60, 714);

    SDL_RenderPresent(RENDERER);
}



void ClassicChessGame::Setup()
{
    board_.SetupDefaultBoard();
    board_.CountPieces();
    board_.DrawChessBoardAndPieces();

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
