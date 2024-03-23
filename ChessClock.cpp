#include "ChessClock.h"



ChessClock::ChessClock(const int input_time_limit)
{
    time_limit_ = input_time_limit;
    white_time_left_ = input_time_limit;
    black_time_left_ = input_time_limit;
    is_running_ = false;
    bool side_to_move_ = _WHITE;
}



void ChessClock::StartClock()
{
    is_running_ = true;
    thread clock_thread(&ChessClock::RunClock, this);
    clock_thread.detach();
}



void ChessClock::StopClock()
{
    is_running_ = false;
}



void ChessClock::RunClock()
{
    while(is_running_)
    {
        auto start_time_point = high_resolution_clock::now();

        MUTEX.lock();

//        cout << "White time left: " << white_time_left_ << " seconds\n";
//        cout << "Black time left: " << black_time_left_ << " seconds\n\n";

        if (side_to_move_ == _WHITE)
        {
            white_time_left_ -= 250;
        }
        else if (side_to_move_ == _BLACK)
        {
            black_time_left_ -= 250;
        }

        if (white_time_left_ == 0 || black_time_left_ == 0)
        {
            is_running_ = false;
        }

        MUTEX.unlock();

        //this_thread::sleep_for(milliseconds(1000));

        auto end_time_point = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds> (end_time_point - start_time_point).count();

        int remaining_time = 250 - duration;
        if (remaining_time > 0)
        {
            this_thread::sleep_for(milliseconds(remaining_time));
        }
    }
}



void ChessClock::SetSideToMove(const _CHESS_PIECE_COLORS side_to_move)
{
    side_to_move_ = side_to_move;
}



pair<string, string> ChessClock::ConvertTime()
{
    int white_minutes_left = white_time_left_ / (1000 * 60);
    int white_seconds_left = (white_time_left_ % (1000 * 60)) / 1000;

    string white_time_left = "";
    if (white_minutes_left < 10)
    {
        white_time_left += ('0' + to_string(white_minutes_left) + ':');
    }
    else
    {
        white_time_left += (to_string(white_minutes_left) + ':');
    }

    if (white_seconds_left < 10)
    {
        white_time_left += ('0' + to_string(white_seconds_left));
    }
    else
    {
        white_time_left += (to_string(white_seconds_left));
    }

    int black_minutes_left = black_time_left_ / (1000 * 60);
    int black_seconds_left = (black_time_left_ % (1000 * 60)) / 1000;

    string black_time_left = "";
    if (black_minutes_left < 10)
    {
        black_time_left += ('0' + to_string(black_minutes_left) + ':');
    }
    else
    {
        black_time_left += (to_string(black_minutes_left) + ':');
    }

    if (black_seconds_left < 10)
    {
        black_time_left += ('0' + to_string(black_seconds_left));
    }
    else
    {
        black_time_left += (to_string(black_seconds_left));
    }

    return make_pair(white_time_left, black_time_left);
}



void ChessClock::RenderTime()
{
    pair<string, string> temp = ConvertTime();
    string white_time_left = temp.first;
    string black_time_left = temp.second;

    SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255);
    SDL_Rect clear_area {560, 13, 63, 33}; // Black's clock area
    SDL_RenderFillRect(RENDERER, &clear_area);
    clear_area.y = 714; // White's clock area
    SDL_RenderFillRect(RENDERER, &clear_area);

    WrappedTexture black_clock_texture;
    black_clock_texture.SetupTextureFromText(black_time_left, SDL_Color{0, 0, 0});
    black_clock_texture.Render(560, 13);

    WrappedTexture white_clock_texture;
    white_clock_texture.SetupTextureFromText(white_time_left, SDL_Color{0, 0, 0});
    white_clock_texture.Render(560, 714);
}
